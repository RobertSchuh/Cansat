void output_data() {
  String data = String(millis());
  
    data = String(data + ", "+reading_temperature);     
    data = String(data + ", "+reading_pressure);        
    data = String(data + ", "+reading_height);          
    data = String(data + ", "+reading_height_filtered); 
    data = String(data + ", "+reading_acc_x);           
    data = String(data + ", "+reading_acc_y);           
    data = String(data + ", "+reading_acc_z);           
    data = String(data + ", "+reading_acc);             
    data = String(data + ", "+reading_acc_filtered);

  if(SERIAL_OUT) Serial.println(data);
  if(SD_DIRECT) writeToSD(data);
}

void initialize_output() {
  if(SD_DIRECT) initialize_SD();
  if(SD_BUFFER) {
    initialize_SD();
    //Add buffer logic  
  }
}
