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
  data = String(data + "\n");
  //Test
  if(SERIAL_OUT) Serial.print(data);
  if(SD_DIRECT) writeToSD(data);
}

void initialize_output() {
  if(SD_DIRECT) {
    initialize_SD();
    writeToSd("t,T,p,h,hf,ax,ay,az,a,af");
  }
  
  if(SD_BUFFER) {
    initialize_SD();
    //Add buffer logic  
  }
}
