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
int rand = random(0,100);
int flag = 1;
void loop() {
  thing.handle();
if(flag==1 && rand>=50){
     pson data;
     data["name"] ="Ayrik";
     data["humadity"]=6;
    thing.call_endpoint("e1",data);
   flag=0;
}
  }
