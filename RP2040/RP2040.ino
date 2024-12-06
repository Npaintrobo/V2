
const int PWM5_1 = 0;
const int PWM5_2 = 1;
const int PWM6_1 = 2;
const int PWM6_2 = 3;
const int PWM7_1 = 4;
const int PWM7_2 = 5;
const int PWM8_1 = 6;
const int PWM8_2 = 7;

void setup() {
  Serial.begin(115200);
  pinMode(
}

void loop() {
  if (Serial.available() > 0 ) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Receive:");
    Serial.println(data);
  }
}
