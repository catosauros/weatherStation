void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // if (Serial1.available()) {
  //   char inByte = Serial1.read();

  //   Serial.write(inByte);
  //   Serial.write('\n');
  //   delay(1000);
  // }
  Serial.write('A');
  delay(1000);
}
