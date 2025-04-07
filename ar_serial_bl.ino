#include <Servo.h>

int motor1_1=4;
int motor1_2=5;
int motor2_1=8;
int motor2_2=9;
int EN=6;
int EN2=10;
int ArmS=3;
int GripS=11;

Servo myServoA;
Servo myServoG;

void setup() {
  Serial.begin(9600);  // Default Serial on pins 0 (RX) and 1 (TX)

  pinMode(motor1_1,OUTPUT);
  pinMode(motor1_2,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(motor2_1,OUTPUT);
  pinMode(motor2_2,OUTPUT);
  pinMode(EN2,OUTPUT);
  
  myServoA.attach(ArmS);
  myServoG.attach(GripS);

  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,LOW);

  Serial.println("Arduino ready to receive commands from ESP32.");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Read command from ESP32
    command.trim();
    
    Serial.print("Received Command: ");
    Serial.println(command);
    
    if (command == "F") {
      moveForward();
    } else if (command == "B") {
      moveBackward();
    } else if (command == "L") {
      moveLeft();
    } else if (command == "R") {
      moveRight();
    } else if (command == "S") {
      stopMotors();
    }
    else if (command.startsWith("ARM")) {  // Check for ARM command
      int angleA = command.substring(3).toInt(); // Extract the angle
      servoARM(angleA);
    }
    // else if (command == "STOP") {  // Check for ARM command
    //   int angleA = command.substring(3).toInt(); // Extract the angle
    //   ARMstop();
    // }
    // else if (command == "ARMre") {  // Check for ARM command
    //   int angleA = command.substring(3).toInt(); // Extract the angle
    //   ARMre();
    // }
    else if (command.startsWith("GRIP")) {  // Check for GRIP command
      int angleG = command.substring(4).toInt(); // Extract the angle
      servoGRIP(angleG);
    }
  }
}

void moveForward(){
  
  Serial.println("Moving Forward");
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,HIGH);
  analogWrite(EN,255);
  analogWrite(EN2,255);

}

void moveBackward(){
  Serial.println("Moving Backward");
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor2_2,LOW);
  digitalWrite(motor2_1,HIGH);
  analogWrite(EN,255);
  analogWrite(EN2,255);

}

void stopMotors(){
  Serial.println("Stopping");
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor2_2,LOW);
  digitalWrite(motor2_1,LOW);
}

void moveRight(){       
  Serial.println("Turning Right (Pivot Turn)");
  digitalWrite(motor1_1, HIGH);  // Right motor forward
  digitalWrite(motor1_2, LOW);
  digitalWrite(motor2_1, LOW);   // Left motor backward
  digitalWrite(motor2_2, HIGH);
  analogWrite(EN, 150);
  analogWrite(EN2, 150);
}

void moveLeft(){        
  Serial.println("Turning Left (Pivot Turn)");
  digitalWrite(motor1_1, LOW);   // Right motor backward
  digitalWrite(motor1_2, HIGH);
  digitalWrite(motor2_1, HIGH);  // Left motor forward
  digitalWrite(motor2_2, LOW);
  analogWrite(EN, 150);
  analogWrite(EN2, 150);
}

void servoARM(int angleA) {                 
  //vStep = constrain(step, 0, 180);
  myServoA.write(angleA);
  Serial.print("ARM set to: ");
  Serial.println(angleA);
}

void servoGRIP(int angleG) {                 
  //vStep = constrain(step, 0, 180);
  myServoG.write(angleG);
  Serial.print("GRIP set to: ");
  Serial.println(angleG);
}
// void ARMstop(){
//   myServoA.write(90);
//   Serial.println("ARM Stopped ");
// }
// void ARMre(){
//   myServoA.write(100);
//   Serial.println("ARM Reversed ");
// }