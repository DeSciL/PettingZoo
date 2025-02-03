 void readSDSettings(){
   // reads the personality setting
   FILE confFile = sdOpen("config.txt");
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

