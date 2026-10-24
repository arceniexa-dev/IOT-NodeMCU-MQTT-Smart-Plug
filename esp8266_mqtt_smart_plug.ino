#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

// ---------------- MQTT topics ----------------
String base_topic     = String("home/") + DEVICE_ID;
String command_topic;   // subscribe: "ON" / "OFF" / "TOGGLE"
String state_topic;     // publish (retained): "ON" / "OFF"
String status_topic;    // LWT: "online" / "offline"

WiFiClient espClient;
PubSubClient client(espClient);

// ---------------- Relay state ----------------
bool relayState = false;  // false = OFF, true = ON

// ---------------- Relay helpers ----------------
void applyRelay(bool on) {
  relayState = on;
#if RELAY_ACTIVE_HIGH
  digitalWrite(RELAY_PIN, on ? HIGH : LOW);
#else
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);
#endif
}

void publishState() {
  if (!client.connected()) return;
  client.publish(state_topic.c_str(), relayState ? "ON" : "OFF", true);
}

// ---------------- WiFi ----------------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MQTT callback ----------------
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim();
  message.toUpperCase();

  Serial.print("Command received [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  if (String(topic) != command_topic) return;

  if (message == "ON") {
    applyRelay(true);
  } else if (message == "OFF") {
    applyRelay(false);
  } else if (message == "TOGGLE") {
    applyRelay(!relayState);
  } else {
    Serial.println("Unknown command");
    return;
  }

  publishState();
}

// ---------------- MQTT reconnect ----------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = String("ESP8266-") + DEVICE_ID;

    // Last Will: "offline" retained
    bool ok = client.connect(
      clientId.c_str(),
      MQTT_USERNAME, MQTT_PASSWORD,
      status_topic.c_str(), 1, true, "offline"
    );

    if (ok) {
      Serial.println("connected");
      client.publish(status_topic.c_str(), "online", true);
      client.subscribe(command_topic.c_str());
      publishState();  // restore last known state
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5s");
      delay(5000);
    }
  }
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);

  command_topic = base_topic + "/command";
  state_topic   = base_topic + "/state";
  status_topic  = base_topic + "/status";

  pinMode(RELAY_PIN, OUTPUT);
  applyRelay(false);  // start OFF for safety

  setup_wifi();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
}

// ---------------- Main loop ----------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
