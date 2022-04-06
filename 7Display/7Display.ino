// TEAM SUCC - Display Arduino 1 V1.2
// Name: Yasith De Silva

char mystr[10];

#define common_cathode 0
#define common_anode 1
bool mode = common_cathode;// my display is common anode

#define pinA  2
#define pinB  3
#define pinC  4
#define pinD  5
#define pinE  6
#define pinF  7
#define pinG  8
#define pinDP 13
#define D1  9
#define D2  10
#define D3  11
#define D4  12

#define DP 30

const int charsInArray = 37;
byte digits[]{D1,D2,D3,D4};
byte seg[] {pinA,pinB,pinC,pinD,pinE,pinF,pinG,pinDP};
byte Char[37][9] { 
            
            {1,1,1,1,1,1,0,0,'0'},//0
            {0,1,1,0,0,0,0,0,'1'},//1
            {1,1,0,1,1,0,1,0,'2'},//2
            {1,1,1,1,0,0,1,0,'3'},//3
            {0,1,1,0,0,1,1,0,'4'},//4
            {1,0,1,1,0,1,1,0,'5'},//5
            {1,0,1,1,1,1,1,0,'6'},//6
            {1,1,1,0,0,0,0,0,'7'},//7
            {1,1,1,1,1,1,1,0,'8'},//8
            {1,1,1,1,0,1,1,0,'9'}, //9
            {1,1,1,0,1,1,1,0,'a'},//A/1
            {0,0,1,1,1,1,1,0,'b'},//b/2
            {1,0,0,1,1,1,0,0,'c'},//C/3
            {0,1,1,1,1,0,1,0,'d'},//d/4
            {1,0,0,1,1,1,1,0,'e'},//E/5
            {1,0,0,0,1,1,1,0,'f'},//F/6
            {1,0,1,1,1,1,0,0,'g'},//G/7
            {0,1,1,0,1,1,1,0,'h'},//H/8
            {0,1,1,0,0,0,0,0,'i'},//I/9
            {0,1,1,1,1,0,0,0,'j'},//J/10
            {0,0,0,1,1,1,0,0,'l'},//L/11
            {0,0,1,0,1,0,1,0,'n'},//n/12
            {0,0,1,1,1,0,1,0,'o'},//o/13
            {1,1,0,0,1,1,1,0,'p'},//P/14
            {1,1,1,0,0,1,1,0,'q'},//q/15
            {0,0,0,0,1,0,1,0,'r'},//r/16
            {1,0,1,1,0,1,1,0,'s'},//S/17   looks like number 5
            {0,0,0,1,1,1,1,0,'t'},//t/18
            {0,1,1,1,1,1,0,0,'u'},//U/19
            {0,1,1,1,0,1,1,0,'y'},//y/20
            {0,0,0,0,0,0,0,1,'.'},//.
            {0,0,0,0,0,0,1,0,'-'},//dash/negative
            {0,0,0,1,0,0,0,0,'_'},//underscore
            {1,0,0,1,1,1,0,0,'['},//[
            {1,1,1,1,0,0,0,0,']'},//]
            {1,1,0,0,1,0,1,0,'?'},//?
            {0,0,0,0,0,0,0,0,' '}//blank
            
            };


//#include "array.h"
//#include "functions.h"

void setup(){
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);     
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  
  
  Serial.begin(9600);

//9, 2, 7, 10, 11, 3
// 6, 5,13 ,4,8, 12

}

void loop(){
   // printDisplay("succ",1000);// use this function to print a string 
   //(has numbers, characters or phrases) when the length of string is 4 or less than 4, 
   //the second variable is the time for printing on display

  Serial.readBytes(mystr,4);
  Serial.println(mystr);
  delay(1000);

  //printDigit('1',D3);
  printDisplay(mystr,1000);
  // use this function to print a string (has numbers, characters or phrases) when the length of 
  //string is 4 or less than 4, the second variable is the time for printing on display
  Reset();// use this function to reset the display
 
  //printDisplay("all usable characters 
  //[[ 1 2 3 4 5 6 7 8 9 0 a b c d e f g h i j l n o p q r s t u y - _ . [ ] ? ]]",300);
  // when the length of string is more than 4, the second variable is custom speed for movement
  //delay(1000);
  //printDigit('y',D1);//print any char on any digit
  //delay(1000);
}

void Reset(){ 
  digitalWrite(D1, !mode);
  digitalWrite(D2, !mode);
  digitalWrite(D3, !mode);
  digitalWrite(D4, !mode); 
  for(byte i = 0 ; i < 8 ; i++){
    digitalWrite(seg[i],mode);
  }
}

void printDigit(char Chara,int digitPort){ 
  Reset(); 
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
  for(int i = 0;i<= 7;i++){
    if(mode == common_anode) digitalWrite(seg[i],!Char[character][i]);     
    else if(mode == common_cathode) digitalWrite(seg[i],Char[character][i]);
      
    }
  }
}

void printDisplay(String Phrase,int Delay){
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
  
