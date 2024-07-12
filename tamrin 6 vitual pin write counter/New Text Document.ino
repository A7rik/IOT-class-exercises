#include<EEPROM.h>
#define BLYNK_TEMPLATE_ID           "TMPL5g027MNsX"
#define BLYNK_TEMPLATE_NAME         "LEDBlink"
#define BLYNK_AUTH_TOKEN            "dxpmrDYoRW-2epyyX8iSDQ1zmkZHTyZi"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";
long lastms;
byte h=0,m=0,s=0;
void setup() {
  Serial.begin(9600);
  EEPROM.begin(256);
  h=EEPROM.read(0);
  m=EEPROM.read(1);
  s=EEPROM.read(2);
 lastms=millis();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop() {

  Blynk.run();
 if(millis()-lastms>=1000){
       s++;
       EEPROM.write(2,s);
       EEPROM.commit();
      Blynk.virtualWrite(V10, h);
      Blynk.virtualWrite(V11, m);
      Blynk.virtualWrite(V12, s);
       if(s>59){
            m++;
       EEPROM.write(1,m);
            s=0;
       EEPROM.write(0,s);
       EEPROM.commit();
       }
       if(m>59){
            h++;
            EEPROM.write(0,h);
            m=0;
            EEPROM.write(2,m);
       EEPROM.commit();
       }
       lastms=millis();
       Serial.print(h);
       Serial.print(":");
       Serial.print(m);
       Serial.print(":");
       Serial.println(s);
        
 }
}
