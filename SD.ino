
String filename = FILE_NAME; 
  
void initialize_SD() {
  if (!SD.begin()) {
    Serial.println("SD module missing");
    set_state(FAIL);  
  }
  //if "file.txt" exists, use "file(1).txt" instead of deleting the old one, we have gigabytes to spare
  for(int n=1;SD.exists(filename);n++) filename = String(String(FILE_NAME).substring(0,String(FILE_NAME).indexOf("."))+"("+n+")"+String(FILE_NAME).substring(String(FILE_NAME).indexOf("."))); //Dark magic don't touch
  Serial.print("Using file name: "); Serial.println(filename);
}

void writeToSD(String data) {
  file = SD.open(filename, FILE_WRITE);
  if (file) {
    file.print(data);
    file.close();
  }
  else Serial.println("SD failed");
}
