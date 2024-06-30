#include <Servo.h>

// Servo objects
Servo myservo1; // Arm up and down
Servo myservo2; // Wrist up and down
Servo myservo3; // Base rotation
Servo myservo4; // Gripper

// Joystick pins
const int joystick1X = A0; // Joystick 1 X-axis for myservo2
const int joystick1Y = A1; // Joystick 1 Y-axis for myservo1
const int joystick2X = A2; // Joystick 2 X-axis for myservo4
const int joystick2Y = A3; // Joystick 2 Y-axis for myservo3

// Servo pins
const int servoPin1 = 9;  // myservo1 pin
const int servoPin2 = 10; // myservo2 pin
const int servoPin3 = 11; // myservo3 pin
const int servoPin4 = 12; // myservo4 pin

// Current angles
int angle1 = 30;
int angle2 = 90;
int angle3 = 90;
int angle4 = 90;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Attach servos to pins
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  myservo3.attach(servoPin3);
  myservo4.attach(servoPin4);

  // Initialize servos to their default positions
  myservo1.write(angle1);
  myservo2.write(angle2);
  myservo3.write(angle3);
  myservo4.write(angle4);
}

void loop() {
  // Read joystick values
  int joystick1XVal = analogRead(joystick1X);
  int joystick1YVal = analogRead(joystick1Y);
  int joystick2XVal = analogRead(joystick2X);
  int joystick2YVal = analogRead(joystick2Y);

  // Threshold to avoid noise
  int threshold = 35;

  // Update angle1 for myservo1 based on joystick1 Y-axis
  if (abs(joystick1YVal - 512) > threshold) {
    int change1 = map(joystick1YVal, 0, 1023, -5,5); // Adjust sensitivity
    angle1 = constrain(angle1 + change1, 0, 180);
    myservo1.write(angle1);

    // Update myservo2 based on myservo1's movement
    // angle2 = angle1; // You can adjust this logic if needed
    // myservo2.write(angle2);
  }

  // Update angle2 for myservo2 based on joystick1 X-axis
  if (abs(joystick1XVal - 512) > threshold) {
    int change2 = map(joystick1XVal, 0, 1023, -5,5); // Adjust sensitivity
    angle2 = constrain(angle2 + change2, 0, 180);
    myservo2.write(angle2);
  }

  // Update angle3 for myservo3 based on joystick2 Y-axis
  if (abs(joystick2YVal - 512) > threshold) {
    int change3 = map(joystick2YVal, 0, 1023, -5,5); // Adjust sensitivity
    angle3 = constrain(angle3 + change3, 0, 180);
    myservo3.write(angle3);
  }

  // Update angle4 for myservo4 based on joystick2 X-axis
  if (abs(joystick2XVal - 512) > threshold) {
    int change4 = map(joystick2XVal, 0, 1023, -5,5); // Adjust sensitivity
    angle4 = constrain(angle4 + change4, 0, 180);
    myservo4.write(angle4);
  }

  // Print angles to Serial Monitor
  Serial.print("myservo1 angle: ");
  Serial.print(angle1);
  Serial.print("\t"); // Tab space

  Serial.print("myservo2 angle: ");
  Serial.print(angle2);
  Serial.print("\t"); // Tab space

  Serial.print("myservo3 angle: ");
  Serial.print(angle3);
  Serial.print("\t"); // Tab space

  Serial.print("myservo4 angle: ");
  Serial.println(angle4); // Move to next line

  // Small delay for stability
  delay(15);
}
