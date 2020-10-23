void initialize_MPU6050() {
  // Test if the sensor is connected
  Wire.beginTransmission(0x68);
  if(Wire.endTransmission()) {
    Serial.println("MPU6050 sensor missing");
    set_state(FAIL);
  }
  
  // Activate the MPU6050 sensor
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); // PWR_MGMT_1
  Wire.write(0x00); 
  Wire.endTransmission();

  // Configure accelerometer sensitivity range
  Wire.beginTransmission(0x68);
  Wire.write(0x1C); // ACCEL_CONFIG
  Wire.write(0x00); // 0x00 for +-2g ... 0x08 for +-4g ... 0x10 for +-8g ... 0x18 for +-16g
  Wire.endTransmission();

  // Sensor calibration
  float ra = 0;

  for (int i = 0; i < N_CALIB_ACC; i++) {
    read_MPU6050();
    ra += reading_acc;
  }
  
  ACC_SCALE_FACTOR = N_CALIB_ACC*G_STUTTGART/ra;
}

void read_MPU6050() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // ACCEL_XOUT_H
  Wire.endTransmission();
  
  Wire.requestFrom(0x68, 6);
  
  while (Wire.available() < 6);

  reading_acc_x = (Wire.read() << 8 | Wire.read())*ACC_SCALE_FACTOR; // Divide by: 16384g (+-2g) 8192g (+-4g) 4096g (+-8g) 2048g (+-16g)
  reading_acc_y = (Wire.read() << 8 | Wire.read())*ACC_SCALE_FACTOR;
  reading_acc_z = (Wire.read() << 8 | Wire.read())*ACC_SCALE_FACTOR;

  reading_acc = sqrt(reading_acc_x*reading_acc_x + reading_acc_y*reading_acc_y + reading_acc_z*reading_acc_z);
}
