#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Right Motors
int motorR1_fw = 3;
int motorR1_bw = 4;
int motorR2_fw = 5;
int motorR2_bw = 6;
int EN1 = 2;
int EN2 = 8;

// Left Motors
int motorL1_fw = 8;
int motorL1_bw = 10;
int motorL2_fw = 11;
int motorL2_bw = 12;
int EN3 = 2;
int EN4 = 8;

// Stepper Motor
int SMotor = 33;

// Frequency and Resolution for DC Motors
int freqM = 5000;
int resM = 8;

// Arm Servo
int servoA = 9;

// Gripper Servo
int servoG = 15;

// Frequency and Resolution of Servo
int freqS = 50;
int resS = 12;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SNATCHO_BOT"); // Bluetooth device name
  Serial.println("Bluetooth Started. Waiting for connection...");

  // Motor setup
  ledcAttach(EN1, freqM, resM);
  ledcAttach(EN2, freqM, resM);
  pinMode(motorR1_fw, OUTPUT);
  pinMode(motorR1_bw, OUTPUT);
  pinMode(motorR2_fw, OUTPUT);
  pinMode(motorR2_bw, OUTPUT);

  ledcAttach(EN3, freqM, resM);
  ledcAttach(EN4, freqM, resM);
  pinMode(motorL1_fw, OUTPUT);
  pinMode(motorL1_bw, OUTPUT);
  pinMode(motorL2_fw, OUTPUT);
  pinMode(motorL2_bw, OUTPUT);

  ledcAttach(servoA, freqS, resS);
  ledcAttach(servoG, freqS, resS);
  ledcAttach(SMotor, freqM, resM);
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();
    Serial.println("Command received: " + command);

    if (command.startsWith("LEFT")) {
      int pwmLeft = command.substring(5).toInt();
      controlLeftSide(pwmLeft);
    } else if (command.startsWith("RIGHT")) {
      int pwmRight = command.substring(6).toInt();
      controlRightSide(pwmRight);
    } else if (command.startsWith("MOVE")) {
      int pwmMove = command.substring(5).toInt();
      controlMovement(pwmMove);
    } else if (command.startsWith("ARM")) {
      int pwmArm = command.substring(4).toInt();
      controlArm(pwmArm);
    } else if (command.startsWith("GRIPPER")) {
      int pwmGripper = command.substring(8).toInt();
      controlGripper(pwmGripper);
    } else if (command.startsWith("STEPPER")) {
      int pwmStepper = command.substring(8).toInt();
      controlStepper(pwmStepper);
    }
  }
}

void controlLeftSide(int pwmLeft) {
  digitalWrite(motorL1_fw, HIGH);
  digitalWrite(motorL1_bw, LOW);
  ledcWrite(EN3, pwmLeft);
  digitalWrite(motorL2_fw, HIGH);
  digitalWrite(motorL2_bw, LOW);
  ledcWrite(EN4, pwmLeft);
}

void controlRightSide(int pwmRight) {
  digitalWrite(motorR1_fw, HIGH);
  digitalWrite(motorR1_bw, LOW);
  ledcWrite(EN1, pwmRight);
  digitalWrite(motorR2_fw, HIGH);
  digitalWrite(motorR2_bw, LOW);
  ledcWrite(EN2, pwmRight);
}

void controlMovement(int pwmMove) {
  controlLeftSide(pwmMove);
  controlRightSide(pwmMove);
}

void controlArm(int pwmArm) {
  ledcWrite(servoA, pwmArm);
}

void controlGripper(int pwmGripper) {
  ledcWrite(servoG, pwmGripper);
}

void controlStepper(int pwmStepper) {
  ledcWrite(SMotor, pwmStepper);
}
