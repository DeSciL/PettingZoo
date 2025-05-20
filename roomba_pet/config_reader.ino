 void readSDSettings(){
   // reads the personality setting
   file_t confFile = sdOpen("config.txt");
   String check;
   if (confFile) {
     if (confFile.available()) { 
        check = check + char(confFile.read());
        personality= uint8_t(check.toInt());
        Serial.println(personality);
        }
     // close the file:
     confFile.close();
 }
}

