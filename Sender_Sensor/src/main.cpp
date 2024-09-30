#include <esp_now.h>
#include <WiFi.h>
#include <esp_sleep.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

uint8_t receiverAddress[] = {0xAC, 0x15, 0x18, 0xEA, 0x9E, 0x08};

typedef struct SensorData {
  float distance;
} SensorData;

SensorData sensorData;
esp_now_peer_info_t peerInfo;
bool dataSent = false;  // Flag zum Prüfen, ob Daten erfolgreich gesendet wurden
int sendAttempts = 0;   // Anzahl der Sendeversuche
const int maxAttempts = 3; // Maximale Anzahl der Sendeversuche

// Callback für gesendete Daten
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send attempt ");
  Serial.print(sendAttempts);
  Serial.print(": ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");

  if (status == ESP_NOW_SEND_SUCCESS) {
    dataSent = true;  // Wenn erfolgreich, setze das Flag auf true
  } else {
    sendAttempts++;   // Erhöhe die Sendeversuchsanzahl bei einem Fehlschlag
  }
}

// Entfernungsmessung mit HC-SR04
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034) / 2;
}

// Daten über ESP-NOW senden
void sendData() {
  sensorData.distance = getDistance();
  Serial.print("Measured Distance: ");
  Serial.println(sensorData.distance);

  esp_now_send(receiverAddress, (uint8_t *) &sensorData, sizeof(sensorData));
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  sendData();  // Erster Sendeversuch
}

void loop() {
  // Prüfe, ob die Daten erfolgreich gesendet wurden oder ob die maximale Anzahl an Versuchen erreicht ist
  if (dataSent || sendAttempts >= maxAttempts) {
    if (dataSent) {
      Serial.println("Data sent successfully. Going to sleep...");
    } else {
      Serial.println("Max attempts reached. Going to sleep...");
    }
    // Gehe in den Deep Sleep Modus für 24 Stunden
    esp_sleep_enable_timer_wakeup(86400000000); // 24 Stunden in Mikrosekunden
    esp_deep_sleep_start();
  } else if (sendAttempts > 0) {
    // Wenn der erste Versuch fehlgeschlagen ist, versuche es erneut
    Serial.print("Retrying to send data (Attempt ");
    Serial.print(sendAttempts + 1);
    Serial.println(")...");
    sendData();
  }
}
