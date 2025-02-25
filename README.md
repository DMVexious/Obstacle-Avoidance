# Arduino Obstacle Avoidance Robot

This repository contains the Arduino code for an obstacle-avoidance robot using ultrasonic sensors. The robot detects obstacles in its path and navigates efficiently to avoid collisions.

## Features
- Uses ultrasonic sensors to detect obstacles.
- Adjusts movement to navigate around objects.
- Optimized for speed and efficiency.

## Hardware Requirements
- **Arduino Uno** (or compatible board)
- **HC-SR04 Ultrasonic Sensors** (minimum 2, recommended 3 for better accuracy)
- **Motor Driver Module** (L298N or similar)
- **DC Motors with Wheels**
- **Power Supply** (Battery pack or USB power)
- **Jumper Wires**
- **Chassis for the robot**

## Installation
1. Install the **Arduino IDE** from [Arduino's official website](https://www.arduino.cc/en/software).
2. Connect the **Arduino board** to your computer using a USB cable.
3. Clone this repository:
   ```sh
   git clone https://github.com/DMVexious/Obstacle-Avoidance.git
   ```
4. Open `New.ino` in Arduino IDE.
5. Select the correct **Board** and **Port** from the "Tools" menu.
6. Click **Upload** to flash the code onto the Arduino board.

## Circuit Diagram
Not yet.

## Usage Instructions
- Turn on the robot.
- It will start moving and avoid obstacles based on sensor readings.
- If an obstacle is detected, it will take corrective actions based on programmed logic.

## Customization
- Adjust the sensor threshold values in the code to fine-tune obstacle detection.
- Modify motor speed settings for different terrains.
- Experiment with different movement strategies for improved navigation.

## Troubleshooting
- **Sensor not detecting obstacles?** Check the sensor wiring and ensure it's powered correctly.
- **Robot not moving properly?** Verify motor driver connections and power supply.
- **Code not uploading?** Ensure the correct port and board are selected in Arduino IDE.

---

### To-Do
- Add circuit diagram images.
- Improve obstacle detection algorithms.


