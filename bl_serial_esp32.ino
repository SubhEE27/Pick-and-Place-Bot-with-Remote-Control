#include "BluetoothSerial.h"

#define TX_PIN 17  // ESP32 TX -> Arduino RX (Pin 2)
#define RX_PIN 16 // ESP32 RX -> Arduino TX (Pin 3)

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // Serial communication with Arduino
  SerialBT.begin("ESP32_Motor_Control");

  Serial.println("Bluetooth device started, ready to pair!");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('#'); // Read command until '#' character
    Serial.print("Received over Bluetooth: ");
    Serial.println(command);

    if (command == "F" || command == "B" || command == "S" || command == "R" || command == "L") {
      sendSerialCommand(command);
    }
    else if (command.startsWith("ARM")) {
      int angleA = command.substring(3).toInt();  // Extracts the number
      sendSerialCommand(command);  // Send full "ARM120" to Arduino
      Serial.print("Setting ARM to: ");
      Serial.println(angleA);
    }
    else if (command.startsWith("GRIP")) {
      int angleG = command.substring(4).toInt();  // Extracts the number
      sendSerialCommand(command);  // Send full "GRIP120" to Arduino
      Serial.print("Setting GRIP to: ");
      Serial.println(angleG);
    }
  }
}

void sendSerialCommand(String command) {
  Serial2.println(command);  // Send command to Arduino via Serial2
  Serial.print("Sent command: ");
  Serial.println(command);
}
