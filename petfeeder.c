#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;  // create servo object to control the pet feeder
LiquidCrystal_I2C lcd(0x27, 16, 2);  // create LCD object

int pos = 0;    // variable to store the servo position
int feedTime = 12;  // set the feeding time to 12:00 PM

void setup() {
  myservo.attach(D1);  // attach the servo to pin D1
  lcd.init();  // initialize the LCD
  lcd.backlight();  // turn on the backlight
  lcd.setCursor(0,0);  // set the cursor to the top row
  lcd.print("Pet Feeder");  // print the title
}

void loop() {
  // get the current time
  int hour = hourFormat12();
  int minute = minute();

  // display the time on the LCD
  lcd.setCursor(0,1);  // set the cursor to the second row
  lcd.print("Time:");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);

  // check if it's time to feed the pet
  if (hour == feedTime && minute == 0) {
    feedPet();  // call the feedPet function
  }

  delay(1000);  // wait for 1 second before checking the time again
}

void feedPet() {
  // rotate the servo to dispense the food
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  delay(1000);  // wait for 1 second

  // rotate the servo back to its original position
  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
