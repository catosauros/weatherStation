#include "DHT.h"
#define DHTTYPE DHT22

// #include <LiquidCrystal.h>
// const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,  20, 4);

#include <avr/sleep.h> 

#define DHTPIN 52
#define RAINDROPPIN A0
#define LIGHTPIN A1
#define MOTORPIN A7
#define SOLARPIN A8
#define BATPIN A9
#define BUTPIN 2 //2, 3, 18, 19 for intterupt pin

volatile bool buttonPressed;
volatile bool watchdogBarked;

#define DELAY 1000

DHT dht(DHTPIN, DHTTYPE);

// byte heart[8] = {
//   0b00000,
//   0b01010,
//   0b11111,
//   0b11111,
//   0b11111,
//   0b01110,
//   0b00100,
//   0b00000
// };

// byte robot[8] = {
//   0b00000,
//   0b10001,
//   0b11111,
//   0b10101,
//   0b11111,
//   0b10001,
//   0b11111,
//   0b00000
// };

// byte cat[8] = {
//   0b00000,
//   0b10001,
//   0b11111,
//   0b10101,
//   0b11011,
//   0b10101,
//   0b11111,
//   0b00000
// };


void setup() {
  Serial.begin(9600);

  dht.begin();

  // direct 
  // lcd.begin(20, 4);
  
  // i2c
  lcd.init();
  //lcd.backlight();

  pinMode(BUTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTPIN), handleButton, LOW);

  setupWatchdog();
  pinMode(LED_BUILTIN, OUTPUT);
  // lcd.print("beeb boop");
  // lcd.createChar(0, heart);
  // lcd.createChar(1, robot);
  // lcd.createChar(2, cat);
  // lcd.setCursor(10, 0);
  // lcd.write(byte(1));
  // lcd.setCursor(0, 1);
  // lcd.write(byte(0));
  // lcd.setCursor(1, 1);
  // lcd.write(byte(2));
}

void loop() {

  if (watchdogBarked) {
    watchdogBarked = false;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // float h = dht.readHumidity();
  // float t = dht.readTemperature();
  
  // if (isnan(h) || isnan(t)) {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  // }

  // // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  // int raindrops = analogRead(RAINDROPPIN);
  // int light = analogRead(LIGHTPIN);

  // int motor = analogRead(MOTORPIN);
  // int solar = analogRead(SOLARPIN);
  // int bat = analogRead(BATPIN);

  if (buttonPressed) {
    lcd.display();
    lcd.backlight();

    yawnAnim();

    lcd.clear();
    lcd.noBacklight();
    lcd.noDisplay();
    buttonPressed = false;
  }

  goToSleep();
  //delay(DELAY);
}

void handleButton() {
 buttonPressed = true;
}


void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();

  sleep_disable();
}

void setupWatchdog() {
  MCUSR &= ~(1<<WDRF); // Clear reset flag
  WDTCSR |= (1<<WDCE) | (1<<WDE); // Enable configuration
  WDTCSR = (1<<WDIE) | (1<<WDP3); // Interrupt only, 8s timeout
}

ISR(WDT_vect) {
  watchdogBarked = true;
}

// lcd prints
void lcdPrintStats(float t, float h, float hic, int raindrops, int light, int motor, int solar, int bat) {
  lcd.setCursor(0, 0);
  lcd.print("t ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C h ");
  lcd.print(h);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("f ");
  lcd.print(hic);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 2);
  lcd.print("L");
  lcd.print(light);
  lcd.print(" R");
  lcd.print(raindrops);
  lcd.print(" W");
  lcd.print(motor);

  lcd.setCursor(0, 3);
  lcd.print("S");
  lcd.print(solar);
  lcd.print(" B");
  lcd.print(bat);
}

// animations

void rainAnim() {
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(3, i);
    lcd.print("|");
    lcd.setCursor(5, (i+2)%4);
    lcd.print("|");
    lcd.setCursor(7, (i+1)%4);
    lcd.print("|");
    lcd.setCursor(9, i);
    lcd.print("|");
    lcd.setCursor(11, (i+2)%4);
    lcd.print("|");
    lcd.setCursor(13, (i+3)%4);
    lcd.print("|");
    delay(80);
    lcd.clear();
  }
} 

void yawnAnim(){
    lcd.setCursor(5, 1);
    lcd.print("yawn! >_<");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("going back to sleep!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print("zzzzzzzzzz");
    delay(1000);
}
// debug

void serialPrintStats(float t, float h, float hic, int raindrops, int light, int motor, int solar, int bat) {
  Serial.print(("Humidity: "));
  Serial.print(h);
  Serial.print(("%  Temperature: "));
  Serial.print(t);
  Serial.print(("°C "));
  Serial.print(("°C  Heat index: "));
  Serial.print(hic);
  Serial.print(("°C "));
  Serial.print("Raindrops: ");
  Serial.print(raindrops);
  Serial.print(" Light: ");
  Serial.println(light);

  Serial.println(motor);
  Serial.print("Solar: ");
  Serial.print(solar);
  Serial.print(", Battery: ");
  Serial.println(bat);
}