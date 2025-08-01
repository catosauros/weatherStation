#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 52     // Digital pin connected to the DHT sensor
#define RAINDROPPIN A0
#define LIGHTPIN A1
#define MOTORPIN A7
#define SOLARPIN A8
#define BATPIN A9

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
  lcd.begin(20, 4);

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
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  int raindrops = analogRead(RAINDROPPIN);
  int light = analogRead(LIGHTPIN);

  int motor = analogRead(MOTORPIN);
  int solar = analogRead(SOLARPIN);
  int bat = analogRead(BATPIN);
  
  // Serial.print(("Humidity: "));
  // Serial.print(h);
  // Serial.print(("%  Temperature: "));
  // Serial.print(t);
  // Serial.print(("°C "));
  // Serial.print(("°C  Heat index: "));
  // Serial.print(hic);
  // Serial.print(("°C "));
  // Serial.print("Raindrops: ");
  // Serial.print(raindrops);
  // Serial.print(" Light: ");
  // Serial.println(light);

  // Serial.println(motor);
  // Serial.print("Solar: ");
  // Serial.print(solar);
  // Serial.print(", Battery: ");
  // Serial.println(bat);

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

  delay(DELAY);
}
