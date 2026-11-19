#include <Wire.h>

const int MPU = 0x68;  //MPU6050 I2C address
float ax, ay, az;
uint8_t axh, axl, ayh, ayl, azh, azl;
int16_t axRaw, ayRaw, azRaw;

unsigned long lastSample;
float magnitude;

uint32_t data_count = 0;
float hz;

int byte6B, byte1C, byte75;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // Talk to register at 6B (Power Management)
  Wire.write(0x00);  // Turns sleep mode off
  Wire.endTransmission(true);

  // Configure Accelerometer Sensitivity - Full Scale Range
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);  // Talk to Accelerometer Config
  Wire.write(0x10);  // Set register bits as 00010000
  Wire.endTransmission();


  // Printing to check setup bytes for registers

  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 1, true);

  byte6B = Wire.read();


  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 1, true);

  byte1C = Wire.read();


  Wire.beginTransmission(MPU);
  Wire.write(0x75);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 1, true);

  byte75 = Wire.read();

  Serial.print("107: ");
  Serial.print(byte6B);
  Serial.print(" 28: ");
  Serial.print(byte1C);
  Serial.print(" 117: ");
  Serial.println(byte75);

  delay(20);
}

void loop() {

  if (millis() - lastSample >= 10) {

    data_count += 1;

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

    //For a range of +-8g, we need to divide the raw values by 4096, per the datasheet
    ax = axRaw / 4096.0;  // X-axis value
    ay = ayRaw / 4096.0;  // Y-axis value
    az = azRaw / 4096.0;  // Z-axis value

    magnitude = sqrt(ax * ax + ay * ay + az * az);


    /*Serial.print("X: ");
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

    /*    hz = data_count/(millis()/1000.0);

    Serial.print(hz, 4);
    Serial.println(" Hz");*/
  }
}
