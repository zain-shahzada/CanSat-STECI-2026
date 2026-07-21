#include <Wire.h>

const int MPU_ADDR = 0x68;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin();

  // Wake up the MPU6050 (it starts in sleep mode)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to 0 to wake up
  Wire.endTransmission(true);

  Serial.println("MPU6050 initialized (raw mode, bypassing WHO_AM_I check)");
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting register for accel readings
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true); // read 14 registers

  int16_t accelX = Wire.read() << 8 | Wire.read();
  int16_t accelY = Wire.read() << 8 | Wire.read();
  int16_t accelZ = Wire.read() << 8 | Wire.read();
  int16_t temp   = Wire.read() << 8 | Wire.read();
  int16_t gyroX  = Wire.read() << 8 | Wire.read();
  int16_t gyroY  = Wire.read() << 8 | Wire.read();
  int16_t gyroZ  = Wire.read() << 8 | Wire.read();

  Serial.print("Accel - X: "); Serial.print(accelX / 16384.0);
  Serial.print(" Y: "); Serial.print(accelY / 16384.0);
  Serial.print(" Z: "); Serial.println(accelZ / 16384.0);

  Serial.print("Gyro - X: "); Serial.print(gyroX / 131.0);
  Serial.print(" Y: "); Serial.print(gyroY / 131.0);
  Serial.print(" Z: "); Serial.println(gyroZ / 131.0);

  Serial.print("MPU Temp: "); Serial.print(temp / 340.0 + 36.53);
  Serial.println(" C");

  Serial.println();
  delay(500);
}