# IOT-NodeMCU-MQTT-Smart-Plug
Wi-Fi smart plug using ESP8266 NodeMCU and relay module, controlled via MQTT. Subscribe to command topics, publish relay state, and integrate with any MQTT dashboard or home automation system.
# ESP8266 MQTT Smart Plug

Wi-Fi smart plug / smart switch based on **NodeMCU ESP8266** and a **relay module**, controlled via **MQTT**.

## Features

- 🔌 Control AC appliance ON/OFF via MQTT
- 📡 Publish relay state to MQTT (retained)
- 🔁 Auto-reconnect on Wi-Fi/MQTT disconnect
- 📊 Last Will and Testament (LWT) for online/offline status
- 🧩 Simple topic structure, compatible with Home Assistant / Node-RED / any MQTT dashboard

## Hardware

| Component | Pin |
|-----------|-----|
| Relay IN | D1 (GPIO5) |
| Relay VCC | 3.3V |
| Relay GND | GND |

> ⚠️ **Safety Warning:** The relay switches mains AC voltage. Ensure proper isolation and never touch the AC side while powered.

## Quick Start

1. Copy `config.example.h` → `config.h`
2. Fill in Wi-Fi and MQTT credentials
3. Open `esp8266_mqtt_smart_plug.ino` in Arduino IDE
4. Install libraries:
   - `PubSubClient` (Nick O'Leary)
   - ESP8266 core (Board Manager URL: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`)
5. Select board: **NodeMCU 1.0 (ESP-12E Module)**
6. Upload

## MQTT Topics

See [docs/MQTT_TOPICS.md](docs/MQTT_TOPICS.md).

## Security

⚠️ Never commit `config.h` — it is git-ignored.

## License

MIT
