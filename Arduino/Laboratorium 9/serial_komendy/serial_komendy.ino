const int D0 = 12;
const int D1 = 8;
const int  BUTTON = 2;
String option;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // definicja startu serial portu
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char readByte = Serial.read();
    option += readByte;

    // still in bullshit state, there is a better way to handle it
    if (option == "ADC?#") {
      float voltage = analogRead(A0) * (5.0 / 1023.0);
      Serial.print("Odczyt z A0: ");
      Serial.print(voltage);
      Serial.println(" [V]");
    } else if (option == "BUTTON?#") {
      Serial.print("Odczyt BUTTON");
      Serial.println(digitalRead(BUTTON));
    } else if (option == "SET_D0#") {
      digitalWrite(D0, HIGH);
    } else if (option == "SET_D1#") {
      digitalWrite(D1, HIGH);
    } else if (option == "RESET_D0#") {
      digitalWrite(D0, LOW);
    } else if (option == "RESET_D1#") {
      digitalWrite(D1, LOW);
    }
  }
}
