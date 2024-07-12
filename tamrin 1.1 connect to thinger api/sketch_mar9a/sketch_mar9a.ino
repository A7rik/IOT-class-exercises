#define THINGER_SERIAL_DEBUG

#include <ThingerESP32.h>
#include "arduino_secrets.h"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define LED_BUILTIN 2
void setup() {
  // open serial for debugging
  Serial.begin(115200);
  
  thing.add_wifi(SSID, SSID_PASSWORD);  

  pinMode(LED_BUILTIN, OUTPUT);
  thing["Ayrik "]<<[](pson & in){
    if(in.is_empty()){
      in=(bool) digitalRead(LED_BUILTIN);
    }
    else{
      digitalWrite(LED_BUILTIN, in ? HIGH : LOW);
    }
  };

}

void loop() {
  thing.handle();
}