#include <esp_now.h>
#include <WiFi.h>

// Definiere die Pins für den HC-SR04
#define TRIG_PIN 5  // Pin für den Trigger
#define ECHO_PIN 18 // Pin für das Echo

// MAC-Adresse von Board 2: ac:15:18:ea:9e:08
uint8_t broadcastAddress[] = {0xAC, 0x15, 0x18, 0xEA, 0x9E, 0x08};

// Struktur zur Übermittlung der Sensordaten
typedef struct test_struct {
  float distance; // Entfernungswert
} test_struct;

test_struct test;

esp_now_peer_info_t peerInfo;

// Callback, wenn Daten gesendet wurden
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Kopiere die MAC-Adresse des Empfängers in einen String
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Funktion zur Messung der Entfernung mit dem HC-SR04
float getDistance() {
  // Trigger-Impuls auslösen
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Dauer des Echo-Signals messen
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Berechne die Entfernung basierend auf der Zeit (Schallgeschwindigkeit = 0,034 cm/µs)
  float distance = (duration * 0.034) / 2;

  return distance;
}

void setup() {
  // Initialisiere den seriellen Monitor
  Serial.begin(115200);

  // Pins für den HC-SR04 initialisieren
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  // Setze das ESP32 als Wi-Fi-Station
  WiFi.mode(WIFI_STA);
 
  // Initialisiere ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Registriere die Callback-Funktion für das Senden
  esp_now_register_send_cb(OnDataSent);
   
  // Peer registrieren
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); // Setze die MAC-Adresse von Board 2 ein
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Entfernung mit dem HC-SR04 messen
  test.distance = getDistance();
  
  // Ausgabe der Entfernung auf dem seriellen Monitor
  Serial.print("Measured Distance: ");
  Serial.print(test.distance);
  Serial.println(" cm");
 
  // Sende die Daten über ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &test, sizeof(test_struct));
   
  if (result == ESP_OK) {
    Serial.print("Sent with success. Distance: ");
    Serial.println(test.distance);
  } else {
    Serial.println("Error sending the data");
  }
  
  delay(2000); // Warte 2 Sekunden vor dem nächsten Senden
}
