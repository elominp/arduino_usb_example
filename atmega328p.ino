void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
}

const uint8_t eot[2] = {27, 0};

void loop() {
  // put your main code here, to run repeatedly:
  /* Serial.print(F("KBD\r\n"));
  Serial.print(F("Hello Everybody"));
  Serial.print((char *)eot);
  delay(1000); */
  Serial.print(F("CDC\r\n"));
  Serial.println(F("Hello CDC Serial"));
  Serial.print((char *)eot);
  delay(1000);
  Serial.print(F("MOUSE\r\n"));
  Serial.println(F("100;-100"));
  Serial.print((char *)eot);
  delay(1000);
}
