#include <LiquidCrystal_I2C.h>
#include <string.h>

using namespace std;

#define LDR_PIN 2

// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

LiquidCrystal_I2C lcd(0x27, 20, 4);


const int whitePin = 0;

const int redPin1 = 7;
const int yellowPin1 = 6;
const int greenPin1 = 5;

const int redPin2 = 12;
const int yellowPin2 = 11;
const int greenPin2 = 10;

void lcd_print(int line, int pos, String str) {
  lcd.setCursor(pos, line - 1);
  lcd.print(str);
}

void lcd_print(int line, int pos, int number) {
  lcd.setCursor(pos, line - 1);
  lcd.print(number);
}

void setup() {
  pinMode(LDR_PIN, INPUT);

  pinMode(whitePin, OUTPUT);

  pinMode(redPin1, OUTPUT);
  pinMode(yellowPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);

  pinMode(redPin2, OUTPUT);
  pinMode(yellowPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);

  lcd.init();
  lcd.backlight();


  lcd_print(1, 0, "Status");
  lcd_print(3, 0, "Lamp");

  lcd_print(1, 12, "R");
  lcd_print(1, 15, "Y");
  lcd_print(1, 18, "G");

  lcd_print(3, 12, "R");
  lcd_print(3, 15, "Y");
  lcd_print(3, 18, "G");
}

void lcd_clear_half_line(int line, String pos) {
  lcd.setCursor(0, line - 1);
  if(pos == "before") {
    for(int i = 0; i < 10; i++) {
      lcd.setCursor(i, line - 1);
      lcd.print(" ");
    }
  }
  else if(pos == "after") {
    for(int i = 10; i < 20; i++) {
      lcd.setCursor(i, line - 1);
      lcd.print(" ");
    }
  }
}

void turn_off_all_traffic_light() {
  digitalWrite(redPin1, LOW);
  digitalWrite(greenPin1, LOW);
  digitalWrite(yellowPin1, LOW);
  digitalWrite(redPin2, LOW);
  digitalWrite(greenPin2, LOW);
  digitalWrite(yellowPin2, LOW);
}

void display_traffic_light(String type) {
  int pos;
  int revPos;

  turn_off_all_traffic_light();
  lcd_clear_half_line(2, "after");
  lcd_clear_half_line(4, "after");

  if(type == "green") {
    pos = 18; 
    revPos = 12;
    digitalWrite(greenPin2, HIGH);
    digitalWrite(redPin1, HIGH);
  }
  else if(type == "yellow") {
    pos = revPos = 15; 
    digitalWrite(yellowPin1, HIGH);
    digitalWrite(yellowPin2, HIGH);  
  }
  else if(type == "red") {
    pos = 12;
    revPos = 18;
    digitalWrite(greenPin1, HIGH);
    digitalWrite(redPin2, HIGH);
  }


  lcd_print(2, pos, 10);
  lcd_print(4, revPos, 10);
  lcd_print(2, pos + 1, " ");
  lcd_print(4, revPos + 1, " ");
  for(int i = 9; i >= 0; i--) {
    lcd_print(2, pos, i);
    lcd_print(4, revPos, i);
    delay(1000);
  }
}

void loop() {
  int analogValue = analogRead(A0);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  if (lux > 50) {
    digitalWrite(whitePin, LOW);
    lcd_clear_half_line(2, "before");
    lcd_print(2, 0, "Day");

    lcd_clear_half_line(4, "before");
    lcd_print(4, 0, "OFF");
  } else {
    digitalWrite(whitePin, HIGH);
    lcd_clear_half_line(2, "before");
    lcd_print(2, 0, "Night");

    lcd_clear_half_line(4, "before");
    lcd_print(4, 0, "ON");
  }

  display_traffic_light("red");
  display_traffic_light("yellow");
  display_traffic_light("green");

  delay(1000);
}
