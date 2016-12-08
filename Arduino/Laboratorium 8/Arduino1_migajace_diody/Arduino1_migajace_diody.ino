/* Kamil Kasperski
   Arduino Laboratoria nie wiem które - Informatyka Stosowana II rok
   Podstawy Techniki Mikroprocesorowej

   Kod pisany dla Arduino Uno

   DEBUG mode:
   false - Serial off
   true - Serial on
   change DEBUG value
*/
// Debugowanie
const bool DEBUG = false;

const int LED1 = 12;      // digital pin 12
const int LED2 = 8;       // digital pin 8
const int button = 2;     // digital pin 2 - INT0

// deklaracja wartości pomocniczych
int LEDp = LED1;          // pomocnicza wartość LED - będzie się zmieniać podczas wykonania kodu, domyślnie przypisana do LED1
int LEDp_state = HIGH;
int buttonState = 0;

// deklaracja wartości opóźnienia
unsigned long previousMillis = 0;
const long interval = 1000;

void change_diode() {
  // funkcja wywoływana podczas przerwania zewnętrznego - zmiana cyfrowego pinu dla zasilania LED

  if (DEBUG) {
    Serial.println("Wejscie do przerwania!");
  }

  if (LEDp == LED1) {
    digitalWrite(LEDp, LOW);        // wygaszanie LED przed zmianą wartości
    LEDp = LED2;                    // zmiana wartości LEDp
  } else {
    digitalWrite(LEDp, LOW);
    LEDp = LED1;
  }
}

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    Serial.println("Inicjalizacja portów");
  }

  pinMode(LED1, OUTPUT);              // ustawienie LED1 jako wyjście
  pinMode(LED2, OUTPUT);              // ustawienie LED2 jako wyjście
  pinMode(button, INPUT_PULLUP);      // ustawienie buttton jako wyjście

  // przypisanie zewnętrznego przerwania do funkcji change_diode()
  attachInterrupt(digitalPinToInterrupt(button), change_diode, RISING);
}

void loop() {
  // Program będzie tak długo migać na LED dopóki nie zmieni się stan na pinie 2 - INT0
  // i nie zmieni wartości portu LEDa
  unsigned long currentMillis = millis();
  buttonState = digitalRead(button);

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;     // zapisuje ostatni czas kiedy LED mignął

    // wyznaczanie wartości LEDa - naprzemiennie LOW lub HIGH
    if (LEDp_state == LOW) {
      LEDp_state = HIGH;
    } else {
      LEDp_state = LOW;
    }
    if (DEBUG) {
      Serial.print("LEDp aktualny pin ");
      Serial.print(LEDp);
      Serial.print(" - stan ");
      Serial.print(LEDp_state);
      Serial.print("\n");
    }
    digitalWrite(LEDp, LEDp_state);   // przypisz portowi LEDp zmienną LEDp_state
  }
}
