#include <Wire.h>
#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);  // Motor connected

void setup() {
  // Wire.begin(8);            // I2C slave address
  // Wire.onReceive(receiveEvent);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);     // Motor speed (0-255)
  
  Serial.begin(9600);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(1000);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(1000);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1000);

  motor1.run(FORWARD);
  motor2.run(RELEASE);
  motor4.run(FORWARD);
  motor3.run(RELEASE);
  delay(1000);

  motor1.run(RELEASE);
  motor2.run(FORWARD);
  motor4.run(RELEASE);
  motor3.run(FORWARD);
  delay(1000);
}

// void receiveEvent(int bytes) {
//   if (Wire.available()) {
//     String command = "";
//     while (Wire.available()) {
//       char c = Wire.read();
//       command += c;   // Store the full command as a string
//     }

//     if (command == "F") {
//       Serial.print("Received: ");
//       Serial.println(command);
//       moveForward();
//     } 
//     else if (command == "B") {
//       Serial.print("Received: ");
//       Serial.println(command);
//       moveBackward();
//     } 
//     else if (command == "S") {
//       Serial.print("Received: ");
//       Serial.println(command);
//       stopMotors();
//     } 
//     else if (command == "R") {
//       Serial.print("Received: ");
//       Serial.println(command);
//       moveRight();
//     }
//     else if (command == "L") {
//       Serial.print("Received: ");
//       Serial.println(command);
//       moveLeft();
//     }
//     // else if (command.startsWith("ARM")) {  // Check for ARM command
//     //   int angleA = command.substring(3).toInt(); // Extract the angle
//     //   servoARM(angleA);
//     // }
//     // else if (command.startsWith("GRIP")) {  // Check for GRIP command
//     //   int angleG = command.substring(4).toInt(); // Extract the angle
//     //   servoGRIP(angleG);
//     // }
//   }
// }
//  void moveForward(){

//   motor1.run(FORWARD);
//   motor2.run(FORWARD);
//   motor3.run(FORWARD);
//   motor4.run(FORWARD);
// }

// void moveBackward(){
  
//   motor1.run(BACKWARD);
//   motor2.run(BACKWARD);
//   motor3.run(BACKWARD);
//   motor4.run(BACKWARD);
// }

// void stopMotors(){
//   motor1.run(RELEASE);
//   motor2.run(RELEASE);
//   motor3.run(RELEASE);
//   motor4.run(RELEASE);
// }

// void moveRight(){       //Left Motors ON 1 and 4
  
//   motor1.run(FORWARD);
//   motor2.run(RELEASE);
//   motor4.run(FORWARD);
//   motor3.run(RELEASE);
// }

// void moveLeft(){        //Right Motors ON 2 and 3
 
//   motor1.run(RELEASE);
//   motor2.run(FORWARD);
//   motor4.run(RELEASE);
//   motor3.run(FORWARD);
// }

// // void servoARM(int angleA) {                 
// //   //vStep = constrain(step, 0, 180);
// //   myServoA.write(angleA);
// //   Serial.print("ARM set to: ");
// //   Serial.println(angleA);
// // }

// // void servoGRIP(int angleG) {                 
// //   //vStep = constrain(step, 0, 180);
// //   myServoG.write(angleG);
// //   Serial.print("GRIP set to: ");
// //   Serial.println(angleG);
// // }