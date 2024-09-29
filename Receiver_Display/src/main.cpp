#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisiere das LCD-Display (Adresse: 0x27, 16 Zeichen, 2 Zeilen)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Falls deine LCD-Adresse anders ist, passe sie hier an

// Struktur für empfangene Daten
typedef struct SensorData {
  float distance;  // Empfange nur die Distanz
} SensorData;

SensorData sensorData;

// Variablen für den Tank
const float maxSensorDistance = 60;  // Der Sensor ist 60 cm von der maximalen Füllhöhe entfernt
const float maxWaterHeight = 200;    // Maximale Wasserhöhe 200 cm
const float tankDiameter = 200;      // Tankdurchmesser 200 cm

// Variablen für Zeitmessung
unsigned long lastReceivedTime = 0;
const unsigned long timeout = 172800000;  // Zeit in Millisekunden, nach der "Sensor prüfen" angezeigt wird (2 Tage)
unsigned long lastSwitchTime = 0;
const unsigned long switchInterval = 30000; // Intervall für Displaywechsel in Millisekunden (30 Sekunden)

bool dataReceived = false;  // Datenempfang-Status
int currentScreen = 0;  // Startbildschirm

// Berechne die Füllhöhe in Prozent
float calculateFillPercentage(float distance) {
  float waterHeight = maxWaterHeight - (distance - maxSensorDistance);
  return (waterHeight / maxWaterHeight) * 100;
}

// Berechne das Wasservolumen in Litern
float calculateVolume(float distance) {
  float waterHeight = maxWaterHeight - (distance - maxSensorDistance);
  float radius = tankDiameter / 2;
  float volume = 3.14159 * (radius * radius) * waterHeight;  // Volumen in Kubikzentimetern
  return volume / 1000;  // Konvertiere in Liter
}

// Funktion zur Anzeige der Distanz
void displayDistance(float distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distanz: ");
  lcd.print((int) distance);
  lcd.print("cm");
}

// Funktion zur Anzeige des Volumens
void displayVolume(float distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vol: ");
  lcd.print((int)calculateVolume(distance));
  lcd.print("L");
}

// Funktion zur Anzeige des Füllstands in Prozent
void displayFill(float distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menge: ");
  lcd.print((int)calculateFillPercentage(distance));
  lcd.print("%");
}

// Funktion zur Anzeige der "Sensor prüfen"-Nachricht
void displayCheckSensor() {
  lcd.setCursor(0, 1);
  lcd.print("Sensor checken!    ");
}

// Callback-Funktion, die ausgeführt wird, wenn Daten empfangen werden
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&sensorData, incomingData, sizeof(sensorData));

  // Ausgabe auf dem seriellen Monitor
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Distanz: ");
  Serial.print((int)sensorData.distance);
  Serial.println(" cm");

  // Aktualisiere den letzten Empfangszeitpunkt
  lastReceivedTime = millis();
  dataReceived = true;

  lcd.setCursor(0, 1);
  lcd.print("                ");  // Lösche mögliche Fehlermeldungen
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
  // Prüfe, ob seit dem letzten Datenempfang mehr als "timeout" Millisekunden vergangen sind
  if (millis() - lastReceivedTime > timeout && dataReceived) {
    displayCheckSensor();
  }

  // Prüfe, ob es Zeit ist, den Bildschirm zu wechseln
  if (millis() - lastSwitchTime > switchInterval) {
    lastSwitchTime = millis();  // Setze den Timer zurück
    currentScreen = (currentScreen + 1) % 3;  // Wechsel zwischen 0, 1 und 2

    switch (currentScreen) {
      case 0:
        displayDistance(sensorData.distance);  // Zeige die Distanz
        break;
      case 1:
        displayVolume(sensorData.distance);  // Zeige das Volumen
        break;
      case 2:
        displayFill(sensorData.distance);  // Zeige den Füllstand
        break;
    }
  }
}
