#include <Wire.h>

const int MPU = 0x68;  //MPU6050 I2C address
float ax, ay, az;
uint8_t axh, axl, ayh, ayl, azh, azl;
int16_t axRaw, ayRaw, azRaw;

unsigned long lastSample;
float magnitude;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // Talk to register at 6B (Power Management)
  Wire.write(0x00);  // Resets 6B
  Wire.endTransmission(true);

  // Configure Accelerometer Sensitivity - Full Scale Range
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);  // Talk to Accelerometer Config
  Wire.write(0x10);  // Set register bits as 00010000
  Wire.endTransmission();

  delay(20);
}

void loop() {

  

  if (millis() - lastSample >= 10) {

    lastSample = millis();

    // Read acceleromter data
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  // Start with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);  // Read 6 registers total, each axis value is stored in 2 registers

    axh = Wire.read();
    axl = Wire.read();
    ayh = Wire.read();
    ayl = Wire.read();
    azh = Wire.read();
    azl = Wire.read();

    axRaw = axh << 8 | axl;
    ayRaw = ayh << 8 | ayl;
    azRaw = azh << 8 | azl;

    //For a range of +-8g, we need to divide the raw values by 4096, according to the datasheet
    ax = axRaw / 4096.0;  // X-axis value
    ay = ayRaw / 4096.0;  // Y-axis value
    az = azRaw / 4096.0;  // Z-axis value

    magnitude = sqrt(ax*ax + ay*ay + az*az);

    /*
    Serial.print("X: ");
    Serial.print(ax, 4);
    Serial.print(" | ");
    Serial.print("Y: ");
    Serial.print(ay, 4);
    Serial.print(" | ");
    Serial.print("Z: ");
    Serial.print(az, 4);
    Serial.print(" | ");
    
    Serial.print("Magnitude: "); */
    Serial.println(magnitude, 4);
  }
}