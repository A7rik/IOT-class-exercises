
float getHumadity() {
  float humad=random(0,100);
  return humad;
}

float getTemp() {
  float temp=random(0,100);
  return temp;
}

void setup(void){
  randomSeed(analogRead(0));
  Serial.begin(115200);
}

void loop(void){
  int humd= getHumadity();
  int temp= getTemp();

  Serial.println(humd);
  Serial.println(temp);

  delay(500);         
}