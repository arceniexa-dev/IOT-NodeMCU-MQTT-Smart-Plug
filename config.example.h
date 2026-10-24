#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
//  DEVICE IDENTIFICATION
// ============================================================
#define DEVICE_ID     "plug-001"          // unique id for this plug
#define DEVICE_LABEL  "Living Room Lamp"  // human-readable name

// ============================================================
//  WIFI
// ============================================================
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// ============================================================
//  MQTT BROKER
// ============================================================
#define MQTT_SERVER   "mqtt.example.com"
#define MQTT_PORT     1883
#define MQTT_USERNAME "YOUR_MQTT_USER"
#define MQTT_PASSWORD "YOUR_MQTT_PASSWORD"

// ============================================================
//  RELAY PIN
// ============================================================
#define RELAY_PIN     5   // D1 = GPIO5

// ============================================================
//  RELAY LOGIC
// ============================================================
// Some relay modules are active-LOW (LOW = ON).
// Set to 1 if your relay turns ON when pin is HIGH.
// Set to 0 if your relay turns ON when pin is LOW.
#define RELAY_ACTIVE_HIGH 1

#endif // CONFIG_H
