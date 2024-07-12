#include<EEPROM.h>
long lastms;
byte h=0,m=0,s=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.begin(256);
  h=EEPROM.read(0);
  m=EEPROM.read(1);
  s=EEPROM.read(2);
 lastms=millis();

}

void loop() {

  // put your main code here, to run repeatedly:
 if(millis()-lastms>=1000){
       s++;
       EEPROM.write(2,s);
       EEPROM.commit();
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