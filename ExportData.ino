void output_data() {
//  String data = String(millis());
//  Serial.println(data);
//  data = String(data + ", "+reading_temperature);     
//  Serial.println(data);
//  data = String(data + ", "+reading_pressure);        
//  Serial.println(data);
//  data = String(data + ", "+reading_height);          
//  Serial.println(data);
//  data = String(data + ", "+reading_height_filtered); 
//  Serial.println(data);
//  data = String(data + ", "+reading_acc_x);           
//  Serial.println(data);
//  data = String(data + ", "+reading_acc_y);           
//  Serial.println(data);
//  data = String(data + ", "+reading_acc_z);           
//  Serial.println(data);
//  data = String(data + ", "+reading_acc);             
//  Serial.println(data);
//  data = String(data + ", "+reading_acc_filtered);
//  Serial.println(data);
//  data = String(data + "\n");
  
//  if(SERIAL_OUT) Serial.print(data); //print data in serial
  if(SD_DIRECT) writeToSD(); //data);    //write data to SD using one SD access per cycle
//  if(SD_BUFFER) {                   //store data in memory until it gets too large, then write to SD
//    buffer.concat(data);
//    Serial.println(buffer);
//    if(buffer.length()>10) write_buffer(); //if buffer full, empty it and try again
//    //Serial.println(String("wrote "+String(data.length())+" to buffer"));
//  } 
}
//
//void write_buffer() {
//  if(buffer.length()>0) { //if buffer isn't empty write buffer to card and empty it
//    String b2 = String(buffer);
//    writeToSD(b2);
//    Serial.println(String("wrote "+String(b2.length())+" to card"));
//    //Serial.println(b2);
//    buffer = String("");  
//  }
//}

void initialize_output() {
  if(SD_DIRECT) {
    initialize_SD();
//  writeToSD("#t,T,p,h,hf,ax,ay,az,a,af \n");
  }
//  if(SD_BUFFER) {
//    initialize_SD();
//    writeToSD("#t,T,p,h,hf,ax,ay,az,a,af \n");
//    buffer = String("");  
//  }
}
