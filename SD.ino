void writeToSD(String data) {
  file = SD.open(FILE_NAME, FILE_WRITE);

  if (file) {
    file.println(data);

    file.close();
  }
}

void initialize_SD() {
  if (!SD.begin()) {
    Serial.println("SD module missing");
    set_state(FAIL);
    
  }
  SD.remove(FILE_NAME);
}
