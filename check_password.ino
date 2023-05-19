#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// set the LCD address to 0x27 for a 16 chars and 2 line display

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int ledPin = 12;
String correct_pwd = "121812";
String user_input = "";
int i = 0;
int currentCursor = 0;

void setup() {
	pinMode(ledPin, OUTPUT); // configure pin for controlling led
  Serial.begin(9600); //  Init serial monitor
  lcd.init();	// initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Pass <number>: ");
	lcd.setCursor(currentCursor, 1);
}

void lcd_clear_line(int line) {
	lcd.setCursor(0, line - 1);
	for(int j = 0; j < 16; j++) {
		lcd.print(" ");
	}
}

void loop() { 
	char key = keypad.getKey();

  if (key != NO_KEY) {
		if(key == 'C') {
			Serial.println("Before: " + user_input);
			lcd.setCursor(0, 1);
			if(user_input == correct_pwd) {
				lcd.print("Correct !");
				digitalWrite(ledPin, HIGH);
				delay(4000);
				digitalWrite(ledPin, LOW);
			}
			else {
				lcd.print("Incorrect !");
				delay(2000);
				lcd_clear_line(2);
				lcd.setCursor(0, 1);
				lcd.print("Try again !");
				delay(2000);
				lcd_clear_line(2);
				user_input = "";
				currentCursor = 0;
				// i = 0;
				Serial.println("wrong: " + user_input);
			}
		}
		else {
			lcd.print(key);
			user_input += key;
			// i++;
			delay(500);
			lcd.setCursor(currentCursor, 1);
			lcd.print('*');
			++currentCursor;
			lcd.setCursor(currentCursor, 1);
		}
  }
}