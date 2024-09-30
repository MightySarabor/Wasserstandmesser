# Arduino Project: Dein Projekttitel

## Intro

Das Ziel dieses Projekts war es, einen **Wasserstandsmesser** für die Zisterne meiner Eltern zu entwickeln. Bisher mussten wir den Wasserstand manuell mit einem Zollstock messen – ein umständlicher und zeitaufwändiger Prozess. Mit diesem Projekt soll der Vorgang stark vereinfacht werden, sodass wir den Wasserstand zukünftig bequem von einem Display ablesen können.

Die ersten Kapitel sollen helfen, das Projekt nachzubauen. Nach der Projektbeschreibung werde ich auf Besonderheiten des Codes und interessante technische Daten eingehen.

### Anforderungen an das Projekt:
1. **Komfort**:  
   Das Display soll sich nicht am Sensor selbst befinden, da wir ansonsten weiterhin fast den gesamten bisherigen Prozess durchlaufen müssten. Stattdessen wird es an einem Ort aufgestellt, der im Alltag leicht zugänglich ist, wie z.B. auf dem Küchentisch.

2. **Zuverlässigkeit**:  
   Die Messungen müssen zuverlässig sein, da wir sonst weiterhin den Wasserstand manuell prüfen müssten – was den Vorteil des Projekts zunichtemachen würde. Hierbei anzumerken, dass eine hohe Präzision nicht von Nöten ist. Ich habe mich als Product Owner intensiv mit meinen Stakeholdern (meinen Eltern) beraten und ihre Anforderungen waren: "Ich möchte wissen, ob ich die Blumen gießen kann." Für die Lesbarkeit werden Nachkommastellen deswegen ausgelassen.

4. **Wartungsarm**:  
   Der Wasserstandsmesser sollte über längere Zeiträume hinweg ohne Eingriff funktionieren. Es soll also keine neue, regelmäßige Arbeit entstehen, wie z.B. häufige Wartung oder Kalibrierung.

### Technische Umsetzung:
- **Sensor und Mikrocontroller**:  
   Der Ultraschallsensor, der speziell für feuchte Umgebungen geeignet ist, wird in der Zisterne platziert. Er erfasst den Wasserstand und überträgt die Daten drahtlos an einen zweiten Mikrocontroller, der sich z.B. im Haus auf dem Küchentisch befindet.
   
- **Energieversorgung**:  
   Der Sensor wird mit wiederaufladbaren Batterien betrieben. Dank des Deep-Sleep-Modus des ESP32-Chips sollte die Batterie eine Laufzeit von 3 bis 6 Monaten haben, bevor sie wieder aufgeladen werden muss.

Mit dieser Lösung gehört das manuelle Messen des Wasserstandes der Vergangenheit an. Der Gang in den Garten dient künftig nur noch der Entspannung!

## Components and Supplies

- **esp32 WROOM32** (x2)  
  <img src="https://m.media-amazon.com/images/I/71BY6XjW4yL._AC_SL1500_.jpg" width="30%" />  
  [ESP32 WROOM32 kaufen](https://www.amazon.de/esp32-wroom/s?k=esp32+wroom)

- **AJ-SR04M** (x1)  
  <img src="https://m.media-amazon.com/images/I/51GyoUWmp5S._AC_.jpg" width="30%" />  
  [AJ-SR04M kaufen](https://www.amazon.de/s?k=AJ-SR04M)

- **16x2 LCD Display with I2C Module** (x1)  
  <img src="https://m.media-amazon.com/images/I/71Kz+RabPiL._SL1500_.jpg" width="30%" />  
  [16x2 LCD kaufen](https://www.amazon.de/s?k=lcd+display+i2c+16x2&__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1Z7IE0Y3NA9SM&sprefix=lcd+display+i2c+16x2%2Caps%2C84&ref=nb_sb_noss_2)

- **Jumper Kabel** (x1)  
  <img src="https://m.media-amazon.com/images/I/81ZY657A7XL._SL1500_.jpg" width="30%" />  
  [Jumper Kabel kaufen](https://www.amazon.de/s?k=jumper+cable+female+female&crid=RU460WHOU1RY&sprefix=jumper+cable+femal%2Caps%2C90&ref=nb_sb_ss_pltr-data-refreshed_1_18)

## Apps and Platforms

- **Visual Studio Code 2024**  
  [Download Visual Studio Code 2024](https://code.visualstudio.com/)

- **PlatformIO**  
  [Download PlatformIO](https://platformio.org/)

## Tools and Machines
Liste die Werkzeuge und Maschinen auf, die für den Bau des Projekts verwendet wurden. Zum Beispiel:
- Lötstation
- Schraubendreher

> [ ] **TODO**: Füge eine vollständige Liste der Werkzeuge und Maschinen hinzu, die du verwendet hast (z.B. Multimeter, Zangen, usw.).

## Project Description

Mit den Anforderungen im Hinterkopf habe ich die benötigten Teile gekauft. Einen ESP32 für den Sensor und einen für das Display. Bevor ich anfangen konnte, sind jedoch noch einige Vorarbeiten nötig gewesen. 

> [ ] **TODO**: Füge ein Bild des Projekts nach dem Zusammenbau hinzu.

### Lötarbeiten
Als erstes habe ich das Display und das dazugelieferte Interface zusammengelötet. Das war das erste Mal, dass ich etwas zusammengelötet habe. Wichtig ist hier, dass man die Pins nicht miteinander verbindet. Leider ist das keine gute Methode, um beim Löten Zeit zu sparen, wie ich am Anfang dachte – es entsteht ein Kurzschluss.

<img src="https://github.com/user-attachments/assets/3331cd9d-84c1-4eb7-94a6-7dd5d7e49625" width="30%" />

Zusätzlich habe ich einen 300 kΩ Widerstand an die R19 Pins meines AJ-SR04M Sensors gelötet. Der AJ-SR04M verfügt über fünf verschiedene Modi, die über diese Pins und einen passenden Widerstand gesteuert werden können. Mit dem 300 kΩ Widerstand schalte ich den Sensor in den Energiesparmodus, wodurch er zwischen den Messungen deutlich weniger Strom verbraucht.

Ein wichtiger Punkt ist, dass in diesem Modus das Trigger-Signal nicht nur 10 Mikrosekunden lang sein sollte, sondern mindestens 1 Millisekunde dauern muss, um eine Messung auszulösen.

### Verkabelung
Dann habe ich die Komponenten erstellt. Sensor und Display müssen wie in den Tabellen beschrieben verkabelt werden. Danach sind die Geräte direkt betriebsbereit.

#### Der Sensor
Der Sensor wird wie folgt angeschlossen:

| **AJ-SR04M** | **ESP32 Pin**  | 
|--------------|----------------|
| VCC          | 5V             |
| GND          | GND            | 
| TRIG         | GPIO 5         |    
| ECHO         | GPIO 18        | 

<img src="https://github.com/user-attachments/assets/162fb203-1b52-4b58-a295-8b85bc301caf" width="30%" />

#### Das Display

Das Display wird wie folgt angeschlossen:

Ein Hinweis bei dem Display: Es gibt eine Stellschraube beim Displayinterface. Damit kann der Kontrast eingestellt werden. Hier einfach ausprobieren, was am besten aussieht.

| LCD-Pin | ESP32-Pin |
|---------|-----------|
| VCC     | 5V        |
| GND     | GND       |
| SDA     | 21        |
| SCL     | 22        |

<img src="https://github.com/user-attachments/assets/1f8e870f-86c3-4933-90d6-19265de6d720" width="30%" />

### Entwicklungsumgebung und Code:

Zum Entwickeln habe ich Visual Studio Code mit der Extension PlatformIO IDE benutzt. Mit der Extension einfach den Code vom Repository clonen und die Projekte jeweils auf die Boards spielen.
Wichtig: Ich habe beide Projekte in einem Workspace und es wird immer nur das obere Projekt hochgeladen. Nachdem ich ein Projekt hochgeladen habe, habe ich es von dem Workspace entfernt und dann das andere hochgeladen.

Wenn der Code auf die Boards geladen wurde, können die Boards an eine beliebige Stromquelle angeschlossen werden und laufen direkt von alleine. Das Display vor dem Sensor anschließen, weil der Sensor nur alle 24 Stunden Daten liefert. 

Um das Projekt selbst umzusetzen, müssen ein paar Anpassungen im Code gemacht werden, um den Code an die eigene Umgebung anzupassen. 

#### Beim Receiver_Display:

LCD Display Adresse:  
Zeile im Code: `LiquidCrystal_I2C lcd(0x27, 16, 2);`  
Beschreibung: I2C-Adresse und Größe des LCD-Displays anpassen.

maxSensorDistance:  
Abstand des Sensors von der maximalen Füllhöhe (in cm).  
Zeile im Code: `const float maxSensorDistance = 60;`

maxWaterHeight:  
Maximale Wasserhöhe im Tank (in cm).  
Zeile im Code: `const float maxWaterHeight = 200;`

tankDiameter:  
Durchmesser des Tanks (in cm).  
Zeile im Code: `const float tankDiameter = 200;`

Timeout für Sensorprüfung:  
Zeile im Code: `const unsigned long timeout = 172800000;`  
Beschreibung: Zeit in Millisekunden, nach der "Sensor checken!" angezeigt wird (2 Tage).

Bildschirmwechsel-Intervall:  
Zeile im Code: `const unsigned long switchInterval = 30000;`  
Beschreibung: Zeitintervall in Millisekunden für Displaywechsel (30 Sekunden).

#### Beim Sender_Sensor:

receiverAddress:  
Zeile im Code: `uint8_t receiverAddress[] = {0xAC, 0x15, 0x18, 0xEA, 0x9E, 0x08};`  
Beschreibung: Dies ist die MAC-Adresse des Empfängers. Die MAC-Adresse des Empfänger-ESP32 muss angepasst werden.

maxAttempts:  
Zeile im Code: `const int maxAttempts = 3;`  
Beschreibung: Maximale Anzahl der Sendeversuche, bevor der ESP32 in den Deep-Sleep geht. Dies kann erhöht oder verringert werden, je nachdem, wie oft der Nutzer eine erneute Übertragung versuchen möchte.

Deep-Sleep Dauer:  
Zeile im Code: `esp_sleep_enable_timer_wakeup(86400000000);`  
Beschreibung: Zeit, die der ESP32 im Deep-Sleep bleibt (hier 24 Stunden in Mikrosekunden). Kann angepasst werden, um die Dauer des Schlafs zu verändern.

### Endmontage:
**Zisterne**:

Um den Sensor in der Zisterne zu installieren, habe ich die Komponenten in wasserfesten Tüten verstaut und vorsichtig Löcher für die Kabel hineingeschnitten. Anschließend habe ich alles in den Igel eingesetzt. Dafür musste ich das Loch mit einer Zange etwas vergrößern. Es war zwar immer noch etwas knifflig, aber letztendlich hat alles gut hineingepasst.

Das Kabel des Sensors musste ich dann noch in der Zisterne befestigen. Dazu habe ich alte Aluschalen meiner Mutter verwendet. Ich habe die Wände der Schalen entfernt, ein Kreuz in den Boden geschnitten und den Sensor hindurchgeführt. Zur zusätzlichen Fixierung habe ich den Sensor mit einem Kabelbinder gesichert. Die Enden der Schalen habe ich einfach um die Gitterstangen gewickelt, um den Sensor stabil zu befestigen.

In einer Ecke der Zisterne habe ich außerdem einen Korken angebracht, um sicherzustellen, dass kein Druck auf das Kabel ausgeübt wird.
  <img src="https://github.com/user-attachments/assets/b49df7d2-764e-4bb3-8485-7e0c6e30b2ce" width="45%" />
  <img src="https://github.com/user-attachments/assets/8bf5ccc8-c24a-4959-afcd-62962e585665" width="45%" />
  <img src="https://github.com/user-attachments/assets/083203ef-f0f0-4674-9472-077183bd864c" width="45%" />


  <img src="https://github.com/user-attachments/assets/793cec12-c066-46a8-b230-9a566d998c38" width="45%" />
  <img src="https://github.com/user-attachments/assets/d894f8ab-c48c-4000-9642-30413c631689" width="45%" />

**Display**:  
Das Display steht bei uns in der Küche. Von dort aus kann man auf einen Blick sehen, wie viel Wasser noch in der Zisterne ist. Die Displays alternieren alle 30 Sekunden zwischen den Anzeigen.

  <img src="https://github.com/user-attachments/assets/22f39efa-2636-467a-9cfb-8cd956662c4d" width="30%" />
  <img src="https://github.com/user-attachments/assets/a76ce32d-dec5-4c4a-9738-4d91f1c7b0f6" width="30%" />
  <img src="https://github.com/user-attachments/assets/7dee42c7-fa07-4301-93bc-b8c8290c6ae2" width="30%" />

## Code

Da der Code selbst im Repository zu finden ist, werde ich auf die Besonderheiten des Codes eingehen. Zu den Standardfunktionen findet man viel im Internet oder kann sich auch von einer KI, wie chatGPT helfen lassen.

Sender_Sensor:

Im Sensor habe ich absichtlich nur die Distanz gemessen. So bleibt der Sensor anwendungsagnostisch und ist nur für das Messen zuständig. Außerdem kann der Sensor im Garten bleiben, auch wenn ich beim Display andere Werte anzeigen möchte, oder das Display mal austasche. Die Transformationen der Daten finden im Receiver_Display statt. 
Besonderheiten beim Sensor ist der Deep_Sleep Modus. Normalerweise besteht ein Arduino Code aus setup und loop. Wird der Deep_Sleep angewendet, startet sich der Microcontroller in vordefinierten Abständen immer wieder an uns aus. Daher wird nur der setup Teil benötigt. Zum loop kommt es nicht.

Die Berechnung von ms in Distanz:
```cp
// Entfernungsmessung mit HC-SR04
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034) / 2;
}
```

Receiver_Display:

Hier werden die Daten transformiert und angezeigt. Die Daten erhält das Receiver_Display in cm. Daraus kann ich mir alle nötigen Messwerte errechnen.

Berechnung von Distanz zum Volumen:
```cpp
// Berechne das Wasservolumen in Litern
float calculateVolume(float distance) {
  float waterHeight = maxWaterHeight - (distance - maxSensorDistance);
  float radius = tankDiameter / 2;
  float volume = 3.14159 * (radius * radius) * waterHeight;  // Volumen in Kubikzentimetern
  return volume / 1000;  // Konvertiere in Liter
}
```
Berechnung von Distanz zu Prozentfüllmenge:
```cpp
// Berechne die Füllhöhe in Prozent
float calculateFillPercentage(float distance) {
  float waterHeight = maxWaterHeight - (distance - maxSensorDistance);
  return (waterHeight / maxWaterHeight) * 100;
}
```



