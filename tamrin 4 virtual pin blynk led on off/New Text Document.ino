#define LED 2
#define BLYNK_TEMPLATE_ID           "TMPL5g027MNsX"
#define BLYNK_TEMPLATE_NAME         "LEDBlink"
#define BLYNK_AUTH_TOKEN            "dxpmrDYoRW-2epyyX8iSDQ1zmkZHTyZi"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";


WidgetLED led1(V3);
void setup() {
  Serial.begin(115200);
  
  pinMode(LED, OUTPUT);


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V3) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
   digitalWrite(LED, HIGH); // Turn LED on.
  } else {
   digitalWrite(LED, LOW); // Turn LED off.
 }
}
