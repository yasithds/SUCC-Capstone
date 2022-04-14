//#include <AFMotor.h>
// AF_Stepper motor1(2038,1); //#steps per rev, motor placement on board
// AF_Stepper motor2(2038,2);

//Rotary Encoder Inputs
#include <SimpleKeypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>   

#define inputCLK 10
#define inputDT 11

#define SLAVE_ADDR 9

LiquidCrystal_I2C lcd(0x27,20,4);     

const byte nb_rows = 4;                         // four rows
const byte nb_cols = 4;                         // four columns
char key_chars[nb_rows][nb_cols] = {            // The symbols of the keys
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[nb_rows] = {5, 4, 3, 2};             // The pins where the rows are connected
byte colPins[nb_cols] = {9, 8, 7, 6};         // The pins where the columns are connected

/* initialize an instance of class NewKeypad */
SimpleKeypad kp1((char*)key_chars, rowPins, colPins, nb_rows, nb_cols);   // New keypad called kp1


int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {
  Wire.begin(); //starts i2c as master
  
  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT);
  pinMode (inputDT, INPUT);

  lcd.init();
  lcd.backlight();                
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  lcd.print("Funny!");
  lcd.setCursor(3,2);            
  lcd.print("Enjoy!");
  lcd.setCursor(8,3);             
  lcd.print("Arduino!");      

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

}

void loop() {

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter --;
      encdir = "CCW";

    } else {
      // Encoder is rotating clockwise
      counter ++;
      encdir = "CW";
      //  digitalWrite(ledCW, HIGH);
      // digitalWrite(ledCCW, LOW);

    }
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
  }

   char key = kp1.getKey();                      // The getKey function scans the keypad every 10 ms and returns a key only one time, when you start pressing it
  if (key) {                                    // If getKey returned any key
    Serial.println(key);                        // it is printed on the serial monitor
    lcd.print(key);   
  }
  if (key=='A') {                                    // If getKey returned any key
    Serial.println(key);                        // it is printed on the serial monitor
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(45);
    Wire.write(1);
    Wire.endTransmission();
    
  } else if (key=='B') {
     Serial.println(key);                        // it is printed on the serial monitor
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(90);
    Wire.write(1);
    Wire.endTransmission();
    
  } else if (key=='C') {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(counter);
    Wire.write(2);
    Wire.endTransmission();
    
  } else if (key=='D') {
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } 

  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}
