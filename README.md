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

### Lötarbeiten
Als erstes habe ich das Display und das dazugelieferte Interface zusammengelötet. Das war das erste Mal, dass ich etwas zusammengelötet habe. Wichtig ist hier, dass man die Pins nicht miteinander verbindet. Leider ist das keine gute Methode, um beim Löten Zeit zu sparen, wie ich am Anfang dachte – es entsteht ein Kurzschluss.

![2ee921cd-962c-41db-8a32-675963d8e4d1](https://github.com/user-attachments/assets/3331cd9d-84c1-4eb7-94a6-7dd5d7e49625)

Zusätzlich habe ich einen 300 kΩ Widerstand an die R19 Pins meines AJ-SR04M Sensors gelötet. Der AJ-SR04M verfügt über fünf verschiedene Modi, die über diese Pins und einen passenden Widerstand gesteuert werden können. Mit dem 300 kΩ Widerstand schalte ich den Sensor in den Energiesparmodus, wodurch er zwischen den Messungen deutlich weniger Strom verbraucht.

Ein wichtiger Punkt ist, dass in diesem Modus das Trigger-Signal nicht nur 10 Mikrosekunden lang sein sollte, sondern mindestens 1 Millisekunde dauern muss, um eine Messung auszulösen.

### Verkabelung
Dann habe ich die Komponenten erstellt. Sensor und Display müssen wie in den Tabellen beschrieben verkabelt werden. Danach sind die Geräte direkt betriebsbereit.

#### Der Sensor
Der Sensor wird wie folgt angeschlossen:

  
| **AJ-SR04M** | **ESP32 Pin**  | 
|--------------------|----------------|
| VCC                | 5V             |
| GND                | GND            | 
| TRIG               | GPIO 5         |    
| ECHO               | GPIO 18        | 

<img src="https://github.com/user-attachments/assets/162fb203-1b52-4b58-a295-8b85bc301caf" width="300"/>

#### Das Display

Das Display wird wie folgt angeschlossen:

Ein Hinweis bei dem Display: Es gibt eine Stellschraube beim Displayinterface. Damit kann der Kontrast eingestellt werden. Hier einfach ausprobieren, was am besten aussieht.

| LCD-Pin | ESP32-Pin |
|---------|-----------|
| VCC     | 5V        |
| GND     | GND       |
| SDA     | 21        |
| SCL     | 22        |

<img src="https://github.com/user-attachments/assets/1f8e870f-86c3-4933-90d6-19265de6d720" width="200"/>

### Endmontage:
- **Zisterne**:  
  ![Bild der Installation in der Zisterne](image_link)

- **Küchentisch**:  
  ![Bild der Installation auf dem Küchentisch](image_link)

> [ ] **TODO**: Füge Bilder der fertigen Installation in der Zisterne und auf dem Küchentisch hinzu.

## Methodenvalidierung

> [ ] **TODO**: Beschreibe, wie du die Funktionsweise des Sensors und der Anzeige überprüft und validiert hast (z.B. Testläufe, Fehlertests).

## Entwicklungsumgebung und Code:

Zum Entwickeln habe ich Visualstudio Codes mit der Extension PlatformIO IDE benutzt. Mit der Extension einfach den Code vom Repository clonen und die Projekte jeweils auf die Boards spielen.
Wichtig: Ich habe beide Projekte in einem Workspace und es wird immer nur das obere Projekt hochgeladen. Nachdem ich ein Projekt hochgeladen habe, habe ich es von dem Workspace entfernt und dann das andere hochgeladen.

Wenn der Code auf die Boards geladen wurde, können die Boards an eine beliebige Stromquelle angeschlossen werden und laufen direkt von alleine. Das Display vor dem Sensor anschließen, weil der Sensor nur alle 24 Stunden Daten liefert. 

### Code

Da der Code selbst im Repository zu finden ist, werde ich auf die Besonderheiten des Codes eingehen. Zu den Standardfunktionen findet man viel im Internet oder kann sich auch von einer KI, wie chatGPT helfen lassen.




