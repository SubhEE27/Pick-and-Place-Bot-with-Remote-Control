#include <Wire.h>
#include "BluetoothSerial.h"

#define ARDUINO_ADDRESS 8

//int Aservo=19;
//int Gservo=18;
//int freqS=50;
int res=8;
//int res2=12;
int Bmotor=15;
int freqM=1000;
int mSpeed=80;

BluetoothSerial SerialBT;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  SerialBT.begin("ESP32_Motor_Control");
  Serial.println("Bluetooth device started, ready to pair!");
  
  // ledcAttach(Aservo,freqS,res2);
  // ledcAttach(Gservo,freqS,res2);
  ledcAttach(Bmotor,freqM,res);
  
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('#'); // Read command until '#' character
    Serial.print("Received over Bluetooth: ");
    Serial.println(command);
    if(command== "F" || command=="B" || command=="S" || command=="R" || command=="L"){
      sendI2CCommand(command);
    }
    // else if (command.startsWith("ARM")) {
    //   int angleA = command.substring(3).toInt();  // Extracts the number
    //   sendI2CCommand(command);  // Send full "ARM120" to Arduino
    //   Serial.print("Setting ARM to: ");
    //   Serial.println(angleA);
    // }
    // else if (command.startsWith("GRIP")) {
    //   int angleG = command.substring(4).toInt();  // Extracts the number
    //   sendI2CCommand(command);  // Send full "GRIP120" to Arduino
    //   Serial.print("Setting GRIP to: ");
    //   Serial.println(angleG);
    // }
    // else if (command == "BASE") {
    //   Serial.println("Motor ON at 30% speed");
    //   ledcWrite(3, mSpeed); // Motor ON at 80% speed
    // } 
    // else if (command == "OFF") {
    //   Serial.println("Motor OFF");
    //   ledcWrite(3, 0); // Motor OFF
    // }
  }
}

void sendI2CCommand(String command) {
  Wire.beginTransmission(ARDUINO_ADDRESS);
  for (int i = 0; i < command.length(); i++) {
    Wire.write(command[i]); // Send each character of the command
  }
  Wire.endTransmission();
  Serial.print("Sent command: ");
  Serial.println(command);
}

// void controlArm(int pwmArm) {
//   ledcWrite(Aservo, pwmArm);
// }

// void controlGrip(int pwmGrip) {
//   ledcWrite(Gservo, pwmGrip);
// }