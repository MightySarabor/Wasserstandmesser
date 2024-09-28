# Arduino Project: Dein Projekttitel

## Intro
Beschreibe hier kurz das Projekt und den Zweck. Erkläre, was du mit diesem Projekt erreichen möchtest.

## The Team
Liste die Teammitglieder auf, die an diesem Projekt gearbeitet haben. Erwähne eventuell ihre Rollen oder Aufgabenbereiche.

## Components and Supplies
Gib hier eine Liste der benötigten Komponenten und Materialien an, die für das Projekt erforderlich sind. Zum Beispiel:
- Arduino Uno
- Breadboard
- LEDs
- Widerstände
- Jumper-Kabel

## Tools and Machines
Liste die Werkzeuge und Maschinen auf, die für den Bau des Projekts verwendet wurden. Zum Beispiel:
- Lötstation
- Schraubendreher
- 3D-Drucker

## Apps and Platforms
Gib die Software-Tools und Plattformen an, die für das Projekt verwendet werden, zum Beispiel:
- Arduino IDE
- Fritzing
- Tinkercad

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
