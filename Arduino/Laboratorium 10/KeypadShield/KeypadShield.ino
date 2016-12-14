/*  Podstawy Techniki mikroprocesorowej - Arduino 3
 *  Kamil Kasperski
 *  Program wymaga Arduino UNO i DFRobot Keypad Shield
 *  
 *  W programie z MENU możemy wybrać jeden z trzech podprogramów:
 *  Button test - pokazuje aktualnie wciśnięty przycisk
 *  Button count - zlicza ilość wciśnięć każdego przycisku z osobna
 *  Values changer - zmienia wartości trzech zmiennych typu:
 *      integer (co 1)
 *      float (co 0.1)
 *      bool (true / false)
 *      
 *  Każdy podprogram po wybraniu wymaga restartu arduino by zakończyć jego pracę (while nieskończony). Na razie nie chce mi się tego zmieniać.
 */    

#include <LiquidCrystal.h>    // WYMAGANA biblioteka do obsługi LCD

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);    // konstruktor ekranu LCD - porty ustalone wg schematu DFRobot Keypad Shield

// definicja stałych
#define RIGHT   0
#define UP      1
#define DOWN    2
#define LEFT    3
#define SELECT  4
#define NONE    5

static String option_list[] = {"Button Test   ", "Button count  ", "Values changer  "};

//funkcja do zmiany indeksu - by nie powielać kodu
int index_change(int btn, int index) { 
  switch (btn) {
    case UP: {
      index--;
      break;
    }
    case DOWN: {
      index++;
      break;
    }
  }
  
  if (index > 2) {
    return 0;
  } else if (index < 0) {
    return 2;
  } else {
    return index;
  }
}

// funkcja do pobierania jaki przycisk został wciśnięty - z dokumentacji DFRobot Keypad Shield
int btn_read() {
  int btn = analogRead(0);

  if (btn < 50) {
    return RIGHT;
  }
  if (btn < 195) {
    return UP;
  }
  if (btn < 380) {
    return DOWN;
  }
  if (btn < 555) {
    return LEFT;
  }
  if (btn < 790) {
    return SELECT;
  }
  
  return NONE;
}

// funkcja pomocnicza do wywoływania innych podfunkcji po przyciśnięciu SELECT
void call_func(int index) {
  switch (index) {
    case 0: {
      lcd.clear();
      while (true) {
        btn_test();
      }
      break;
    }
    case 1: {
      lcd.clear();
      while (true) {
        btn_count();
      }
      break;
    }
    case 2: {
      lcd.clear();
      while (true) {
        val_incr();
      }
      break;
    }
  }
}

// właściwe podprogramy
// button counter
void btn_count() {
  lcd.setCursor(0,0);
  lcd.print("Button counter");
  lcd.setCursor(0,1);

  // deklaracja zmiennych zliczających
  static int countSEL = 0;
  static int countUP = 0;
  static int countDOWN = 0;
  static int countLEFT = 0;
  static int countRIGHT = 0;

  int btn = btn_read();
  
  switch (btn) {
    case UP: {
      countUP++;
      lcd.print("UP count        ");
      lcd.setCursor(9,1);
      lcd.print(countUP);
      break;
    }
    case DOWN: {
      countDOWN++;
      lcd.print("DOWN count      ");
      lcd.setCursor(11,1);
      lcd.print(countDOWN);
      break;
    }
    case LEFT: {
      countLEFT++;
      lcd.print("LEFT count      ");
      lcd.setCursor(11,1);
      lcd.print(countLEFT);
      break;
    }
    case RIGHT: {
      countRIGHT++;
      lcd.print("RIGHT count     ");
      lcd.setCursor(12,1);
      lcd.print(countRIGHT);
      break;
    }
    case SELECT: {
      countSEL++;
      lcd.print("SELECT count    ");
      lcd.setCursor(13,1);
      lcd.print(countSEL);
      break;
    }
    case NONE:{
      break;
    }
  }
  delay(150); // opóźnienie by program zbytnio nie szalał...
}

// button tester
void btn_test() {
  lcd.setCursor(0,0);
  lcd.print("Button tester");
  lcd.setCursor(0,1);
  
  int btn = btn_read();
  
  switch (btn) {
    case UP: {
      lcd.print("UP              ");
      break;
    }
    case DOWN: {
      lcd.print("DOWN            ");
      break;
    }
    case LEFT: {
      lcd.print("LEFT            ");
      break;
    }
    case RIGHT: {
      lcd.print("RIGHT           ");
      break;
    }
    case SELECT: {
      lcd.print("SELECT          ");
      break;
    }
    case NONE: {
      lcd.print("                ");
      break;
    }
  }
}

// value changer - shitcode
void val_incr() {

  lcd.setCursor(0,0);
  lcd.print("Values changer  ");
  lcd.setCursor(0,1);

  int btn = btn_read();

  static int integer_val = 0;
  static float float_val = 0;
  static bool bool_val = false;
  static String options[] = {"Integer         ", "Float           ", "Bool            "};
  static int sub_index = 0;
  
  switch (btn) {
    case UP: {
      sub_index = index_change(btn, sub_index);
      lcd.print(options[sub_index]);
      lcd.setCursor(9,1);
  
      switch (sub_index) {
        case 0: lcd.print(integer_val); break;
        case 1: lcd.print(float_val); break;
        case 2: {
          if (bool_val == false) {
            lcd.print("false");
          } else {
            lcd.print("true");
          }
        }
      }
      
      break;
    }
    case DOWN: {
      sub_index = index_change(btn, sub_index);
      lcd.print(options[sub_index]);
      lcd.setCursor(9,1);
      
      switch (sub_index) {
        case 0: lcd.print(integer_val); break;
        case 1: lcd.print(float_val); break;
        case 2: {
          if (bool_val == false) {
            lcd.print("false");
          } else {
            lcd.print("true");
          }
        }
      }
      break;
    }
    case LEFT: {
      lcd.print(options[sub_index]);
      lcd.setCursor(9,1);
      switch (sub_index) {
        case 0: integer_val--; lcd.print(integer_val); break;
        case 1: float_val -= 0.1; lcd.print(float_val); break;
        case 2: {
          bool_val = !bool_val;
          if (bool_val == false) {
            lcd.print("false");
          } else {
            lcd.print("true");
          }
          break;
        }
      }
      break;
    }
    case RIGHT: {
      lcd.print(options[sub_index]);
      lcd.setCursor(9,1);
      switch (sub_index) {
        case 0: {
          integer_val++;
          lcd.print(integer_val);
          break;
        }
        case 1: {
          float_val += 0.1;
          lcd.print(float_val);
          break;
        }
        case 2: {
          bool_val = !bool_val;
          if (bool_val == false) {
            lcd.print("false");
          } else {
            lcd.print("true");
          }
          break;
        }
      }
      break;
    }
    case SELECT:{
      lcd.print(options[sub_index]);
      lcd.setCursor(9,1);
  
      switch (sub_index) {
        case 0: lcd.print(integer_val); break;
        case 1: lcd.print(float_val); break;
        case 2: {
          if (bool_val == false) {
            lcd.print("false");
          } else {
            lcd.print("true");
          }
        }
      }
      break;
    }
    case NONE: {     
      break;
    }
  }
  delay(150);  // wymagany delay by program zbytnio nie szalał...
}

void setup() {
  // pierwsze uruchomienie wyświetlacza i wyświetlenie informacji z głównego menu
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Menu:");
  lcd.setCursor(0,1);
  lcd.print("~ ");
  lcd.print(option_list[0]);
}

void loop() {
  // główne menu
  int btn = btn_read();
  static int index = 0;
  
  lcd.setCursor(2,1);
  switch (btn) {
    case SELECT: {
      call_func(index);
      break;
    }
    case UP: {
      // lista do góry
      index = index_change(btn, index);
      lcd.print(option_list[index]);
      break;
    }
    case DOWN: {
      // lista w dół
      index = index_change(btn, index);
      lcd.print(option_list[index]);
      break;
    }
    case NONE: {
      break;
    }
  }
  delay(250);  // wymagany delay by program zbytnio nie szalał...
}
