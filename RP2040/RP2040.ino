#include <Arduino.h>

// Motor PWM pins
const int PWM5_1 = 2;
const int PWM5_2 = 3;
const int PWM6_1 = 4;
const int PWM6_2 = 5;
const int PWM7_1 = 6;
const int PWM7_2 = 7;
const int PWM8_1 = 8;
const int PWM8_2 = 9;

int MOTOR5, MOTOR6, MOTOR7, MOTOR8;
byte direction;

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

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(PWM5_1, OUTPUT);
  pinMode(PWM5_2, OUTPUT);
  pinMode(PWM6_1, OUTPUT);
  pinMode(PWM6_2, OUTPUT);
  pinMode(PWM7_1, OUTPUT);
  pinMode(PWM7_2, OUTPUT);
  pinMode(PWM8_1, OUTPUT);
  pinMode(PWM8_2, OUTPUT);
}

void loop() {
  if (Serial1.available() >= 7) {  // 5 bytes data + 1 byte CRC +/n
    byte dataReceived[5];
    for (int i = 0; i < 5; i++) {
      dataReceived[i] = Serial1.read();
    }
    uint8_t receivedCRC = Serial1.read();
    uint8_t calculatedCRC = computeCRC8(dataReceived, 5);

    if (receivedCRC == calculatedCRC) {
      direction = dataReceived[0];
      MOTOR5 = dataReceived[1];
      MOTOR6 = dataReceived[2];
      MOTOR7 = dataReceived[3];
      MOTOR8 = dataReceived[4];

      Serial.print("direction:");
      Serial.print(direction & 0x01);
      Serial.print((direction & 0x02) >> 1);
      Serial.print((direction & 0x04) >> 2);
      Serial.print((direction & 0x08) >> 3);
      Serial.print(" MOTOR5: ");
      Serial.print(MOTOR5);
      Serial.print(" MOTOR6: ");
      Serial.print(MOTOR6);
      Serial.print(" MOTOR7: ");
      Serial.print(MOTOR7);
      Serial.print(" MOTOR8: ");
      Serial.println(MOTOR8);
      setMotor(PWM5_1, PWM5_2, (direction & 0x01), MOTOR5);
      setMotor(PWM6_1, PWM6_2, (direction & 0x02) >> 1, MOTOR6);
      setMotor(PWM7_1, PWM7_2, (direction & 0x04) >> 2, MOTOR7);
      setMotor(PWM8_1, PWM8_2, (direction & 0x08) >> 3, MOTOR8);
    } else {
      //Serial.println("CRC error, data is invalid.");
    }
  }
}


void setMotor(int pin1, int pin2, bool dir, int speed) {
  if (dir == 0) {
    analogWrite(pin1, speed);
    analogWrite(pin2, 0);
  } else {
    analogWrite(pin1, 0);
    analogWrite(pin2, speed);
  }
}
