/* Podstawy Techniki mikroprocesorowej - Arduino 2
 * Kamil Kasperski 
 * Dzięki temu programowi Arduino może orzymywać podstawowe komendy przez Serial Port.
 * 
 * Komendy wbudowane:
 * ADC? - zczytuje napięcie na potencjometrze
 * BUTTON? - zczytuje stan przycisku
 * SET - ustawia wartość HIGH na cyfrowym porcie SKLADNIA - SET_D0 lub SET_D1 - Hardcoded
 * RESET - ustawia wartość LOW na cyfrowym porcie SKŁADNIA - RESET_D0 lub RESET_D1 - Hardcoded
 * PWM - Ustawia odpowiednią wartośćnapęcia na cyfrowym porcie. użyto analogWrite() SKŁADNIA - PWM_DX VAL
 * 
 * Użyto pętli 'while' do parsowania komend. Każda komenda winna się kończyć #
 */
const int D0 = 11;   // LED0 = This port supports PWM!!!
const int D1 = 10;   // LED1 = This port supports PWM!!!
const int  BUTTON = 2;    // BUTTON
char serial_cmd[15];    // komenda z Serial portu
char readByte;          // zmienna pomocnicza do zczytywania znaków

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // definicja startu serial portu

  // definicja wszystkich wejść i wyjść
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop () {
  // zmienne lokalne
  int Dp;
  static int index = 0;
  String option;
  String spwm_val;
  int pwr;
  
  if (Serial.available()) {   // Sprawdzamy czy zostały wysłane komendy
    readByte = Serial.read(); // zczytujemy znaki
    if (readByte != '#') {    // dopóki nie trafimy na znak końca komendy '#'
      serial_cmd[index] = readByte; // do listy znaków dodajemy kolejne zczytane znaki
      index++;  // zwiększamy indeks
    } else {  // po zakończeniu zczytywtania znaków

      index = 0;  // zerujemy indeks by zacząć tłumaczyć komendę dla arduino od początku
      // te 3 pętle będą po kolei sprawdzać czy jesteśmy na końcu, czy natrafiliśmy na jakiś
      // specjalny znak typu '_' lub ' '.
      while (serial_cmd[index] != '\0') {
        if (serial_cmd[index] == '_') {
          index++;
          break;
        }
        option += serial_cmd[index];
        index++;
      }
      // tutaj zczytujemy który port ma być wybrany - 0 czy 1
      while (serial_cmd[index] != '\0') {
        if (serial_cmd[index] == ' ') {
          index++;
          break;
        }
        if (serial_cmd[index] == '0') {
          Dp = D0;
          index++;
          break;
        } else if (serial_cmd[index] == '1') {
          Dp = D1;
          index++;
          break;
        }
        index++;
      }
      // tutaj zczytujemy wartość dla ustawienia jasności diody
      while (serial_cmd[index] != '\0') {
        spwm_val += serial_cmd[index];
        index++;
      }

      // właściwa definicja komend
      if (option == "ADC?") {
        float voltage = analogRead(A0) * (5.0 / 1023.0);    // ze wzoru ze strony Arduino
        Serial.print("A0 voltage: ");
        Serial.print(voltage);
        Serial.println(" [V]");

      } else if (option == "BUTTON?") {
        Serial.print ("BUTTON State: ");
        Serial.println (!digitalRead(BUTTON));    // zczytuje stan przycisku. Wartość musi być odwrócowa przez podłączenie do GND

      } else if (option == "SET") {
        digitalWrite(Dp , HIGH);
        Serial.print(Dp);
        Serial.println(" Pin turned on.");

      } else if (option == "RESET") {
        digitalWrite (Dp , LOW);
        Serial.print(Dp);
        Serial.println(" Pin turned off.");

      } else if (option == "PWM") {
        int pwm_val = (255 * spwm_val.toInt()) / 100;   // z proporcji 
        analogWrite(Dp, pwm_val);
        Serial.print(Dp);
        Serial.print(" Pin Light value set: ");
        Serial.print(pwm_val);
        Serial.print(" - ");
        Serial.print(spwm_val.toInt());
        Serial.println("%");

      } else {
        Serial.println("Incorrect command.");   // zabezpieczenie przed zlymi komendami

      }
      // czyszczenie buforu komendy i indeksu
      for (int i=0; i < sizeof(serial_cmd); i++) {
        serial_cmd[i] = '\0';
      }
      index = 0;
    }
  }
}
