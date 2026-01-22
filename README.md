# Smart Water Level & Water Quality Monitoring System  
### ESP32 + Blynk Console

![ESP32](https://img.shields.io/badge/ESP32-IoT-blue)
![Blynk](https://img.shields.io/badge/Blynk-Cloud-green)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-blue)
![License](https://img.shields.io/badge/License-MIT-yellow)
![Status](https://img.shields.io/badge/Status-Active-success)

---

## 📌 Project Summary

The **Smart Water Level & Water Quality Monitoring System** is an IoT-based embedded solution designed to **monitor water level in real time**, display it locally on an **OLED screen**, and visualize data remotely using the **Blynk Cloud Console**. The system also generates **alerts using LEDs and a buzzer** when water reaches critical thresholds.

The project is built around the **ESP32 microcontroller**, chosen for its integrated Wi-Fi, processing power, and low energy consumption. While the current implementation focuses on **water level monitoring using an ultrasonic sensor**, the architecture is designed to be **extensible** to support **real-time water quality monitoring** such as **pH, TDS, and turbidity**.

This repository follows **industry-standard documentation and structure**, making it suitable for:
- Academic projects & evaluations  
- Hackathons (SIH, internal ideathons)  
- Prototype & pilot deployments  
- Resume & portfolio demonstration  

---

## 📑 Table of Contents

1. Project Overview  
2. System Architecture & Flow  
3. Hardware Components (BOM)  
4. Wiring & Circuit Diagram  
5. Software Stack & Libraries  
6. Quick Start (5-Minute Setup)  
7. Local Development & Build Instructions  
8. Blynk Console Setup  
9. Calibration & Testing  
10. Data Logging & Analytics  
11. Alerts & Notifications  
12. Water Quality Extension  
13. Deployment & Enclosure Guidelines  
14. Troubleshooting  
15. Security & Privacy  
16. Repository Structure  
17. Contribution Guidelines  
18. Testing & QA  
19. Release & Versioning  
20. FAQ & References  
21. License & Credits  

---

## 1️⃣ Project Overview

### 🎯 Objectives
- Measure **water level accurately** in overhead/underground tanks
- Display level locally and remotely
- Provide **early alerts** to prevent overflow or dry run
- Design a **scalable system** for future water quality monitoring

### ⭐ Core Features
- Real-time water level (%) calculation
- Distance measurement in centimeters
- OLED display for local visualization
- Blynk dashboard for cloud monitoring
- LED & buzzer alert mechanism
- Push-button control for alert mute
- ESP32 Wi-Fi connectivity

### 🚀 Future Scope
- pH, TDS, turbidity monitoring
- Historical data visualization
- Smart pump automation
- Water quality classification
- Predictive analytics

---

## 2️⃣ System Architecture & Flow

### 🔷 High-Level Architecture

**TODO:** Add image  
📁 `assets/diagram-architecture.png`

**Diagram description:**

Ultrasonic / Quality Sensors ↓ ESP32 ↓ OLED Display ─── Buzzer / LEDs ↓ Blynk Cloud ↓ Dashboard ─ Alerts ─ Data Storage

### 🔷 Data Flow Explanation

1. Ultrasonic sensor measures distance to water surface
2. ESP32 converts distance to water level percentage
3. Data is:
   - Displayed on OLED
   - Sent to Blynk via virtual pins
4. Blynk dashboard updates in real time
5. Alerts are triggered if thresholds are crossed

---

## 3️⃣ Hardware Components (BOM)

| Item | Component | Qty | Description |
|----|----|----|----|
| ESP32 | ESP32-WROOM-32 | 1 | Main controller |
| Ultrasonic | HC-SR04 / JSN-SR04T | 1 | Water level sensing |
| OLED | SSD1306 (0.96") | 1 | Display (I2C) |
| TDS Sensor | Analog TDS | 1 | Water conductivity |
| pH Sensor | pH probe + ADC | 1 | Acidity/alkalinity |
| Turbidity | Optical sensor | 1 | Water clarity |
| Buzzer | Active buzzer | 1 | Alert |
| LEDs | Red/Green LEDs | 2 | Status indication |
| Button | Push button | 1 | Alert mute/reset |
| Misc | Wires, PCB/Breadboard | — | Connections |

📄 **TODO:** `docs/bom.csv`

---

## 4️⃣ Wiring & Circuit Diagram

### 🔌 ESP32 Pin Mapping

| ESP32 Pin | Component |
|----|----|
| GPIO 27 | Ultrasonic TRIG |
| GPIO 26 | Ultrasonic ECHO |
| GPIO 14 | LED |
| GPIO 13 | Buzzer |
| GPIO 12 | Push Button |
| SDA / SCL | OLED Display |

**TODO:**
- `assets/wiring-fritzing.png`
- `assets/schematic.png`

⚠️ Notes:
- Use 5V-to-3.3V logic precautions
- Prefer waterproof ultrasonic sensor for tanks

---

## 5️⃣ Software Stack & Libraries

### 🔧 Firmware
- Arduino (ESP32 core)
- PlatformIO (optional)

### 📚 Libraries Used
- `Adafruit_SSD1306`
- `BlynkSimpleEsp32`
- `AceButton`
- `Wire`

### ☁️ Cloud Platform
- **Blynk Console (Blynk.Cloud)**

---

## 6️⃣ Quick Start (5-Minute Setup)

```bash
git clone https://github.com/Indian24/Smart-Water-Quality-Level-Monitoring-System-using-IoT-ESP32-
cd Smart-Water-Quality-Level-Monitoring-System-using-IoT-ESP32-

1. Open WaterLevelMonitor.ino


2. Configure Wi-Fi & Blynk credentials


3. Upload code to ESP32


4. Open Blynk dashboard




---

7️⃣ Local Development & Build Instructions

Arduino IDE

1. Install ESP32 board package


2. Install required libraries


3. Create secrets file



// secrets.h (DO NOT COMMIT)
#define WIFI_SSID "YourSSID"
#define WIFI_PASS "YourPassword"
#define BLYNK_TOKEN "YourToken"

PlatformIO

[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino


---

8️⃣ Blynk Console Setup

Create organization

Create device

Add widgets:

Gauge → V1 (Water Level %)

Value Display → V2 (Distance)



TODO: assets/screenshot-blynk.png


---

9️⃣ Calibration & Testing

Ultrasonic Calibration

Measure tank empty distance

Measure tank full distance

Update code constants


Water Quality Calibration

pH buffer (4, 7, 10)

TDS standard solution

Turbidity reference samples



---

🔟 Data Logging & Analytics (Optional)

Blynk Webhooks

MQTT + Node-RED

InfluxDB + Grafana



---

1️⃣1️⃣ Alerts & Notifications

Local: buzzer & LED

Cloud: Blynk push notifications

Threshold-based alerts



---

1️⃣2️⃣ Water Quality Extension

Sensors

pH

TDS

Turbidity


Sample Logic

If pH 6.5–8.5 AND TDS < 500 AND Turbidity < 5
→ Water = GOOD
Else → ALERT


---

1️⃣3️⃣ Deployment & Enclosure Guidelines

IP65 enclosure

Vertical ultrasonic mounting

Buck converter for 12V tanks

Optional solar power



---

1️⃣4️⃣ Troubleshooting

Issue	Cause	Solution

No data	Wi-Fi issue	Check credentials
Zero reading	Sensor misalignment	Re-mount
Fluctuations	Noise	Add averaging



---

1️⃣5️⃣ Security & Privacy

Never commit secrets

Use .gitignore

Use GitHub PAT or SSH

Minimal data retention



---

1️⃣6️⃣ Repository Structure

/
├─ README.md
├─ code/
│  ├─ WaterLevelMonitor.ino
│  └─ platformio.ini
├─ docs/
│  ├─ calibration.md
│  └─ deployment.md
├─ assets/
│  ├─ diagram-architecture.png
│  ├─ wiring-fritzing.png
│  └─ screenshot-blynk.png
├─ hardware/
│  └─ PCB_files/
├─ .gitignore
└─ LICENSE


---

1️⃣7️⃣ Contribution Guidelines

Branch naming:

feature/<name>

fix/<issue>



Sample Commit

feat: add water quality sensor integration


---

1️⃣8️⃣ Testing & QA

Unit testing (sensor validation)

Integration testing (ESP32 → Blynk)

Hardware-in-the-loop testing



---

1️⃣9️⃣ Release & Versioning

Semantic versioning


git tag v1.0.0
git push origin v1.0.0


---

2️⃣0️⃣ FAQ & References

Q: Can it work offline?
A: Yes, OLED and buzzer still function locally.

References

ESP32 Datasheet

Blynk Documentation

Adafruit SSD1306 Library



---

📜 License & Credits

License

MIT License

Credits

ESP32 Community

Blynk Team

Adafruit Libraries


