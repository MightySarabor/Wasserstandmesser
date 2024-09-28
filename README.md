# Arduino Project: Dein Projekttitel

## Intro
Beschreibe hier kurz das Projekt und den Zweck. Erkläre, was du mit diesem Projekt erreichen möchtest.

## The Team
Liste die Teammitglieder auf, die an diesem Projekt gearbeitet haben. Erwähne eventuell ihre Rollen oder Aufgabenbereiche.

## Components and Supplies

- **esp32 WROOM32** (x2)  
  <img src="https://m.media-amazon.com/images/I/71BY6XjW4yL._AC_SL1500_.jpg" width="200" />  
  [ESP32 WROOM32 kaufen](https://www.amazon.de/esp32-wroom/s?k=esp32+wroom)

- **AJ-SR04M** (x1)  
  <img src="https://m.media-amazon.com/images/I/51GyoUWmp5S._AC_.jpg" width="200" />  
  [AJ-SR04M kaufen](https://www.amazon.de/s?k=AJ-SR04M)

- **16x2 LCD Display with I2C Module** (x1)  
  <img src="https://m.media-amazon.com/images/I/71Kz+RabPiL._SL1500_.jpg" width="200" />  
  [16x2 LCD kaufen](https://www.amazon.de/s?k=lcd+display+i2c+16x2&__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1Z7IE0Y3NA9SM&sprefix=lcd+display+i2c+16x2%2Caps%2C84&ref=nb_sb_noss_2)

- **Jumper Kabel** (x1)  
  <img src="https://m.media-amazon.com/images/I/81ZY657A7XL._SL1500_.jpg" width="200" />  
  [Jumper Kabel kaufen](https://www.amazon.de/s?k=jumper+cable+female+female&crid=RU460WHOU1RY&sprefix=jumper+cable+femal%2Caps%2C90&ref=nb_sb_ss_pltr-data-refreshed_1_18)

## Apps and Platforms

- **Visual Studio Code 2024** (x1)  
  [Download Visual Studio Code 2024](https://code.visualstudio.com/)

- **PlatformIO** (x1)  
  [Download PlatformIO](https://platformio.org/)

## Tools and Machines
Liste die Werkzeuge und Maschinen auf, die für den Bau des Projekts verwendet wurden. Zum Beispiel:
- Lötstation
- Schraubendreher
- 3D-Drucker

## Project Description
Beschreibe das Projekt im Detail. Erläutere die Funktionsweise, die Logik und die Abläufe. Füge auch Schaltpläne oder Diagramme bei, falls erforderlich.

## Code
Füge hier den Code ein, der im Projekt verwendet wird. Alternativ kannst du auf eine externe Datei oder ein Repository verlinken.

```cpp
// Beispielcode
void setup() {
  // Setup-Funktion
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Loop-Funktion
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
