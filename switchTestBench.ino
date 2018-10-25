const int buttonPin = 6;    // the number of the pushbutton pin
#define INTERVAL_1 60
#define INTERVAL_2 80
#define INTERVAL_3 2000
unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long previousMillis = 0;
int upDate = true;
int holdOff = HIGH;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

#define strobe 5
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int DIN = 9;
int CLK = 8;
int LE  = 7;
byte inputValue = 0;
void setup() {
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(strobe,OUTPUT);
  pinMode(DIN, OUTPUT);     
  pinMode(CLK, OUTPUT);     
  pinMode(LE , OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(strobe,HIGH);
//  digitalWrite(resetLow,LOW);
  delay(1000);
//  digitalWrite(resetLow,HIGH);
  delay(1000);
//  previousMillis = millis();
digitalWrite(DIN,LOW);
for (int i = 0;i <20;i++)
  {
     clk();  
  }
  latch();
}

void loop() {
  int reading = digitalRead(buttonPin);
  lcd.setCursor(0,0);
  if(upDate == true)
    { 
      portDAdd(inputValue);
      inputValue++;
      if(inputValue >5)
          {
            inputValue = 0;
            }
      upDate = false;
    }
  if((millis()  > time_1 + INTERVAL_1) && (holdOff)){
        time_1 = millis();
        digitalWrite(strobe,LOW);
    }
  if((millis()  > time_2 + INTERVAL_2) && (holdOff)){
        time_2 = millis();
        digitalWrite(strobe,HIGH);

        
    }
  if(millis()  > time_3 + INTERVAL_3){
       time_3 = millis();
       holdOff = HIGH;
  }
  else
    {
      holdOff = LOW; 
    }
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
    if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
            upDate = true;

        }
      }
    }
      lastButtonState = reading;
}

int portDAdd(byte Value)
  {
    int a = 0;
    if (Value >=15)
      {
        Value = 0;
        a = 1;
      }
    switch (Value){
      case 0:
        lcd.print("Channel 1    ");
        max_write(HIGH);
       digitalWrite(0,LOW);
        digitalWrite(1,LOW);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
      digitalWrite(4,LOW);
       break;
     case 1:
        lcd.print("Channel 2    ");
        max_write(LOW);
        digitalWrite(0,HIGH);
        digitalWrite(1,LOW);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
       case 2:
        lcd.print("Channel 3    ");
        max_write(LOW);
        digitalWrite(0,LOW);
        digitalWrite(1,HIGH);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
      case 3:
        lcd.print("Channel 4    ");
        max_write(LOW);
        digitalWrite(0,HIGH);
        digitalWrite(1,HIGH);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
      case 4:
        lcd.print("White Balance   ");
        max_write(LOW);
        digitalWrite(0,LOW);
        digitalWrite(1,LOW);
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
      case 5:
        lcd.print("Dark refrence   ");
        max_write(LOW);
        digitalWrite(0,HIGH);
        digitalWrite(1,LOW);
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
       default:
//        Serial.println("Not sure why im here?");
        digitalWrite(0,LOW);
        digitalWrite(1,LOW);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
       digitalWrite(4,LOW);
       break;
    }
    return a;
  }
  void clk() {
  digitalWrite(CLK, LOW);
  digitalWrite(CLK, HIGH);
}

void latch() {
  digitalWrite(LE, LOW);
  digitalWrite(LE, HIGH);
}

void max_write(boolean data) {
  digitalWrite(DIN, data);
  clk();
  latch();
}

