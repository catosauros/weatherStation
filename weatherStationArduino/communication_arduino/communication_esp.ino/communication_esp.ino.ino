void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      char inByte = Serial.read();
      // Serial.write(inByte);
      // Serial.write('\n');
    }
      delay(1000);


      // digitalWrite(LED_BUILTIN, LOW);
      // delay(500);
      // digitalWrite(LED_BUILTIN, HIGH);
      // delay(500);

}
