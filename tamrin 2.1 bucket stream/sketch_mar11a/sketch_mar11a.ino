#include <cstdlib>
#define THINGER_SERIAL_DEBUG

#include <ThingerESP32.h>
#include "arduino_secrets.h"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {

  Serial.begin(115200);
  randomSeed(analogRead(0));
  thing.add_wifi(SSID, SSID_PASSWORD);  

}
void loop() {
  thing["TempHum"] >> [](pson &out){
  out["temperature"] =  random(0, 100);
  out["humadity"] =  random(0, 100); 
  }; 
  thing.handle();
  thing.stream("TempHum");
  /////////////////
  if(random(0, 100)>30)
     thing.write_bucket("writebucket", "TempHum");

  delay(2000);   
}
