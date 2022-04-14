#include <Wire.h>
#include <AFMotor.h>

#define SLAVE_ADDR 9

AF_Stepper motor1(200,1); //#steps per rev, motor placement on board
AF_Stepper motor2(200,2);

String data ="";
int angle =0;
int stepNum;
int tilt = 0;
int ratio=1;// gear ratio (40)
int indexAngle=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
Wire.begin(SLAVE_ADDR); //I2C as slave

Wire.onReceive(receiveEvent);
Wire.onRequest(requestEvent);

motor1.setSpeed(100);
motor2.setSpeed(100);
}

void requestEvent(){

}


void receiveEvent(int howMany){
  data ="";
  int c =0;
  while(1 < Wire.available()){
    c = Wire.read();          
    Serial.print(c);             
    //data += c;//used to determine the angle (in degrees)
  }

  int action = Wire.read(); // determines the actual motor to manipulate
  Serial.println(action);

  //angle = data.toInt();
  
  if (action == 1){ //motor 1 = tilt
    stepNum = map(c, -90, 90, (-200/4)*ratio, (200/4)*ratio);
    if (stepNum >= tilt && stepNum+tilt <= ratio){ //50* (1:40) from gearing
      
    Serial.print("angle: ");
    Serial.println(angle);
    Serial.print("steps: ");
    Serial.println(stepNum);
    motor1.step(stepNum-tilt, FORWARD, SINGLE);
    tilt = stepNum - tilt;
    
    } else if (stepNum >= tilt && stepNum+tilt >= ratio){
      motor1.step(ratio - tilt, FORWARD, SINGLE);
      tilt = ratio;
      
    } else if (stepNum>0 && stepNum < tilt && stepNum+tilt <= -ratio){
      motor1.step(stepNum, BACKWARD, SINGLE);
      tilt = tilt - stepNum;  
    } else if (stepNum < tilt && stepNum+tilt <= -ratio){
      motor1.step(tilt, BACKWARD, SINGLE);
      tilt = 0; 
    }

      
    motor1.step(stepNum+tilt, BACKWARD, SINGLE);
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
     motor2.step(stepNum, FORWARD, SINGLE);
  }
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
  delay(200);
}
