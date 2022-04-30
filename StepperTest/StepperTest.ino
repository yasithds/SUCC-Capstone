#include <Wire.h>
//#include <AFMotor.h>

#define SLAVE_ADDR 9

//AF_Stepper motor1(200,1); //#steps per rev, motor placement on board
//AF_Stepper motor2(200,2);
#define NO_OF_STEPS 200
#define motor1 2
#define motor1_dir 5
#define motor2 3
#define motor2_dir 6

//keypress modes
// 0= change indexing mode
// 1= index
// 2= motor1 tilt
// 3= 15
// 4 = 30
// 5 = 45
// 9= demo mode

String data ="";
int data_int;
int angle =0;
int stepNum_angle;
int stepNum_tilt;
int tilt = 0;
int ratio=1;// gear ratio (40)
int indexAngle=0;
int index_type =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor1_dir, OUTPUT);
  pinMode(motor2_dir, OUTPUT);

     
Serial.begin (9600);
Wire.begin(SLAVE_ADDR); //I2C as slave

Wire.onReceive(receiveEvent);
Wire.onRequest(requestEvent);

//motor1.setSpeed(100);
//motor2.setSpeed(100);
}

void requestEvent(){

}


void receiveEvent(int howMany){
  data ="";
  int c =0;
  while(1 < Wire.available()){
    c = Wire.read();          
    Serial.print(c);             
    data += c;//used to determine the angle (in degrees)
  }
  
  int action = Wire.read(); // determines the actual motor to manipulate
  Serial.println(action);

  data_int = data.toInt();
  tilt = (data.substring(0,2)).toInt();
  angle = (data.substring(2)).toInt();
  Serial.print("tilt ");
  Serial.println(tilt);
    Serial.print("anlge ");
  Serial.println(angle);
  //angle = data.toInt();
  
  if (action ==0) {
    if (index_type ==0){
        index_type =1; // amount
        stepNum_angle = (360/angle)*(200*40);
       
      } else {
        index_type =0; // angle
        stepNum_angle = map(angle, 0, 180, 0, (200/2)*40);
      }
      
    
  }
    
  stepNum_tilt = map(tilt, 0, 90, 0, (200/4)*90);
  
  if (action ==1) {
    //index
    for(int x = 0; x<stepNum_angle; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
  } else if (action == 2){ //motor1 = tilt
  
    //tilt
    for(int x = 0; x<stepNum_tilt; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(500);
    }
  }  else if (action == 9){ //demo mode
  
    //tilt
    for(int x = 0; x<(200/4)*40; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(500);
    }
    delay(1000);
    digitalWrite(motor1_dir,LOW);
    for(int x = (200/4)*40; x>0; x--) { // loop for steps
      digitalWrite(motor1_dir,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(500);
    }
    delay(1000);
    /*
        for(int x = 0; x<200*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
      */
    } else if (action ==3) { //15
    //index
    for(int x = 0; x<200*15/360*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
  } else if (action ==4) { //30
    //index
    for(int x = 0; x<200*30/360*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
    
  }else if (action ==5) { // 45
    //index
    for(int x = 0; x<200*45/360*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
  } else if (action ==6) { //90
    //index
    for(int x = 0; x<200*90/360*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
  } else if (action ==7) { //180
    //index
    for(int x = 0; x<200*0.5*40; x++) { // loop for steps
      digitalWrite(motor2,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor2,LOW); 
      delayMicroseconds(500);
    }
  }  else if (action ==8) { //360
    //index
      digitalWrite(motor1_dir, HIGH);
    for(int x = 0; x<200*0.125*90; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(600);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(600);
    }
  } else if (action ==9) { //360
    //index
      digitalWrite(motor1_dir, LOW);
    for(int x = 0; x<200*90; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(600);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(600);
    }
  } 




  

   /*
    stepNum = map(c, -90, 90, (-200/4)*ratio, (200/4)*ratio);
    if (stepNum >= tilt && stepNum+tilt <= ratio){ //50* (1:40) from gearing
      
    Serial.print("angle: ");
    Serial.println(angle);
    Serial.print("steps: ");
    Serial.println(stepNum);
   // motor1.step(stepNum-tilt, FORWARD, SINGLE);
    tilt = stepNum - tilt;
    
    } else if (stepNum >= tilt && stepNum+tilt >= ratio){
     // motor1.step(ratio - tilt, FORWARD, SINGLE);
      tilt = ratio;
      
    } else if (stepNum>0 && stepNum < tilt && stepNum+tilt <= -ratio){
      //motor1.step(stepNum, BACKWARD, SINGLE);
      tilt = tilt - stepNum;  
    } else if (stepNum < tilt && stepNum+tilt <= -ratio){
      //motor1.step(tilt, BACKWARD, SINGLE);
      tilt = 0; 
    }

      
    //motor1.step(stepNum+tilt, BACKWARD, SINGLE);
    tilt += stepNum;
    
    Serial.print("Current Tilt: ");
    Serial.println(tilt);
    
  } else if (action==2){ // motor 2 = indexing angle
    // Set indexing angle
    stepNum = map(c, 0, 180, 0, (200/2)*ratio);
  } else if (action==3){ // motor 2 - indexing divisions
    // Set indexing by divisions
    stepNum = (200/c) * ratio;
  } else {
    // Continue with current index
    // motor2.step(stepNum, FORWARD, SINGLE);
  
  */
  
} 




void loop() {
  // stuff here is basically just reference material -------------------------
  // put your main code here, to run repeatedly:
  //FORWARD/BACKWARD, SINGLE/DOUBLE/INTERLEAVE/MICROSTEP
// Serial.println("Single coil steps");
  //motor1.step(200, FORWARD, SINGLE);
  delay(200);
  // motor2.step(200, FORWARD, SINGLE);
  //Serial.println(data);

  //index

  /*

     digitalWrite(motor1_dir, HIGH);
     for(int x = 0; x<200*40; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(500);
    }
    delay(1000);
        //index
     digitalWrite(motor1_dir, LOW);
     for(int x = 0; x<200*40; x++) { // loop for steps
      digitalWrite(motor1,HIGH);
      delayMicroseconds(500);
      digitalWrite(motor1,LOW); 
      delayMicroseconds(500);
    }
    */
   
   
    
  delay(2000);
  //tilt
//digitalWrite(motor1_dir,HIGH); //high = rotate up

}
