// NAME: OpenServo-HWTest-FW.ino

#include <Wire.h>

#define EN_A    2  // PD2, pin 32
#define EN_B    3  // PD3, pin 1
#define SMPL_B  4  // PD4, pin 2
#define SMPL_A  7  // PD7, pin 11
#define PWM_A   9  // PB1, pin 13
#define PWM_B   10 // PB2, pin 14

uint16_t current, voltage, position, tempv, bemf;

void i2cTransmitter() {
  Wire.write((uint8_t*)&current, 2);
  Wire.write((uint8_t*)&voltage, 2);
  Wire.write((uint8_t*)&position, 2);
  Wire.write((uint8_t*)&tempv, 2);
  Wire.write((uint8_t*)&bemf, 2);
}

void setup() {
  Wire.begin(0x10);
  Wire.onRequest(i2cTransmitter);

  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  digitalWrite(PWM_A, LOW);
  digitalWrite(PWM_B, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(EN_A, LOW);
}

void loop() {
  current = analogRead(A0);
  voltage = analogRead(A1);
  position = analogRead(A2);
  tempv = analogRead(A3);
  bemf = analogRead(A7);

  if (position > 513) {
    digitalWrite(PWM_B, LOW);
    digitalWrite(EN_B, LOW);
    delay(1);
    uint8_t pwm = (position-512) / 2;
    analogWrite(PWM_A, pwm);
    digitalWrite(EN_A, HIGH);
  } else if (position < 511) {
    digitalWrite(PWM_A, LOW);
    digitalWrite(EN_A, LOW);
    delay(1);
    uint8_t pwm = (511-position) / 2;
    analogWrite(PWM_B, pwm);
    digitalWrite(EN_B, HIGH);
  } else {
    digitalWrite(PWM_A, LOW);
    digitalWrite(EN_A, LOW);
    digitalWrite(PWM_B, LOW);
    digitalWrite(EN_B, LOW);
    delay(1);
  }
}
