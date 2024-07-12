#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";
const char* password = "pass";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  if (!client.connected()) {
    reconnect();
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.publish("building/floor-1/sensor1", "name");
  client.publish("AyrikRoom/humd", "humd 10");
  client.loop();

}
