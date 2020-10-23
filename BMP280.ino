void initialize_BMP280() {
  if (!bmp280.initialize()) {
    Serial.println("BMP280 sensor missing");
    set_state(FAIL);
  }
  
  bmp280.setEnabled(0);
  bmp280.triggerMeasurement();

  // Sensor calibration
  float rh = 0;
  
  for (int i = 0; i < N_CALIB_HEIGHT; i++) {
    read_BMP280();
    rh += reading_height;
  }

  HEIGHT__OFFSET = rh/N_CALIB_HEIGHT;
}

void read_BMP280() {
  bmp280.awaitMeasurement();
  bmp280.getTemperature(reading_temperature);
  bmp280.getPressure(reading_pressure);
  bmp280.getAltitude(reading_height);
  bmp280.triggerMeasurement();

  reading_height -= HEIGHT__OFFSET;
}
