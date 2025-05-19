# 💧 Water Level Monitoring System

An IoT-based smart water level monitoring and control system using **NodeMCU (ESP8266)**, **ultrasonic sensor**, **LED indicators**, **LCD display**, and **Blynk app**. The system continuously measures the tank’s water level and automatically turns **OFF the water pump** when the tank is full. Users can monitor the real-time level remotely through the Blynk app.

---

## 📦 Features

- 📲 **Blynk Integration**: Real-time water level monitoring on a mobile app
- 💡 **LED Indicators**: 5-step LED display to visually indicate current water level
- ⚡ **Automatic Pump Control**: Relay-controlled motor automatically turns off at high water level
- 📟 **LCD Display**: Optional on-device display showing water level percentage

---

## 🛠️ Tech Stack

- **Microcontroller**: NodeMCU ESP8266  
- **Sensor**: HC-SR04 Ultrasonic Sensor  
- **Actuators**: Relay Module, LED Indicators  
- **Communication**: Wi-Fi via ESP8266  
- **Cloud Platform**: Blynk IoT  
- **Display**: 16x2 LCD with I2C (optional)  
- **Language**: C++ (Arduino IDE)

---

## 🔧 Hardware Components

- NodeMCU ESP8266 Board  
- HC-SR04 Ultrasonic Sensor  
- 5 × LEDs (Red, Yellow, Green)  
- 5 × 220Ω Resistors  
- Relay Module (for controlling water pump)  
- 16x2 LCD Display + I2C Module (optional)  
- Breadboard + Jumper wires  
- Wi-Fi connection

---

## 🖼️ Circuit Diagram

https://github.com/jahnavii-25/Water-Level-Monitoring/blob/main/Circuit%20Diagram.png

---

## 🧠 How It Works

- The ultrasonic sensor measures the distance from the sensor to the water surface.
- This distance is converted into a water level percentage (0–100%).
- Based on the level:
  - LEDs turn on incrementally (e.g., Very Low to Full).
  - Water level is sent to the Blynk app and displayed on the mobile dashboard.
  - If level reaches **85% or more**, the pump is automatically **turned OFF** via the relay.
  - If level is **below 20%**, the pump is turned **ON** again.
- All logic runs autonomously without manual intervention.

---

## 📱 Blynk Configuration

- **Template ID**: `TMPL39Uso7HJ0`  
- **Template Name**: `Water Level Monitoring System`  
- **Auth Token**: *(Replace with your own token)*  
- **Virtual Pins**:  
  - `V0` – Displays current water level %  
  - `V3` – Shows pump ON/OFF status

---

## 🚀 Getting Started

1. Install **Arduino IDE** and set up the ESP8266 board support.
2. Install required libraries:
   - `Blynk`
   - `ESP8266WiFi`
   - `LiquidCrystal_I2C` (if using LCD)
3. Replace the Wi-Fi credentials and Blynk token in the code:
   ```cpp
   char auth[] = "YourAuthToken";
   char ssid[] = "YourWiFiSSID";
   char pass[] = "YourWiFiPassword";

## 🌍 Applications

This water level monitoring system can be applied in various real-world scenarios:

- 🏠 **Home Water Tank Automation**: Automatically turns off the motor when the tank is full, preventing overflow and saving electricity.
- 🏢 **Apartments and Societies**: Centralized monitoring and control of water tanks with real-time updates via Blynk.
- 🌾 **Agricultural Irrigation**: Automates pump control for borewells or irrigation tanks based on water levels.
- 🏫 **Institutes and Campuses**: Used to manage water usage efficiently in schools, colleges, and hostels.
- 🏭 **Industrial Use**: Monitors and controls liquid levels in storage tanks in small-scale industrial applications.
