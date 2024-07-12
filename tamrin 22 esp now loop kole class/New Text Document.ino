#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress[] = { 0xC8, 0xC9, 0xA3, 0x5D, 0x6B, 0xC9 };
// uint8_t rec[] = {0xA0, 0xA3, 0xB3, 0x30, 0xFD, 0x38};
uint8_t rec[] = {0xA4, 0xCF, 0x12, 0xF1, 0xF7, 0x75};
uint8_t broadcastAddress[] = {0xA0, 0xA3, 0xB3, 0x30, 0xFD, 0x38};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char ID[200];
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {

    if(mac[0]==rec[0]&&mac[1]==rec[1]&&mac[2]==rec[2]&&mac[3]==rec[3]&&mac[4]==rec[4]&&mac[5]==rec[5]){
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Char: ");
    Serial.println(myData.ID);
    Serial.println();
    // strcat(myData.a, "/25")
    strncat(myData.ID, "25/", sizeof(myData.ID) - strlen(myData.ID) - 1);  // Prevent buffer overflow
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

    if (result == ESP_OK) {
      Serial.println("Sent with success");
    } else {
      Serial.println("Error sending the data");
    }
    }
}
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
 }