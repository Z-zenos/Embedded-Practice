int ledPin = 9;
int btnPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  int btnValue = digitalRead(btnPin);

  if(btnValue == LOW) {
    digitalWrite(ledPin, HIGH);
    delay(2000);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

/*
https://docs.wokwi.com/parts/wokwi-pushbutton

Bản chất bên trong cái nút này nó là 1 khóa K, khi mình nhấn
thì khóa K đóng, bỏ nhấn -> khóa K mở.

Nếu ta nối 2 chân 2.l và 2.r (hoặc 1.l và 1.r) vào arduino nghĩa là 
dòng điện đã được thông qua và giá trị của btn được đọc vào 
mặc định sẽ là HIGH.

Vì thế ta phải nối 2 chân lệch nhau như: 2.l và 1.r hoặc 1.l và 2.r


Lí do giá trị của nút bấm khi được bấm là LOW vì khi nhấn khóa K đóng
đoạn mạch trong nút được thông nhau và dòng điện sẽ đi qua đó và xuống
đất -> không có điện áp -> LOW

*/