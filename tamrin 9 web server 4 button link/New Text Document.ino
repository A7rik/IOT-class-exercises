#include <WiFi.h>

const char* ssid     = "your_SSID";
const char* password = "your_Pass";

WiFiServer server(80);// Set port to 80
String header; // This storees the HTTP request

int led = 2;
char temperatureString[6];
float getTemperature() {
  float temp=random(0,100);
  return temp;
}
char humadityString[6];
float getHumadity() {
  float humad=random(0,100);
  return humad;
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();


  

}
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /LED/on") >= 0) {
              Serial.println("led on");
              digitalWrite(led, HIGH);
            } else if (header.indexOf("GET /LED/off") >= 0) {
              Serial.println("led off");
              digitalWrite(led, LOW);
            } 

            if (header.indexOf("GET /newTemp") >= 0) {
              float temperature = getTemperature();
                dtostrf(temperature, 2, 2, temperatureString);
            } else if (header.indexOf("GET /newHu") >= 0) {
                float humad = getTemperature();
                 dtostrf(humad, 2, 2, humadityString);
    
            } 
       
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("body {background-color: #FFE3C6}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".button3 {background-color: #D3664F;}");
            client.println(".button4 {background-color: #2BA5B9;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
              client.println("<p>Ayrik</p>");
              client.println("<p></p>");
              client.println("<p><a href=\"/LED/on\"><button class=\"button\">ON</button></a></p>");
              client.println("<p><a href=\"/LED/off\"><button class=\"button button2\">OFF</button></a></p>");
              client.println("<p><a href=\"/newTemp\"><button class=\"button button3\">Temp</button></a></p>");
              client.println("<p><a href=\"/newHu\"><button class=\"button button4\">humadity</button></a></p>");
            if (header.indexOf("GET /newTemp") >= 0){
              client.println("<h1>Temperature</h1><h3>");
              client.println(temperatureString);
              client.println("</h3>");
            }
             else if (header.indexOf("GET /newHu") >= 0){
              client.println("<h1>Humadity</h1><h3>");
              client.println(humadityString);
              client.println("</h3>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}