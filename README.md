# 🤖Pick and Place Robot (Manual Control)

Zengrip is a manually controlled pick and place robotic system built with affordability and modularity in mind. Designed as part of a robotics exploration project, this bot uses **PLA and acrylic-based mechanical structures**, **DC and servo motors**, and is controlled using **ESP32 (Bluetooth)** for manual operation via a custom interface.

---

## 🚀 Features

- 🎮 **Manual Remote Control** (via Wi-Fi and Bluetooth)
- 🤲 **Gripper Mechanism** for object pickup and release
- ⚙️ **3D Printed Arm and Frame** (PLA + Acrylic)
- 🔌 **ESP32 WROOM-based Control System**
- 🔧 Built with affordability and expandability in mind

---

## 🛠️ Hardware Components

| Component              | Description                              |
|------------------------|------------------------------------------|
| Microcontroller        | ESP32 WROOM                              |
| Motor Drivers          | L298N / L293D                             |
| Motors (Drive)         | 4 × N20 6V 100RPM DC Motors               |
| Gripper Servo          | SG90 Servo Motor                         |
| Frame Material         | PLA (3D Printed) + Acrylic (for gripper and body) |
| Power Supply           | Li-ion battery pack / USB                |
| Control Interface      | Webpage buttons (Wi-Fi) / Bluetooth App  |
| Sensors                | Sharp IR Sensor (optional for autonomy)  |

---

## 🔧 Mechanical Design

- Designed in **Autodesk Fusion 360**
- **4-Wheel Drive Base** with steering bar (optional servo mechanism)
- **Acrylic Gripper Arm** mounted on PLA frame
- Lightweight chassis (≤ 500g) for mobility

---

## 🧠 Control Modes
**Bluetooth Control**  
   - Uses serial communication with mobile apps (like Serial Bluetooth Terminal)  
   - Button-based movement and grip control  

---

## 🖥️ Code Overview

- Written in **Arduino IDE**  
- Key functionalities:
  - Drive motor control via L298N
  - Servo control for gripper
  - Web server for Wi-Fi interface
  - Bluetooth command parser

> Code is modular and easy to extend for autonomous upgrades (wall-following, line following, etc.)

---
