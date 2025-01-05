#include <ESP32-TWAI-CAN.hpp>
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
  int direction;
  int MOTOR5;
  int MOTOR6;
  int MOTOR7;
  int MOTOR8;
  int MOTOR5d;
  int MOTOR6d;
  int MOTOR7d;
  int MOTOR8d;

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
  ledcAttachPin(PWM3_1, 4); 
  ledcAttachPin(PWM3_2, 5); 
  ledcAttachPin(PWM4_1, 6); 
  ledcAttachPin(PWM4_2, 7);
  
  //LOW
  digitalWrite(PWM1_1, LOW);
  digitalWrite(PWM1_2, LOW);
  digitalWrite(PWM2_1, LOW);
  digitalWrite(PWM2_2, LOW);
  digitalWrite(PWM3_1, LOW);
  digitalWrite(PWM3_2, LOW);
  digitalWrite(PWM4_1, LOW);
  digitalWrite(PWM4_2, LOW);
}

uint8_t computeCRC8(uint8_t *data, size_t len) {
  uint8_t crc = 0xFF;
  for (size_t i = 0; i < len; ++i) {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x31;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void loop() {
  direction = (MOTOR8d << 3) | (MOTOR7d << 2) | (MOTOR6d << 1) | MOTOR5d;
  byte dataToSend[5] = {static_cast<byte>(direction), static_cast<byte>(MOTOR5), static_cast<byte>(MOTOR6), static_cast<byte>(MOTOR7), static_cast<byte>(MOTOR8)};
  uint8_t crc = computeCRC8(dataToSend, sizeof(dataToSend));
  Serial.write(dataToSend, sizeof(dataToSend));
  Serial.write(crc);
  Serial.pritnt("\n")
}
