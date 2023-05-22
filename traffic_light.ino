#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2

const int redPin = 3;
const int yellowPin = 4;
const int greenPin = 5;


LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  // Init
  lcd.init();
  lcd.backlight();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void displayTrafficLight(String type) {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);

  if(type == "green") digitalWrite(greenPin, HIGH);
  else if(type == "yellow") digitalWrite(yellowPin, HIGH);
  else if(type == "red") digitalWrite(redPin, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(type + ":");
  lcd.setCursor(0, 1);
  for(int i = 10; i >= 0; i--) {
    lcd.print(i);

    delay(1000);
    if(i == 10) {
      lcd.setCursor(1, 1);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
  }
}


void loop() {
  displayTrafficLight("green");
  displayTrafficLight("yellow");
  displayTrafficLight("red");
}
