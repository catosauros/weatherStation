
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define DHTPIN 52     // Digital pin connected to the DHT sensor
#define RAINDROPPIN A0
#define LIGHTPIN A1

#define DELAY 1000

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RAINDROPPIN, INPUT);
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  int raindrops = analogRead(RAINDROPPIN);
  int light = analogRead(LIGHTPIN);
  
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

  delay(DELAY);
}
