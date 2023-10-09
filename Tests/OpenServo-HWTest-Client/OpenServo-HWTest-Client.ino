// NAME: I2C-Test-Master

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("I2C-Test-Master");
}

void loop() {
  Serial.print("Requesting data from 0x10: ");

  uint8_t data[10];
  Wire.requestFrom(0x10, sizeof(data));
  uint8_t pos = 0;
  while (Wire.available()) {
    data[pos] = Wire.read();
    Serial.print(data[pos], HEX); Serial.print(' ');
    pos++;    
  }
  Serial.println();

  uint16_t currentValue = data[0] | uint16_t(data[1])<<8;
  uint16_t voltageValue = data[2] | uint16_t(data[3])<<8;
  uint16_t position = data[4] | uint16_t(data[5])<<8;
  uint16_t tempValue = data[6] | uint16_t(data[7])<<8;
  uint16_t bemf = data[8] | uint16_t(data[9])<<8;
  
  Serial.print(F("current: 0x")); Serial.print(currentValue, HEX);
  float Vges = float(currentValue)/1023.0 * 5.0;
  float Vout = Vges * 4.99 / 5.99;
  float Iout = Vout / (0.01*0.05*4990);
  Serial.print(' '); Serial.print(Iout, 3); Serial.println('A');
  
  Serial.print(F("voltage: 0x")); Serial.print(voltageValue, HEX);
  float Vsense = float(voltageValue)/1023.0 * 5.0;
  float Vbatt = Vsense * 30.0/20.0;
  Serial.print(' '); Serial.print(Vbatt); Serial.println('V');
  
  Serial.print(F("position: ")); Serial.println(position);
  
  Serial.print(F("tempv: ")); Serial.print(tempValue);
  float tempVout = float(tempValue)/1023.0 * 5.0;
  float Ta = (tempVout - 0.4) / 0.0195; // Vo=400mV (0°C), Tc=19,5mV/°C
  Serial.print(' '); Serial.print(Ta); Serial.println("°C");

  Serial.print(F("bemf: ")); Serial.println(bemf);
  
  delay(1000);
}
