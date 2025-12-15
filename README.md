# 🌡️ ESP32 DHT11 – MQTT Temperature & Humidity Monitoring System

## 📌 General Description

This project is a **temperature and humidity monitoring system** based on the **MQTT protocol**.

It is mainly designed for:

* 🎓 **Students** in embedded systems / IoT
* 🔧 **Enthusiasts** who want to learn MQTT, ESP32, and real‑time monitoring

The system is composed of **three independent but connected parts**:

1. A **Mosquitto MQTT broker** running on Linux (Ubuntu)
2. An **ESP32 + DHT11 sensor** that publishes data
3. A **Web interface** that subscribes to the broker and displays data in real time
4. An optional **Linux script** to display and store received data into a `.log` file

---

## 🧱 System Architecture

![Global system architecture](docs/images/architecture.png)

```
[DHT11] → ESP32 → MQTT → Mosquitto (Linux)
                               ↓
                      Web Interface (MQTT WebSocket)
                               ↓
                         Logger Script (.log)
```

---

## 🐧 Part 1: Linux (Mosquitto MQTT Broker)

### 🔹 Role

The MQTT broker acts as a **central server** that receives data sent by the ESP32 and redistributes it to subscribed clients (web page, scripts, etc.).

### 🔹 Mosquitto Installation (Ubuntu)

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients
```

### 🔹 Verification

```bash
mosquitto -v
```

### 🔹 Enable Mosquitto at Startup

```bash
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

### 🔹 Enable MQTT WebSocket

Edit the configuration file:

```bash
sudo nano /etc/mosquitto/mosquitto.conf
```

Add:

```conf
listener 1883
protocol mqtt

listener 8080
protocol websockets
allow_anonymous true
```

Then restart Mosquitto:

```bash
sudo systemctl restart mosquitto
```

---

## 🔌 Part 2: ESP32 + DHT11

### 🔹 Role

* Read **temperature** and **humidity** from the DHT11 sensor
* Publish values every **2 seconds** to the MQTT broker

### 🔹 MQTT Topics Used

```text
esp32/dht11/temperature
esp32/dht11/humidity
```

### 🔹 Published Data

* Temperature: °C
* Humidity: %

### 🔹 Update Rate

⏱️ Every **2 seconds**

![ESP32 + DHT11 wiring diagram](docs/images/esp32_dht11_wiring.png)

---

## 🌐 Part 3: Web Interface

### 🔹 Role

* Subscribe to MQTT topics
* Display sensor values **in real time**
* Uses **MQTT over WebSocket**

### 🔹 Technologies Used

* HTML / CSS
* JavaScript
* `mqtt.js` library

### 🔹 Features

* Modern UI (dark theme)
* Connection status indicator
* Real‑time updates

![Web interface – real‑time display](docs/images/web_interface.png)

---

## 📜 Part 4: Linux Logger Script

### 🔹 Role

* Subscribe to the same MQTT topics
* Display data in the terminal
* Store received values in a `.log` file

### 🔹 Example Usage

```bash
./dht11_logger.sh
```

### 🔹 Example Log Output

```text
2025-01-10 14:32:01 | Temperature: 25.3 °C | Humidity: 54 %
2025-01-10 14:32:03 | Temperature: 25.4 °C | Humidity: 55 %
```

---

## 🚀 Educational Objectives

* Understand **MQTT** (publish / subscribe)
* Learn **distributed IoT architecture**
* Use **ESP32** with sensors
* Build a **real‑time web interface**
* Work with Linux network services

---

## 🔮 Possible Improvements

* MQTT authentication and security
* Database integration (InfluxDB, SQLite)
* Advanced dashboards (Grafana)
* Alert system (temperature thresholds)
* Support for DHT22 / BME280 sensors

---

## 👤 Author

Project created for **educational and experimental** purposes.

---

## 📄 License

Free for personal and educational use.
