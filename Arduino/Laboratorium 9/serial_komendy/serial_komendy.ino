const int D0 = 12;
const int D1 = 8;
const int  BUTTON = 2;
String option;
int Dp;
char readByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // definicja startu serial portu
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // theoretically this should fetch entire string from Serial up to '#' symbol
    // will test it later
    while (readByte != '#') {
      readByte = Serial.read();
      option += readByte;
    }

    Serial.println(option); // for debug purposes
    
    // still in bullshit state, there is a better way to handle it
    if (option == "ADC?#") {
      
      float voltage = analogRead(A0) * (5.0 / 1023.0);
      Serial.print("A0 voltage: ");
      Serial.print(voltage);
      Serial.println(" [V]");
      
    } else if (option == "BUTTON?#") {
      
      Serial.print("BUTTON state: ");
      Serial.println(digitalRead(BUTTON));
      
    } else if (option == "SET") {
      
      digitalWrite(Dp, HIGH);
      
    } else if (option == "RESET") {
      
      digitalWrite(Dp, LOW);
      
    }
  }
}
