// TEAM SUCC - Control Arduino 1 V1.2
// Name: Yasith De Silva

#include <LiquidCrystal.h> 
#include <Stepper.h>

//Create Liquid Crystal Object called LCD and assigns pins
LiquidCrystal LCD(7, 8, 9, 10, 11, 12); 
Stepper stepper = Stepper(2048, 3, 5, 4, 6); // 3 4 5 6

int button1 =13;
int button2 =2;
int button3 =A2;
double pot = A5;

bool buttonState1;
bool buttonState2;
bool buttonState3;

int delayAmount=50;
int menu=0;
double angle;

int stepPos=0;
int currentPos=0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(pot,INPUT);

  stepper.setSpeed(10);
    
  LCD.begin(16,2);
  LCD.clear();
  LCD.setCursor(0,0); 
  LCD.print("MENU ");
  LCD.setCursor(0,1); 
  LCD.print("1.Adjust Angle");
  
  buttonState1= digitalRead(button1);
  buttonState2= digitalRead(button2);
  buttonState3= digitalRead(button3);
}

void loop() {
  buttonState1= digitalRead(button1);
  buttonState2= digitalRead(button2);
  buttonState3= digitalRead(button3);

  if (buttonState1==0 && menu==0) {
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("2.Adjust Incline");
    menu++;
    delay(delayAmount);
  } else if (buttonState2==0 && menu==1) {
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("1.Adjust Angle");
    menu--;
    delay(delayAmount);
  } else if (buttonState1==0 && menu==1) {
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("1.Adjust Angle");
    menu--;
    delay(delayAmount);
  } else if (buttonState2==0 && menu==0) {
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("2.Adjust Incline");
    menu++;
    delay(delayAmount);
  }

  if (menu==0 && buttonState3==0){
    adjustAngle();
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("1.Adjust Angle");
  } else if (menu==1 && buttonState3==0){
    adjustTilt();
    LCD.clear();
    LCD.setCursor(0,0); 
    LCD.print("MENU ");
    LCD.setCursor(0,1); 
    LCD.print("2.Adjust Incline");
  }
  
  // put your main code here, to run repeatedly:
}

int adjustAngle(){
  char TempString[10];  //  Hold The Convert Data
  LCD.clear();
  LCD.setCursor(0,0); 
  LCD.print("Adjust Angle ");

  while (true){
     
    buttonState1= digitalRead(button1);
    buttonState3= digitalRead(button3);
    angle =  analogRead(pot);

    //this will be updated with incremental encoder code
    angle =  analogRead(pot)/(900.00)*180;

    dtostrf(angle,5,5,TempString);
 // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )

    //Serial.write(TempString,5);
    Serial.println(angle);
    LCD.setCursor(0,1); 
    LCD.print(angle,2);
    delay(delayAmount);

    if (buttonState1==0){
      
      break; //setup motor code function
    }
    LCD.setCursor(0,1);
    LCD.print("                ");
  }
}


void adjustTilt(){

  LCD.clear();
  LCD.setCursor(0,0); 
  LCD.print("Adjust Tilt ");
  
  while (true){
    buttonState1= digitalRead(button1);
    buttonState3= digitalRead(button3);
    angle =  analogRead(pot);
    
    angle =  analogRead(pot)/(900.00)*90; 
  
    LCD.setCursor(0,1); 
    LCD.print(angle,2);
    delay(delayAmount);

    if (buttonState1==0){
      motorTilt(angle);
      break; //setup motor code function
    }
    
    LCD.setCursor(0,1);
    LCD.print("                ");
  }
}

void motorTurnint(double angle){
  
}

void motorTilt(double angle){
   stepPos = map(angle, 0.00, 90, 0.00, 2048.00);
   stepper.step(stepPos+currentPos);
   currentPos+=stepPos;
}

//for mapping servo (not needed for stepper)
long fmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
