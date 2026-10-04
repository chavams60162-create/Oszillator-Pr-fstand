Oszillator-Prüfstand

 Beschreibung
Ein Arduino-basierter Prüfstand zur Messung der Frequenzstabilität eines einfachen Pendels – inspiriert von der Unruh-Regulierung in mechanischen Uhren.

Komponenten
- 1x Kleine Steckplatine
- 1x Arduino Uno R3
- 1x LED RGB (an Pin 8, 9 und 10)
- 1x CNY70 Sensor (optischer Reflexsensor, an Pin A2)
- 1x 10 kΩ Widerstand
- 5x 220 Ω Widerstände

Schaltplan
**Wichtiger Hinweis:**  
Der Schaltplan und das Anschlussdiagramm befinden sich im **zusätzlichen Dokument (PDF)** im **Abschnitt 3**. Dort findest du die Pläne und wichtige zusätzliche Notizen, um den Schaltplan zu verstehen.

In der Simulation (Tinkercad) wurde anstelle des CNY70 ein Taster verwendet, da der Sensor dort nicht verfügbar ist. Die Position des Tasters und die Kabelführung in der Simulation entsprechen **exakt** dem Anschluss des realen Sensors.

Funktionsweise
Das Pendel schwingt und unterbricht den Lichtstrahl des CNY70-Sensors. Der Arduino misst die Zeit zwischen den Unterbrechungen und berechnet daraus die Frequenz.

- Anfangszustand: Das LED RGB leuchtet rot.
- Bei jeder Erkennung:** Jedes Mal, wenn das Pendel den Sensor passiert, blinkt das LED grün.
- Nach 5 stabilen Perioden: Wenn in 5 aufeinanderfolgenden Messungen keine Anomalie festgestellt wird, leuchtet das LED dauerhaft grün.
- Bei einer Anomalie: Wenn die Frequenz außerhalb des erlaubten Bereichs liegt, stoppt das System, das LED leuchtet blau und eine Fehlermeldung wird angezeigt.

Akzeptabler Frequenzbereich:
- Referenzfrequenz: ~0,85 Hz
- Obergrenze: 1,0 Hz
- Untergrenze: 0,75 Hz
- Maximale Abweichung: ~12–18 %

Ausführung
1. Die Schaltung gemäß dem Schaltplan aufbauen.
2. Den Code in der Arduino IDE öffnen und auf das Board hochladen.
3. Den seriellen Monitor öffnen (9600 Baud), um die gemessene Frequenz zu sehen.
4. Das Pendel in Bewegung versetzen und die LED-Anzeige beobachten.

Ergebnisse
- Gemessene Frequenz: ~0,85 Hz
- Abweichung: ~12–18 % (innerhalb des akzeptablen Bereichs)
  
***video***
  https://youtu.be/fMC7iJrH5pU?si=q8NbWx_Mj7CZ83-r
  
***Hinweis zur Nutzung von KI***
Während der Entwicklung dieses Projekts wurden KI-Tools als Unterstützung für die Übersetzung ins Deutsche, die Ideenfindung und die Erstellung der Code-Kommentare verwendet. Design, Umsetzung, Montage, Tests und Programmierung wurden vom Autor durchgeführt.

Autor
Salvador Martínez Santoyo  
Tecnológico de Monterrey, Campus Querétaro  
[GitHub](https://github.com/chavams60162-create)
