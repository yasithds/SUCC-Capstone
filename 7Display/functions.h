void Reset()
{ digitalWrite(D1, !mode);
  digitalWrite(D2, !mode);
  digitalWrite(D3, !mode);
  digitalWrite(D4, !mode); 
  for(byte i = 0 ; i < 8 ; i++){
  digitalWrite(seg[i],mode);
  }
}



void printDigit(char Chara,int digitPort)
{ Reset(); 
  int character = -1;
  digitalWrite(digitPort,mode);
  for(int i = 0 ; i < charsInArray ; i++){
    
    if(Chara == Char[i][8]){
      character = i;
    }
  }
  if (character == -1){
    digitalWrite(pinG,!mode);
  }else{
for(int i = 0;i<= 7;i++)
    {if(mode == common_anode) digitalWrite(seg[i],!Char[character][i]);     
    else if(mode == common_cathode) digitalWrite(seg[i],Char[character][i]);
      
    }
  }
}





void printDisplay(String Phrase,int Delay)
{
char char1 = Phrase.charAt(0);
char char2 = Phrase.charAt(1);
char char3 = Phrase.charAt(2);
char char4 = Phrase.charAt(3);
//char char5 = Phrase.charAt(4);
char char1Num = 0;
char char2Num = 0;
char char3Num = 0;
char char4Num = 0;
int stringLength = Phrase.length();

if(stringLength < 5){
  for(int ti = 0 ; ti <= (Delay / 8) ; ti++){
  if(1 > stringLength) char1 = ' ';
  else char1 = Phrase.charAt(0);
  if(2 > stringLength) char2 = ' ';
  else char2 = Phrase.charAt(1);
  if(3 > stringLength) char3 = ' ';
  else char3 = Phrase.charAt(2);
  if(4 > stringLength) char4 = ' ';
  else char4 = Phrase.charAt(3);
 /* Reset();
  delay(2);*/
  printDigit(char1,D1);
  delay(2);
  printDigit(char2,D2);
  delay(2);
  printDigit(char3,D3);
  delay(2);
  printDigit(char4,D4);
  delay(2);
  }
}else{
for(int t = 0 ; t <= stringLength ; t++){
  for(int ti = 0 ; ti <= (Delay / 8) ; ti++){
  
  /*Reset();
  delay(2);*/
  printDigit(char1,D1);
  delay(2);
  printDigit(char2,D2);
  delay(2);
  printDigit(char3,D3);
  delay(2);
  printDigit(char4,D4);
  delay(2);
}
  if(t + 1 > stringLength) char1 = ' ';
  else char1 = Phrase.charAt(t);
  if((t + 2) > stringLength) char2 = ' ';
  else char2 = Phrase.charAt(t + 1);
  if((t + 3) > stringLength) char3 = ' ';
  else char3 = Phrase.charAt(t + 2);
  if((t + 4) > stringLength) char4 = ' ';
  else char4 = Phrase.charAt(t + 3);
  
  
  
}
}
}
  
