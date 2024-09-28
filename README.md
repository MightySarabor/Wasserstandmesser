# Arduino Project: Dein Projekttitel

## Intro

Das Ziel dieses Projekts war es, einen **Wasserstandsmesser** für die Zisterne meiner Eltern zu entwickeln. Bisher mussten wir den Wasserstand manuell mit einem Zollstock messen – ein umständlicher und zeitaufwändiger Prozess. Mit diesem Projekt soll der Vorgang stark vereinfacht werden, sodass wir den Wasserstand zukünftig bequem von einem Display ablesen können.

### Anforderungen an das Projekt:
1. **Komfort**:  
   Das Display soll sich nicht am Sensor selbst befinden, da wir ansonsten weiterhin fast den gesamten bisherigen Prozess durchlaufen müssten. Stattdessen wird es an einem Ort aufgestellt, der im Alltag leicht zugänglich ist, wie z.B. auf dem Küchentisch.

2. **Zuverlässigkeit**:  
   Die Messungen müssen zuverlässig sein, da wir sonst weiterhin den Wasserstand manuell prüfen müssten – was den Vorteil des Projekts zunichtemachen würde.

3. **Wartungsarm**:  
   Der Wasserstandsmesser sollte über längere Zeiträume hinweg ohne Eingriff funktionieren. Es soll also keine neue, regelmäßige Arbeit entstehen, wie z.B. häufige Wartung oder Kalibrierung.

### Technische Umsetzung:
- **Sensor und Mikrocontroller**:  
   Der Ultraschallsensor, der speziell für feuchte Umgebungen geeignet ist, wird in der Zisterne platziert. Er erfasst den Wasserstand und überträgt die Daten drahtlos an einen zweiten Mikrocontroller, der sich z.B. im Haus auf dem Küchentisch befindet.
   
- **Energieversorgung**:  
   Der Sensor wird mit wiederaufladbaren Batterien betrieben. Dank des Deep-Sleep-Modus des ESP32-Chips sollte die Batterie eine Laufzeit von 3 bis 6 Monaten haben, bevor sie wieder aufgeladen werden muss.

Mit dieser Lösung gehört das manuelle Messen des Wasserstandes der Vergangenheit an. Der Gang in den Garten dient künftig nur noch der Entspannung!

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
