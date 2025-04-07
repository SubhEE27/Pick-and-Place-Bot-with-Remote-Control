#include <BluetoothSerial.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "realme11Pro";
const char* password = "12345679";

// Web server on port 80
WebServer server(80);

// Bluetooth serial
BluetoothSerial SerialBT;

// Motor and servo pins
int motorR1_fw = 3;
int motorR1_bw = 4;
int motorL1_fw = 8;
int motorL1_bw = 10;
int servoA = 9;
int servoG = 15;

void setup() {
  Serial.begin(115200);

  // Start Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Start Bluetooth
  SerialBT.begin("SNATCHO_BOT");
  Serial.println("Bluetooth Started. Waiting for connection...");

  // Set up web server routes
  server.on("/forward", [](){ sendCommand("MOVE 255"); });
  server.on("/backward", [](){ sendCommand("MOVE -255"); });
  server.on("/left", [](){ sendCommand("LEFT 255"); });
  server.on("/right", [](){ sendCommand("RIGHT 255"); });
  server.on("/arm_up", [](){ sendCommand("ARM 180"); });
  server.on("/arm_down", [](){ sendCommand("ARM 0"); });
  server.on("/grip_open", [](){ sendCommand("GRIPPER 180"); });
  server.on("/grip_close", [](){ sendCommand("GRIPPER 0"); });

  server.begin();
}

void loop() {
  server.handleClient();
}

void sendCommand(String command) {
  SerialBT.println(command);
  server.send(200, "text/plain", "Command sent: " + command);
}
