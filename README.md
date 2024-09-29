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

> [ ] **TODO**: Füge eine vollständige Liste der Werkzeuge und Maschinen hinzu, die du verwendet hast (z.B. Multimeter, Zangen, usw.).

## Project Description

Mit den Anforderungen im Hinterkopf habe ich die benötigten Teile gekauft. Einen ESP32 für den Sensor und einen für das Display. Bevor ich anfangen konnte, sind jedoch noch einige Vorarbeiten nötig gewesen. 

> [ ] **TODO**: Füge ein Bild des Projekts nach dem Zusammenbau hinzu.

### Lötarbeiten:
Als erstes habe ich das Display und das dazugelieferte Interface zusammengelötet. Das war das erste Mal, dass ich etwas zusammengelötet habe. Wichtig ist hier, dass man die Pins nicht miteinander verbindet. Leider ist das keine gute Methode, um beim Löten Zeit zu sparen, wie ich am Anfang dachte – es entsteht ein Kurzschluss.

> [ ] **TODO**: Füge detaillierte Lötanleitungen oder Links zu Tutorials für Anfänger hinzu.

### Entwicklungsumgebung:
Mit der Extension PlatformIO IDE habe ich dann ein neues Projekt gestartet.

<img src="https://github.com/user-attachments/assets/5212c9b2-bfbe-4dda-b172-903561b6971d" width="300"/>  

Wie im Screenshot habe ich die folgenden Einstellungen gewählt:

> [ ] **TODO**: Erkläre die genauen Einstellungen in der Entwicklungsumgebung (z.B. Board, Baudrate, Bibliotheken).

### Verkabelung:
Dann habe ich die Komponenten erstellt. Sensor und Display müssen wie folgt verkabelt werden:

> [ ] **TODO**: Füge eine detaillierte Anleitung zur Verkabelung des ESP32-Boards hinzu (inkl. Pinbelegung).

#### Der Sensor:
- **Verkabelung**:  
  ![Sensor Verkabelung](image_link)
  
  Der Sensor wird wie folgt angeschlossen:
Nachdem der Sensor angeschlossen ist, ist er auch schon betriebsbereit. Im Standardmodus braucht der Sensor einen Trigger um dann das Echosignal zu senden. Anschließend sendet der Sensor die zurückgelegte Distanz des Signals in ms zurück. Anhand der ms kann man dann mit folgender Formel die zurückgelegten cm berechnen und damit die Distanz.

```cpp
// Berechne die Entfernung basierend auf der Zeit (Schallgeschwindigkeit = 0,034 cm/µs)
float distance = (duration * 0.034) / 2;
```
Neben dem Standardmodus gibt es noch 4 weitere Modi, diese werden via Widerständen über R19 eingestellt. Um eine möglichst viel Energie zu sparen, können wir den Sensor in den Energiesparmodus bringen. So geht er zwischen den Messungen in einen Standbymodus wodurch er weniger Energie verbraucht.




  > [ ] **TODO**: Beschreibe die Anschlüsse des Sensors im Detail und erkläre, wie der Sensor funktioniert.

#### Das Display:
- **Verkabelung**:  
  ![Display Verkabelung](image_link)

  Das Display wird wie folgt angeschlossen:

> [ ] **TODO**: Erkläre, wie das I2C-Protokoll funktioniert und wie es mit dem ESP32 verbunden wird.

### Endmontage:
- **Zisterne**:  
  ![Bild der Installation in der Zisterne](image_link)

- **Küchentisch**:  
  ![Bild der Installation auf dem Küchentisch](image_link)

> [ ] **TODO**: Füge Bilder der fertigen Installation in der Zisterne und auf dem Küchentisch hinzu.

## Methodenvalidierung

> [ ] **TODO**: Beschreibe, wie du die Funktionsweise des Sensors und der Anzeige überprüft und validiert hast (z.B. Testläufe, Fehlertests).

## Code

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


### Zusätzliche TODOs:
1. **Füge mehr Erklärungen** zur Funktionsweise der einzelnen Komponenten (Sensor, Display, ESP32) hinzu.
2. **Verkabelungsdiagramme**: Ein Fritzing-Diagramm für die Verkabelung kann hilfreich sein.
3. **Bibliotheken und Abhängigkeiten**: Liste alle notwendigen Arduino/PlatformIO-Bibliotheken auf, die du für das Projekt benötigt hast.
4. **Testberichte und Ergebnisse**: Füge einen Abschnitt hinzu, in dem du Testläufe und Ergebnisse dokumentierst.

Mit diesen TODOs hast du eine klare Übersicht über die noch anstehenden Aufgaben, um die README zu vervollständigen.
