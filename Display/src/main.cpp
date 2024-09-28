#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisiere das LCD-Display (Adresse: 0x27, 16 Zeichen, 2 Zeilen)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Falls deine LCD-Adresse anders ist, passe sie hier an

// Struktur für empfangene Daten (muss mit dem Sender übereinstimmen)
typedef struct test_struct {
  float distance;  // Empfange nur die Distanz
} test_struct;

// Erstelle eine Struktur für empfangene Daten
test_struct myData;
// Funktion zur Aktualisierung des LCD-Displays
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);  // Setze den Cursor in die erste Zeile
  lcd.print("Distance:");
  lcd.setCursor(0, 1);  // Setze den Cursor in die zweite Zeile
  lcd.print(myData.distance);  // Zeige die empfangene Distanz an
  lcd.print(" cm");
}
// Callback-Funktion, die ausgeführt wird, wenn Daten empfangen werden
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  // Ausgabe auf dem seriellen Monitor
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distance: ");
  Serial.print(myData.distance);
  Serial.println(" cm");
  
  // Aktualisiere das LCD-Display mit den empfangenen Werten
  updateDisplay();
}



void setup() {
  // Initialisiere den seriellen Monitor
  Serial.begin(115200);

  // Initialisiere das LCD-Display
  lcd.init();
  lcd.backlight();

  // Setze das ESP32 als Wi-Fi-Station
  WiFi.mode(WIFI_STA);

  // Initialisiere ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Registriere die Callback-Funktion für den Empfang von Daten
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Hier ist keine Aktion notwendig, da alles in der Callback-Funktion OnDataRecv passiert
}
