#ifdef DeviceType_Logger
  void DebugLogger()
  {
    if (timer_Debug.check())
    {

      
      
     

      

    }
  }

void LoggerSave()
  {
    //lage snelheid logging
    if (timer_LoggerLowSpeed.check())
    {
      getReadings();
      StartMillis = millis();
      logSDCard(FileNameLow);
      StopMillis = millis();
      Serial.print("log low tijd ms: ");
      Serial.println(StopMillis - StartMillis);
    }
    //hoge snelheid loggibng
    if (timer_LoggerHighSpeed.check())
    {
      getReadings();
      StartMillis = millis();
      logSDCard(FileNameHigh);
      StopMillis = millis();
      Serial.print("log high tijd ms: ");
      Serial.println(StopMillis - StartMillis);
    }
  }

  // Function to get temperature
  void getReadings(){
    temperature1 += random(10); if (temperature1 > 1000){temperature1=0;}
    temperature2 += random(10); if (temperature2 > 1000){temperature2=0;}
    temperature3 += random(10); if (temperature3 > 1000){temperature3=0;}
    temperature4 += random(10); if (temperature4 > 1000){temperature4=0;}
    temperature5 += random(10); if (temperature5 > 1000){temperature5=0;}
    temperature6 += random(10); if (temperature6 > 1000){temperature6=0;}
    temperature7 += random(10); if (temperature7 > 1000){temperature7=0;}
    temperature8 += random(10); if (temperature8 > 1000){temperature8=0;}
    temperature9 += random(10); if (temperature8 > 1000){temperature9=0;}
    temperature10 += random(10); if (temperature10 > 1000){temperature10=0;}
    Serial.print("Temperature: ");
    Serial.println(temperature1);

    
  }
  String SetLogNames(){
    String Message;
    for (int i = 0; i <= NumberLowLOG - 1; i++) 
      {
        Message = Message + LOG_LOW[i].Name;
        if (i <  NumberLowLOG - 1)
          {
            Message = Message + ", ";
          }
        else
          {
            Message = Message + "\r\n";
          }
      }
      return Message;
  }
  



  // Write the sensor readings on the SD card
  void logSDCard(const char * path) {
    dataMessage = String(StartMillis) +"," + 
                  String(temperature1) +"," + 
                  String(temperature2) +"," + 
                  String(temperature3) +"," + 
                  String(temperature4) +"," + 
                  String(temperature5) +"," + 
                  String(temperature6) +"," + 
                  String(temperature7) +"," + 
                  String(temperature8) +"," + 
                  String(temperature9) +"," + 
                  String(temperature10) + "\r\n";
    Serial.print("Save data: ");
    Serial.println(dataMessage);
    appendFile(SD, path, dataMessage.c_str());
  }

  // Write to the SD card (DON'T MODIFY THIS FUNCTION)
  void writeFile(fs::FS &fs, const char * path, const char * message) {
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file) {
      LEDPettern = LED_ERROR;
      Serial.println("Failed to open file for writing");
      return;
    }
    if(file.print(message)) {
      Serial.println("File written");
    } else {
      Serial.println("Write failed");
    }
    file.close();
  }

  // Append data to the SD card (DON'T MODIFY THIS FUNCTION)
  void appendFile(fs::FS &fs, const char * path, const char * message) {
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file) {
      LEDPettern = LED_ERROR;
      Serial.println("Failed to open file for appending");
      return;
    }
    if(file.print(message)) {
      LEDPettern = LED_LOGGING;
      Serial.println("Message appended");
    } else {
      LEDPettern = LED_ERROR;
      Serial.println("Append failed");
    }
    file.close();
  }


 
#endif