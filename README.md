# STII-game
Semesterarbeit Seminar Softwaretechnologie II
<p align="center" width="200">
  <img src="https://github.com/stereolith/STII-game/raw/master/docs/stII.gif">
</p>

## Dokumentation
### Starten
1. Projekt herunterladen und entpacken
2. .pro-Datei in QT öffnen
3. Kompilieren
(getestet mit _Desktop Qt 5.11.1 MSVC2017 64bit_)

### Spielen
- Klick auf "Start" startet das Spiel
- "Sichern" und "Laden" ermöglicht das speichern und laden, während das Spiel pausiert ist
#### Steuerung
- Spieler lässt sich mit den Pfeiltasten ←  → steuern
#### Ziel/ Spielfluss
- Herunterfallenden Blöcken ausweichen
- Berührt man einen Block, verliert man ein Leben (◆◆◇) und ist für kurze Zeit unverwundbar (Spieler ist grau gefärbt)
- Das Einsammeln von roten Power-Up-Blöcken (➕) lädt Leben wieder auf


### Wichtige Klassen und Funktionen
1. **`class meinWidget`** Grundlegender Fensteraufbau, enthält Laden-, Sichern- und Start-/Pause-Buttons und Spielfeld-Renderbereich
2. **`class spielFeld`** Renderbereich für die Elemente des Spieles selbst: Spieler, fallende Blöcke und Lebensanzeige
    - `spielFeld::updateEvent()` Dieser SLOT wird durch einen Timer alle 30ms aufgerufen. Positionen der Fallenden Blöcke und die Punktzahl werden hier aktualisiert, sowie werden timeouts verwaltet, die für eine kurze Zeit das Spiel anhalten oder den Spieler unverwundbar machen, wenn der Spieler getroffen wurde.
    - `spielFeld::spawnFallingPiece()` Erstellt einen neuen fallenden Block. Fallende Blöcke werden mit integer für den Typ (0-5) initialisiert, welcher Form, Farbe und Geschwindigkeit/ Richtung bestimmt. Pointer zu allen fallenden Blöcken sind in einem vector gespeichert. Bei jedem Aufruf dieser Funktion werden alte, zur Löschung markierte Blöcke aus dem vector entfernt.
    - `spielFeld::setActive()` Stellt ein, ob das Spiel aktiv ist. Inaktiv: Alle Blöcke und der Hintergrund erscheinen ausgegraut: Die InactiveColor bei piece-Objekten wurd durch das signal `signalActive()` bei allen dieser Objekten aktiviert. Der `setActive(bool a)`-SLOT jedes piece-Objektes wurde bei der Initialization mit dem signal verbunden.
    - `spielFeld::serialize(QFile &file)` und `spielFeld::deserialize(QFile &file)` Für das Speichern und Laden eines Savegame: Bringen Daten zur Position aller Elemente, den Punktestand und die Anzahl der Leben in serielle (und human-readable) Form und extrahieren aus diesen seriellen Daten wieder alle Informationen für das Spiel. 
    - `spielFeld::gameOver()` Zeigt beim Verlieren des Spieles eine entsprechende Nachricht und den Punktestand in Textform an.
3. **`class piece`** Grundbaustein/ Superklasse für Elemente auf dem Spielfeld: player, lives, fallingPieces. Definiert Farbe, Füllmuster, Form und implementiert entsprechend ein PaintEvent. 
    - für den "ausgegraut"-Effekt bei einem inaktiven spielFeld wird eine inactiveColor-Version der Grundfarbe erstellt, die eine geringere Sättigung hat (siehe `spielFeld::setActive()`)
4. **`class fallingPiece : public piece`** Klasse für alle fallenden Blöcke. Farbe, Form und Geschwindigkeit/ Richtung (bei alternierender Richtung zusätzlich: alternative Richtung, Wechselintervall) werden im Konstruktor je nach übergebenen Typ bestimmt. Ein eigener Timer für Objekte dieser Klasse feuert alle 100ms eine SLOT-Funktion, die bei Blöcken mit alternierender Richtung ("Zick-Zack") je nach gesetztem Intervall den alternativen Richtungswert mit dem aktuellen Richtungswert tauscht.
    - **`fallingPiece::setFallingShape(int shapeNo)`** Definiert die Polygone für die Form der fallingPiece-Objekte
5. **`class lives`** Rendert dynamisch die Rauten für die Lebensanzeige (◆◆◇) 
