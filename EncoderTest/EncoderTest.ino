//#include <AFMotor.h>
// AF_Stepper motor1(2038,1); //#steps per rev, motor placement on board
// AF_Stepper motor2(2038,2);

//Rotary Encoder Inputs
#include <SimpleKeypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>   

#define inputCLK 2
#define inputDT 3

#define SLAVE_ADDR 9

LiquidCrystal_I2C lcd(0x27,20,4); 

int menuCounter = 0; //counts the clicks of the rotary encoder between menu items (0-3 in this case)

int menu1_Value = 0; //value within menu 1
int menu2_Value = 0; //value within menu 2
int menu3_Value = 0; //value within menu 3
int menu4_Value = 0; //value within menu 4

bool menu1_selected = false; //enable/disable to change the value of menu item
bool menu2_selected = false;
bool menu3_selected = false;
bool menu4_selected = false;

const byte nb_rows = 4;                         // four rows
const byte nb_cols = 4;                         // four columns
char key_chars[nb_rows][nb_cols] = {            // The symbols of the keys
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[nb_rows] = {5, 4, 11, 10};             // The pins where the rows are connected
byte colPins[nb_cols] = {9, 8, 7, 6};         // The pins where the columns are connected

/* initialize an instance of class NewKeypad */
SimpleKeypad kp1((char*)key_chars, rowPins, colPins, nb_rows, nb_cols);   // New keypad called kp1


int counter = 0;
int angle =0;
int index =0;
int currentStateCLK;
int previousStateCLK;
int button=12;
int buttonState=1;

String encdir = "";

void setup() {
  Wire.begin(); //starts i2c as master
  
  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT);
  pinMode (inputDT, INPUT);
  pinMode (button, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();                
  lcd.setCursor(0,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("        SUCC");
  lcd.setCursor(0,2);            
  lcd.print("  DIGITAL  INDEXING");
  lcd.setCursor(0,3);             
  //lcd.print("Press to wake");      

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

    while (buttonState ==1) {
    buttonState = digitalRead(button);
    delay(500);
    Serial.println("Press encoder button to start");
  }
}

void loop() {

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
  buttonState = digitalRead(button);

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
    Serial.println(key);  
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(counter);
    Wire.write(2);
    Wire.endTransmission();  
  } else if (key=='D') {
    Serial.println(key);  
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();  
  } else if (key=='1') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();   
  } else if (key=='2') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission(); 
  } else if (key=='3') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='4') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='5') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='6') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='7') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='8') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='9') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='0') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  }else if (key=='*') {
    Serial.println(key);
    Serial.println("DEMO SEQUENCE"); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } else if (key=='#') {
    Serial.println(key); 
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0);
    Wire.write(4);
    Wire.endTransmission();
  } 
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}
