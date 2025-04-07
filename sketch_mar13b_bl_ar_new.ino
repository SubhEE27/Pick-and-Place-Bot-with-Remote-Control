#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);  // Motor connected to M1
int variableSpeed = 0;

void setup() {
  Wire.begin(8);            // I2C slave address
  Wire.onReceive(receiveEvent);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);     // Motor speed (0-255)
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void receiveEvent(int bytes) {
  if (Wire.available()) {
    char command = Wire.read();

    if (command == 'F') {
      Serial.print("Received: ");
      Serial.println(command);
      moveForward();
    } 
    else if (command == 'B') {
      Serial.print("Received: ");
      Serial.println(command);
      moveBackward();
    } 
    else if (command == 'S') {
      Serial.print("Received: ");
      Serial.println(command);
      stopMotors();
    } 
    else if (command == 'R' || command == 'L') {  // Right or Left motors
      String speedStr = "";                      // To store speed as a string
      while (Wire.available()) {
        char c = Wire.read();
        if (c == '#') break;                     // Stop when '#' is found
        speedStr += c;                           // Build the speed string
      }
      int speed = speedStr.toInt();              // Convert speed string to int
      if (command == 'R') {
        speedRight(speed);
      } else if (command == 'L') {
        speedLeft(speed);
      }
    }
  }
}
 void moveForward(){
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveBackward(){
  motor1.setSpeed(120);
  motor2.setSpeed(120);
  motor3.setSpeed(120);
  motor4.setSpeed(120);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void stopMotors(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void speedRight(int speed) {                 //Left Motors ON 1 and 4
  variableSpeed = constrain(speed, 0, 200);
  motor1.setSpeed(variableSpeed);
  motor4.setSpeed(variableSpeed);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  Serial.print("Variable speed set to: ");
  Serial.println(variableSpeed);
}

void speedLeft(int speed) {                  //Right Motors ON 2 and 3
  variableSpeed = constrain(speed, 0, 200);
  motor2.setSpeed(variableSpeed);
  motor3.setSpeed(variableSpeed);
  motor1.run(RELEASE);
  motor4.run(RELEASE);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  Serial.print("Variable speed set to: ");
  Serial.println(variableSpeed);
}