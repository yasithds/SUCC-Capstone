//#include <AFMotor.h>
// AF_Stepper motor1(2038,1); //#steps per rev, motor placement on board
// AF_Stepper motor2(2038,2);

//Rotary Encoder Inputs

#define inputCLK 10
#define inputDT 11

#include <SimpleKeypad.h>

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

  // Set encoder pins as inputs
  pinMode (inputCLK, INPUT);
  pinMode (inputDT, INPUT);

  // pinMode (2,OUTPUT);
  // pinMode (13,OUTPUT);
  // pinMode (9,OUTPUT);
  //     pinMode (10,OUTPUT);

  //   digitalWrite(2, HIGH);
  //  digitalWrite(13, HIGH);
  //   digitalWrite(9, HIGH);
  //  digitalWrite(10, HIGH);


  // Set LED pins as outputs
  //  pinMode (ledCW,OUTPUT);
  // pinMode (ledCCW,OUTPUT);

  // Setup Serial Monitor
  Serial.begin (9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

  // motor1.setSpeed(100);
  //   motor2.setSpeed(100);
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
      //  digitalWrite(ledCW, LOW);
      // digitalWrite(ledCCW, HIGH);

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

  //FORWARD/BACKWARD, SINGLE/DOUBLE/INTERLEAVE/MICROSTEP
  // Serial.println("Single coil steps");
  //motor1.step(2048, FORWARD, SINGLE);
  //motor2.step(2048, FORWARD, SINGLE);

   char key = kp1.getKey();                      // The getKey function scans the keypad every 10 ms and returns a key only one time, when you start pressing it
  if (key=='A') {                                    // If getKey returned any key
    Serial.println(key);                        // it is printed on the serial monitor
  }

  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}
