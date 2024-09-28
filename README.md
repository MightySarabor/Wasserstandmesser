# Arduino Project: Dein Projekttitel

## Intro
Beschreibe hier kurz das Projekt und den Zweck. Erkläre, was du mit diesem Projekt erreichen möchtest.

## The Team
Liste die Teammitglieder auf, die an diesem Projekt gearbeitet haben. Erwähne eventuell ihre Rollen oder Aufgabenbereiche.

## Components and Supplies

- **esp32 WROOM32** (x2)  
  <https://www.amazon.de/esp32-wroom/s?k=esp32+wroom>
  ![ESP32 WROOM32]([http://url/to/img.png](https://m.media-amazon.com/images/I/71BY6XjW4yL._AC_SL1500_.jpg))

- **AJ-SR04M** (x1)  
  <Link zum Produkt>  
  ![AJ-SR04M]([image_link](https://m.media-amazon.com/images/I/71BY6XjW4yL._AC_SL1500_.jpg))

- **16x2 LCD Display with I2C Module** (x1)  
  <Link zum Produkt>  
  ![16x2 LCD](image_link)

- **Jumper Kabel** (x1)  
  <Link zum Produkt>  
  ![Jumper Kabel](image_link)

## Apps and Platforms

- **Visual Studio Code 2024** (x1)  
  <Link zur Plattform>

- **PlatformIO** (x1)  
  <Link zur Plattform>


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
