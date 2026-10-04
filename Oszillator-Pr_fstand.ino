// Oszillator-Prüfstand
// Arduino-basierte Frequenzmessung eines Pendels
// inspiriert von der Unruh-Regulierung in mechanischen Uhren

const int red = 8;    // Roter LED-Pin
const int blue = 10;  // Blauer LED-Pin
const int green = 9;  // Grüner LED-Pin
const int sens = A1;  // Analoger Eingang für den CNY70-Sensor
int umbral = 500;     // Schwellenwert für die Erkennung (kann angepasst werden)
int detecciones = 0;  // Zähler für die Anzahl der erkannten Durchgänge
unsigned long tiempo_anterior = 0; // Zeitpunkt der letzten Messung (in Mikrosekunden)
bool detectadoAntes = false;       // Status der vorherigen Erkennung (Flankenerkennung)
unsigned long oscilacion = 0;      // Gemessene Schwingungsdauer (in Mikrosekunden)

void setup() {
  // Konfiguration der Pins als Ausgänge
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  
  // Serielle Kommunikation starten
  Serial.begin(9600);
  Serial.println("Prüfstand gestartet");
}

void loop() {
  // Sensorwert einlesen
  int lectura = analogRead(sens);
  
  // Standardzustand: LED rot, grün aus
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  
  // Erkennung: Sensorwert über Schwellenwert?
  bool detectado = (lectura > umbral);

  // Flankenerkennung: Nur bei Wechsel von nicht erkannt zu erkannt
  if (detectado && !detectadoAntes) {
    // LED auf grün schalten (Erkennung)
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    
    detecciones++;
    unsigned long ahora = micros(); // Aktuellen Zeitstempel in Mikrosekunden holen

    // Erste Erkennung: Referenzzeit speichern
    if (detecciones == 1) {
      tiempo_anterior = ahora;
      Serial.println("Referenz gespeichert");
    }
    // Jede ungerade Detektion (außer der ersten) entspricht einem vollen Zyklus
    else if ((detecciones % 2 != 0) && (detecciones != 1)) {
      oscilacion = ahora - tiempo_anterior;
      tiempo_anterior = ahora;
      
      // Umrechnung in Sekunden und Berechnung der Frequenz
      float periodo = oscilacion / 1000000.0; // Periodendauer in Sekunden
      float frecuencia = 1 / periodo;         // Frequenz in Hertz
      
      // Ausgabe der Messwerte auf dem seriellen Monitor
      Serial.print("Zyklus #");
      Serial.print(detecciones / 2);
      Serial.print("  Periodendauer: ");
      Serial.print(periodo, 4);
      Serial.print(" s  Frequenz: ");
      Serial.print(frecuencia, 3);
      Serial.println(" Hz");

      // LED wieder auf grün (kurzes Aufblinken)
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      
      // (Wiederholung - könnte entfernt werden)
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      
      // Überprüfung, ob Frequenz außerhalb des Toleranzbereichs liegt
      if (frecuencia > 1 || frecuencia < 0.75) {
        Serial.println("=== FEHLER: außerhalb der Toleranz ===");
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, HIGH); // Blaue LED signalisiert Fehler
        while (true) {}           // Programm anhalten
      }
    }
    
    // Nach 5 vollen Zyklen (detecciones/2 == 5) den Test als bestanden markieren
    if (detecciones / 2 == 5) {
      Serial.println("Oszillator in gutem Zustand - BESTANDEN");
      Serial.println("Programmende");
      while (true) {} // Programm anhalten
    }
    delay(2); // Kurze Pause zur Entprellung
  }
  
  // Status für die nächste Iteration speichern
  detectadoAntes = detectado;
}
