// NAME: OpenServo-TestClient

#include <Wire.h>
#include "registers.h"
#include "banks.h"
#include "commands.h"
#include "alert.h"

#define ALARM_PIN   12    // MISO

#define OPS_ADDRESS 0x10

void printRegisters() {
  uint8_t regs[REGISTER_COUNT];

  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(0); 
  byte error = Wire.endTransmission();
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    exit(-1);
  }

#define REGS1 32
  Wire.requestFrom(OPS_ADDRESS, REGS1);
  Serial.print(F("Reading ")); Serial.print(REGS1); Serial.print(F(" registers:"));
  int cnt = 0;
  while (cnt < REGS1) {
    while (!Wire.available()) Serial.print('.'); // wait
    regs[cnt] = Wire.read();
    Serial.print(' '); Serial.print(regs[cnt], HEX);
    cnt++; 
  }
  Serial.println();
  delay(5);

  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(REGS1); 
  error = Wire.endTransmission();
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    exit(-1);
  }

#define REGS2 16
  Wire.requestFrom(OPS_ADDRESS, REGS2);
  Serial.print(F("Reading ")); Serial.print(REGS2); Serial.print(F(" registers:"));
  cnt = 0;
  while (cnt < REGS2) {
    while (!Wire.available()) Serial.print('.'); // wait
    regs[REGS1+cnt] = Wire.read();
    Serial.print(' '); Serial.print(regs[REGS1+cnt], HEX);
    cnt++; 
  }
  Serial.println();
  delay(5);
  
  Serial.print(F("Device type=")); Serial.print(regs[REG_DEVICE_TYPE]);
  Serial.print(F(", subtype=")); Serial.println((char)regs[REG_DEVICE_SUBTYPE]);
  Serial.print(F("Software version: ")); Serial.print(regs[REG_VERSION_MAJOR]);
  Serial.print('.'); Serial.println(regs[REG_VERSION_MINOR]);

  Serial.print(F("Flags: 0x")); Serial.print(regs[REG_FLAGS_LO], HEX); 
  Serial.print(':'); Serial.print((regs[REG_FLAGS_LO] & (1<<FLAGS_LO_PWM_ENABLED) ? "PWM" : "/PWM"));
  Serial.print(':'); Serial.print((regs[REG_FLAGS_LO] & (1<<FLAGS_LO_WRITE_ENABLED) ? "WR" : "R/O"));
  Serial.print(':'); Serial.print((regs[REG_FLAGS_LO] & (1<<FLAGS_LO_MOTION_ENABLED) ? "MOTION" : "/MOTION")); 
  Serial.println();
  
  Serial.print(F("Position=")); Serial.print(int16_t(regs[REG_POSITION_HI])<<8 | regs[REG_POSITION_LO]);
  Serial.print(F(", Velocity=")); Serial.println(int16_t(regs[REG_VELOCITY_HI])<<8 | regs[REG_VELOCITY_LO]);

  Serial.print(F("Power: ")); 
  float power = getPower();
  Serial.print(power, 3); Serial.println('A');
  
  Serial.print(F("Voltage: ")); 
  float voltage = getBattVoltage();
  Serial.print(voltage); Serial.println('V');

  Serial.print(F("Temp: ")); 
  float temp = getTemp();
  Serial.print(temp); Serial.println("°C");

  Serial.print(F("PWM DirA=")); Serial.print(regs[REG_PWM_DIRA]);
  Serial.print(F(", DirB=")); Serial.println(regs[REG_PWM_DIRB]);

  Serial.print(F("Seek: position=")); Serial.print(int16_t(regs[REG_SEEK_POSITION_HI])<<8 | regs[REG_SEEK_POSITION_LO]);
  Serial.print(F(", velocity=")); Serial.println(int16_t(regs[REG_SEEK_VELOCITY_HI])<<8 | regs[REG_SEEK_VELOCITY_LO]);

  Serial.print(F("PID: Deadband=")); Serial.print(bankReadByte(POS_PID_BANK, REG_PID_DEADBAND));
  Serial.print(F(", Pgain=")); Serial.print(bankReadWord(POS_PID_BANK, REG_PID_PGAIN_HI));
  Serial.print(F(", Dgain=")); Serial.println(bankReadWord(POS_PID_BANK, REG_PID_DGAIN_HI));

  Serial.print(F("Seek Range: Min=")); Serial.print(bankReadWord(POS_PID_BANK, REG_MIN_SEEK_HI));
  Serial.print(F(", Max=")); Serial.println(bankReadWord(POS_PID_BANK, REG_MAX_SEEK_HI));
}

uint8_t getRegister(uint8_t addr) {
  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(addr);
  byte error = Wire.endTransmission();
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    return 0;
  }

  Wire.requestFrom(OPS_ADDRESS, 1);
  while (!Wire.available());  // wait
  uint8_t data = Wire.read();
  delay(5);
  return data;
}

bool setRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  byte error = Wire.endTransmission();
  delay(5);
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    return false;
  }
  return true;
}

uint16_t getRegisterWord(uint8_t addr) {
  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(addr);
  byte error = Wire.endTransmission();
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    return 0;
  }

  uint8_t regs[2];
  Wire.requestFrom(OPS_ADDRESS, sizeof(regs));
  while (Wire.available() < sizeof(regs));
  for (int i=0; i<sizeof(regs); i++) {
    regs[i] = Wire.read();
  }
  uint16_t value = uint16_t(regs[0])<<8 | regs[1];
  delay(5);
  return value;
}

bool setRegisterWord(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(reg);
  uint8_t data[2];
  data[0] = value >> 8;
  data[1] = value & 0xff;
  Wire.write(data, sizeof(data));
  byte error = Wire.endTransmission();
  delay(5);
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    return false;
  }
  return true;
}

uint8_t getBank() {
  return getRegister(REG_BANK_SELECT);
}
void selectBank(uint8_t bank) {
  static uint8_t currentBank = 0;
  if (currentBank != bank) {
    setRegister(REG_BANK_SELECT, bank);
  }
}
uint8_t bankReadByte(uint8_t bank, uint8_t addr) {
  selectBank(bank);
  return getRegister(MIN_BANK_REGISTER+addr);
}
uint16_t bankReadWord(uint8_t bank, uint8_t addr) {
  selectBank(bank);
  uint8_t hi = getRegister(MIN_BANK_REGISTER+addr);
  uint8_t lo = getRegister(MIN_BANK_REGISTER+addr+1);
  return uint16_t(hi)<<8 | lo;
}

void printAlertStatus() {
  uint8_t alertStatus = bankReadByte(ALERT_BANK, ALERT_STATUS);
  Serial.print(F("Status: %")); Serial.print(alertStatus, BIN);
  if (alertStatus & (1 << ALERT_OVERCURR)) Serial.print(F(" OverCurr"));
  if (alertStatus & (1 << ALERT_OVERVOLT)) Serial.print(F(" OverVolt"));
  if (alertStatus & (1 << ALERT_UNDERVOLT)) Serial.print(F(" UnderVolt"));
  if (alertStatus & (1 << ALERT_OVERTEMP)) Serial.print(F(" OverTemp"));
  if (alertStatus & (1 << ALERT_POSITION_REACHED)) Serial.print(F(" PositionReached"));
  Serial.println();  
}

void printAlertRegisters() {
  uint16_t maxVolt = bankReadWord(ALERT_CONFIG_BANK, ALERT_VOLT_MAX_LIMIT_HI);
  uint16_t minVolt = bankReadWord(ALERT_CONFIG_BANK, ALERT_VOLT_MIN_LIMIT_HI);
  uint16_t maxTemp = bankReadWord(ALERT_CONFIG_BANK, ALERT_TEMP_MAX_LIMIT_HI);
  uint16_t maxCurr = bankReadWord(ALERT_CONFIG_BANK, ALERT_CURR_MAX_LIMIT_HI);

  Serial.print(F("maxVolt: ")); Serial.print(maxVolt); 
  Serial.print(' '); Serial.print(maxVolt/1023.0*7.5, 1); Serial.println('V');
  Serial.print(F("minVolt: ")); Serial.print(minVolt);
  Serial.print(' '); Serial.print(minVolt/1023.0*7.5, 1); Serial.println('V');
  Serial.print(F("maxTemp: ")); Serial.print(maxTemp);
  Serial.print(' '); Serial.print((maxTemp/1023.0*5.0-0.4)/0.0195, 1); Serial.println("°C");
  Serial.print(F("maxCurr: ")); Serial.print(maxCurr);
  Serial.print(' '); Serial.print(maxCurr/1023.0*1.66945, 1); Serial.println('A');
}

bool writeCommand(uint8_t cmd) {
  Wire.beginTransmission(OPS_ADDRESS);
  Wire.write(cmd);
  byte error = Wire.endTransmission();
  delay(5);
  if (0 != error) {
    Serial.print(F("ERROR: OpenServo not found! error=")); Serial.println(error);
    Serial.flush();
    return false;
  }
  return true;
}

float getPower() {
  uint16_t value = getRegisterWord(REG_POWER_HI);
  Serial.print(value); Serial.print(' ');
  // Vges = value/1023 * 5V;
  float Vges = float(value)/1023.0 * 5.0;
  // Vout = Vges * R3/(R1+R3) 
  float Vout = Vges * 0.8331; // 0.8331 = 4.99/5.99
  // Vout = 0.01*Vsense*Rout (Datasheet: Application Information, pg.4)
  // Vsense = Rsense*Iload, Rsense=R2=0.05Ohm, Rout=R3=4.99K
  // => Vout = 0.01*R2*Iload*R3
  // => Iload = Vout / (0.01*R2*R3)
  float Iload = Vout / 2.495; //2.495=(0.01*0.05*4990);
  return Iload;
}

float getBattVoltage() {
  uint16_t value = getRegisterWord(REG_VOLTAGE_HI);
  Serial.print(value); Serial.print(' ');
  // Vsense = value/1023 * 5V;
  float Vsense = value/1023.0 * 5.0;
  // Vbatt = Vsense * (R4+R6)/R6, R4=10K, R6=20K
  float Vbatt = Vsense * 1.5; // (10K+20K)/20K=30K/20K=1.5
  return Vbatt;
}

float getTemp() {
  int16_t value = getRegisterWord(REG_TEMPERATURE_HI); // register in V3.1
  Serial.print(value); Serial.print(' ');
  // Vout = value/1023 * 5V;
  float Vout = value/1023.0 * 5.0;
  // Ta = (Vout - V0) / Tc, V0=400mV, Tc=19.5mv/°C
  float Ta = (Vout - 0.4) / 0.0195;
  return Ta;  
}

uint16_t getCurrPosition() {
  return getRegisterWord(REG_POSITION_HI);
}

uint16_t getSeekPosition() {
  return getRegisterWord(REG_SEEK_POSITION_HI);
}

uint16_t getCurrVelocity() {
  return getRegisterWord(REG_VELOCITY_HI);
}

uint16_t getSeekVelocity() {
  return getRegisterWord(REG_SEEK_VELOCITY_HI);
}

void setPosition(uint16_t position) {
  setRegisterWord(REG_SEEK_POSITION_HI, position);
}

void setVelocity(uint16_t velocity) {
  setRegisterWord(REG_SEEK_VELOCITY_HI, velocity);
}

void setPID_PGain(uint16_t pgain) {
  setRegisterWord(REG_PID_PGAIN_HI, pgain);
}

void setPID_DGain(uint16_t dgain) {
  setRegisterWord(REG_PID_DGAIN_HI, dgain);
}

void setDeadband(uint8_t deadband) {
  setRegister(REG_PID_DEADBAND, deadband);
}

void resetServo() {
  writeCommand(TWI_CMD_RESET);
  delay(50);
}

void enableWrite() {
  writeCommand(TWI_CMD_WRITE_ENABLE);
}

void setup() {
  pinMode(ALARM_PIN, INPUT);
  
  Wire.begin();
  Serial.begin(115200);
  Serial.println(F("---------------"));
  Serial.println(F("OpenServo-Testclient"));
  
  Serial.print(F("Checking OpenServo... "));
  Wire.beginTransmission(OPS_ADDRESS);
  byte error = Wire.endTransmission();
  if (0 != error) {
    Serial.print(F("not found! error=")); Serial.println(error);
    Serial.flush();
    exit(-1);
  }  
  Serial.print(F("found at address 0x"));
  Serial.println(bankReadByte(CONFIG_BANK, REG_TWI_ADDRESS), HEX);

  Serial.println(F("Reset...")); 
  resetServo();
  delay(50);
  
  printRegisters();
  printAlertRegisters();
  Serial.println(F("---------------"));

  Serial.println(F("Set position..."));
  setPosition(512);
  setVelocity(512);
  
  Serial.println(F("Running..."));
}

void loop() {
  if (digitalRead(ALARM_PIN)) {
    Serial.print(F("ALERT: ")); printAlertStatus();
  }
  
  printRegisters();
  Serial.println(F("---------------"));
  delay(1000);
}
