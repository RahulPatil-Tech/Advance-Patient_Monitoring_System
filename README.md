# Advance Patient Monitoring System

![Project Banner](https://img.shields.io/badge/status-completed-brightgreen)  
**Developed at Vidyalankar Institute of Technology, Mumbai**  
📅 *Apr 2023 – Mar 2024*

## 🚀 Project Overview

The **Advance Patient Monitoring System** is an IoT-based health monitoring solution designed to provide real-time, non-invasive tracking of vital parameters such as:

- 🫀 **Heart Rate (BPM)**
- 🌡️ **Body Temperature**
- 🩸 **SpO2 (Blood Oxygen Level)**
- 🍬 **Glucose Level** (non-invasive IR-based estimate)

This system aims to enhance the comfort and convenience of patients, particularly diabetics, by eliminating the need for traditional finger-prick tests for glucose monitoring. It features:

- OLED visual feedback
- WiFi connectivity
- ThingSpeak integration for live data streaming
- Button-based mode switching between different health parameters

---

## 📷 Preview

*(You may include images or a short video of your project running here.)*

---

## 🧰 Hardware & Components

- ESP32 / ESP8266 Microcontroller
- Adafruit MLX90614 (IR Temperature Sensor)
- DFRobot MAX30102 (Heart Rate & SpO2 Sensor)
- IR Sensor for glucose level approximation
- OLED Display (SSD1306)
- Push Button
- WiFi Connection
- ThingSpeak API for data logging

---

## 📂 Project Structure

AdvancePatientMonitoring/ </br>
  │
  ├── src/ </br>
  │    └── main.ino </br>
  ├── README.md </br>


---

## 🔧 Features

- 👨‍⚕️ Real-time vitals monitoring
- 📡 Wireless data logging to ThingSpeak
- 🖥️ OLED display output for each parameter
- 🧠 Non-invasive glucose level estimation using IR sensor
- 🔘 Button-controlled mode cycling (BPM → Glucose → Temp → SpO2)

---

## 🧰 Hardware & Components

- ✅ **ESP32 / ESP8266 Microcontroller**
- 🌡️ **Adafruit MLX90614** (IR-based Temperature Sensor)
- ❤️ **DFRobot MAX30102** (SpO2 and Heart Rate Sensor)
- 🍬 **IR Sensor** for glucose estimation
- 🖥️ **OLED Display** (SSD1306 compatible)
- 🔘 **Push Button** for mode switching
- 📶 **WiFi Connection** for ThingSpeak API
- 🔌 Breadboard, jump wires, power source

---

## 🛠️ How It Works

Each health metric is mapped to a mode on the device. Using a push button, users can cycle between:

1. **Heart Rate Mode (field1)** – Measured using the MAX30102 sensor.
2. **Glucose Estimation (field2)** – Based on analog IR sensor reading (mapped to a glucose scale).
3. **Body Temperature (field3)** – Read from the MLX90614 IR thermometer.
4. **SpO2 Mode (field4)** – Calculated via the MAX30102.

Each reading is shown on an OLED display and pushed to ThingSpeak for remote access and visualization.

---

## 📶 ThingSpeak Integration

| Field   | Parameter                    |
|---------|------------------------------|
| field1  | Heart Rate (BPM)             |
| field2  | IR Sensor Value (Glucose Proxy) |
| field3  | Temperature (°C)             |
| field4  | SpO2 (%)                     |

---

## 🧑‍💻 Getting Started

### 1. Prerequisites

- Arduino IDE installed
- ESP32/ESP8266 board package installed
- ThingSpeak account created

### 2. Upload Code to Microcontroller

1. Open `main.ino` in Arduino IDE
2. Select board (**ESP32** or **ESP8266**) and correct port
3. Install required libraries
4. Upload the sketch

### 3. Required Libraries

Install from **Arduino Library Manager**:

- `Adafruit_GFX`
- `Adafruit_SSD1306`
- `Adafruit_MLX90614`
- `DFRobot_MAX30102`
- `WiFi.h` *(included with ESP32/ESP8266)*

### 4. Configure WiFi & ThingSpeak

In `main.ino`, replace placeholders:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
unsigned long channelID = YOUR_CHANNEL_ID;
char writeAPIKey[] = "YOUR_WRITE_API_KEY";
```

-----

## 🧠 Future Enhancements
We're always looking to improve and expand the capabilities of this system. Here are some planned future enhancements:

- ✅ **Advanced Non-invasive Glucose Monitoring Hardware**: Investigating and integrating more accurate and reliable non-invasive glucose sensing technologies as they mature.
- 📱**Android/iOS App Development**: Creating a dedicated mobile application for seamless real-time health tracking, historical data analysis, and user-friendly interaction.
- 📩 **SMS or Email Alert System**: Implementing automated notifications for caregivers or patients when vital signs exceed predefined healthy thresholds.
- ☁️ **Cloud Database & EHR Integration**: Exploring secure cloud database solutions and potential integration with Electronic Health Record (EHR) systems for comprehensive patient management.
- 📊 **Local Data Storage (SD Card Module)**: Adding an SD card module for offline data logging, useful when WiFi connectivity is intermittent or unavailable.
- ⚡ **Power Optimization**: Implementing advanced power management techniques, such as deep sleep modes, to significantly extend battery life for portable applications. 

---

## 🙌 Contributors
This project was developed with passion and dedication by:

****Rahul Patil****  – Hardware, Software, Integration

****Tejaswi Yelgonda****  – Software Development, UI/UX

****Karuna Padwal****  – Research, Documentation

****Abel D'souza****   – Testing, Debugging

****Komal Shinde****   – Project Guidance and Support

***Vidyalankar Institute of Technology, Mumbai***  – The institution where this project was developed. 

---

## 📃 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

---

## 🌐 Links
- 🔗 [Documentation (optional)](https://drive.google.com/file/d/16HMGW06kHYQN3rumrJIO6_49DiM2XZCQ/view?usp=sharing)
- 🔗 [Buisness Plan](https://drive.google.com/file/d/1qhWqfrWm_Aeyf7ocscaptGyd1arihvFN/view?usp=drive_link)

---

## 🩺 Empowering Smarter Healthcare

Improving patient comfort and health outcomes through smarter, continuous, and non-intrusive monitoring technology.

---


