//Boad pin
  //CAN
  #define CAN_TX  25
  #define CAN_RX  5
  //Motor
  const int PWM1_1 = 32;
  const int PWM1_2 = 33;
  const int PWM2_1 = 27;
  const int PWM2_2 = 14;
  const int PWM3_1 = 19;
  const int PWM3_2 = 18;
  const int PWM4_1 = 16;
  const int PWM4_2 = 4;
  //Relay
  const int Relay1 = 23;
  const int Relay2 = 17;
  const int Relay3 = 13;
  const int Relay4 = 26;
  //I2C
  const int I2C_SDA = 21;
  const int I2C_SCL = 22;
  //一バイト目
  char direction;
  //MOTOR5
  char MOTOR5;
  char MOTOR6;
  char MOTOR7;
  char MOTOR8;

void setup() {
  setCpuFrequencyMhz(160);
  Serial.begin(115200);
  if (ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX, CAN_RX, 10, 10)) {
    Serial.println("CAN bus started!");
  } else {
    Serial.println("CAN bus failed!");
  }
  //pinmode
  pinMode(PWM1_1,OUTPUT);
  pinMode(PWM1_2,OUTPUT);
  pinMode(PWM2_1,OUTPUT);
  pinMode(PWM2_2,OUTPUT);
  pinMode(PWM3_1,OUTPUT);
  pinMode(PWM3_2,OUTPUT);
  pinMode(PWM4_1,OUTPUT);
  pinMode(PWM4_2,OUTPUT);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  //PWMタイマー割り当て
  ledcSetup(0, 20000, 10); 
  ledcSetup(1, 20000, 10); 
  ledcSetup(2, 20000, 10); 
  ledcSetup(3, 20000, 10); 
  ledcSetup(4, 20000, 10); 
  ledcSetup(5, 20000, 10); 
  ledcSetup(6, 20000, 10); 
  ledcSetup(7, 20000, 10); 
  ledcAttachPin(PWM1_1, 0); 
  ledcAttachPin(PWM1_2, 1); 
  ledcAttachPin(PWM2_1, 2); 
  ledcAttachPin(PWM2_2, 3);
  ledcAttachPin(PWM1_1, 4); 
  ledcAttachPin(PWM1_2, 5); 
  ledcAttachPin(PWM2_1, 6); 
  ledcAttachPin(PWM2_2, 7);
  
  //LOW
  digitalWrite(pwm1_1, LOW);
  digitalWrite(pwm1_2, LOW);
  digitalWrite(pwm2_1, LOW);
  digitalWrite(pwm2_2, LOW);
  digitalWrite(pwm3_1, LOW);
  digitalWrite(pwm3_2, LOW);
  digitalWrite(pwm4_1, LOW);
  digitalWrite(pwm4_2, LOW);
}

void loop() {
　
  Serial.println();
}
