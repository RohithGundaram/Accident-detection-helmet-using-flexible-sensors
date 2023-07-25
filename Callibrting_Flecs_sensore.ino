int val1 = 0;
//int val2 = 0;
//int val3 = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = analogRead(34);
//  val2 = analogRead(32);
//  val3 = analogRead(34);
  Serial.print(val1);
//  Serial.print(val2);
//  Serial.print(val3);
  Serial.print('\n');
  delay(1000);

}
