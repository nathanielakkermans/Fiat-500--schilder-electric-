 #ifdef DeviceType_GSM
  //Syncing the output state with the app at startup
  BLYNK_CONNECTED()
  {
    Blynk.syncVirtual(V3);  // will cause BLYNK_WRITE(V0) to be executed
  }

  BLYNK_WRITE(V6)   //charger set current
  {
    int value = param.asInt(); // Get value as integer
    Serial.print("Charger Set Current :");  Serial.println(value);
  }



  void sendSensor()
  {
    // displayInfo();

    Serial.printf("lat:%f lon:%f\n", flat, flon);
    Serial.print("sat :");  Serial.println(satellites);

    String signalS;
    int signalRSSI; 
    signalS = modem.getSignalQuality();
    signalRSSI = signalS.toInt();
    // Blynk.virtualWrite(V2, signalRSSI*3);
    Serial.print("Signal quality: ");
    Serial.println(signalRSSI);

    Blynk.virtualWrite(V0, BMS_SOC);      //SOC
    Blynk.virtualWrite(V1, BMS_Voltage/100);  //battery voltage
    Blynk.virtualWrite(V2, Miliamps/1000);  //battery current
    Blynk.virtualWrite(V3, DCcurrent);      //charge current
    Blynk.virtualWrite(V4, (Charging == 5));     //charging
    if (gps.location.isValid())
        {
          Blynk.virtualWrite(V5, flon, flat); //GPS lacation
          // myMap.location(move_index, latitude, longitude, "GPS_Location");
        }
    Blynk.virtualWrite(V7, satellites); //aantal satalieten


    Blynk.virtualWrite(V8, BMS_MinCellVoltage);
    Blynk.virtualWrite(V9, BMS_MaxCellVoltage); 
    Blynk.virtualWrite(V10, BMS_MinTemperature); 
    Blynk.virtualWrite(V11, BMS_MaxTemperature);
    Blynk.virtualWrite(V12, GPSSpeed);
  }

  void displayInfo()
  {
    Serial.print(F("Location: ")); 
    if (gps.location.isValid())
    {
      flat = gps.location.lat();
      flon = gps.location.lng();
      Serial.print(flat, 6);
      Serial.print(F(","));
      Serial.print(flon, 6);
    }
    else
    {
      Serial.print(F("INVALID"));
    }

    Serial.print(F("  Date/Time: "));
    if (gps.date.isValid())
    {
      Serial.print(gps.date.month());
      Serial.print(F("/"));
      Serial.print(gps.date.day());
      Serial.print(F("/"));
      Serial.print(gps.date.year());
    }
    else
    {
      Serial.print(F("INVALID"));
    }

    Serial.print(F(" "));
    if (gps.time.isValid())
    {
      if (gps.time.hour() < 10) Serial.print(F("0"));
      Serial.print(gps.time.hour());
      Serial.print(F(":"));
      if (gps.time.minute() < 10) Serial.print(F("0"));
      Serial.print(gps.time.minute());
      Serial.print(F(":"));
      if (gps.time.second() < 10) Serial.print(F("0"));
      Serial.print(gps.time.second());
      Serial.print(F("."));
      if (gps.time.centisecond() < 10) Serial.print(F("0"));
      Serial.print(gps.time.centisecond());
    }
    else
    {
      Serial.print(F("INVALID"));
    }

    Serial.println();
  }
  
  void GSMSetup()
  {
    Serial.println("Device type GSM");
    SerialAT.begin(115200 , SERIAL_8N1, PIN_RX, PIN_TX);
    // SerialGPS.begin(115200 , SERIAL_8N1, GPS_RX_PIN, 99);
    // CAN0.setCANPins(GPIO_NUM_19, GPIO_NUM_18);
    // CAN0.begin(500000);  
    LEDPettern = LED_OK;
    delay(100);

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

    // POWER_PIN : This pin controls the power supply of the Modem
    pinMode(POWER_PIN, OUTPUT);
    digitalWrite(POWER_PIN, HIGH);
    // PWR_PIN ： This Pin is the PWR-KEY of the Modem
    // The time of active low level impulse of PWRKEY pin to power on module , type 500 ms
    pinMode(PWR_PIN, OUTPUT);
    digitalWrite(PWR_PIN, HIGH);
    delay(500);    
    digitalWrite(PWR_PIN, LOW);

    Serial.println("Initializing modem...");
    if (!modem.init()) {
      Serial.println("Failed to restart modem, attempting to continue without restarting");
    }
    /*
      2 Automatic
      13 GSM only
      38 LTE only
      51 GSM and LTE only
    * * * */
    // modem.setNetworkMode(13);
      // delay(500);
    String name = modem.getModemName();
    // delay(500);
    Serial.println("Modem Name: " + name);
    String modemInfo = modem.getModemInfo();
      DBG("Modem Info:", modemInfo);

    bool res = modem.isGprsConnected();
      DBG("GPRS status:", res ? "connected" : "not connected");

      String ccid = modem.getSimCCID();
      DBG("CCID:", ccid);

      String imei = modem.getIMEI();
      DBG("IMEI:", imei);

      String cop = modem.getOperator();
      DBG("Operator:", cop);

      IPAddress local = modem.localIP();
      DBG("Local IP:", local);

      int csq = modem.getSignalQuality();
      DBG("Signal quality:", csq);


    Blynk.begin(auth, modem, apn, user, pass);
    // Blynk.begin(auth, ssid, pass);
    // Setup a function to be called every second
    timer.setInterval(1000L, sendSensor);
  }

  void GSMLoop()
  {
      if(timer_GSMTimeout.check())
      {
        if (!modem.isGprsConnected()) 
        {
          Serial.println("Reconnect");
          Blynk.begin(auth, modem, apn, user, pass);
        }
      }

      // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
      // if ((WiFi.status() != WL_CONNECTED)) {
      //   if(timer_GSMTimeout.check())
      //   {  
      //     Serial.println("Reconnecting to WiFi...");
      //     WiFi.disconnect();
      //     WiFi.reconnect();
      //     Blynk.begin(auth, ssid, pass);
      //   }
      // }
      

      // sendSensor();
      Blynk.run();

      // Serial.println("Going to sleep now");
      // // delay(1000);
      // Serial.flush(); 
      // // esp_deep_sleep_start();
      // esp_light_sleep_start();
      // Serial.println("wakeup");
      // Blynk.begin(auth, modem, apn, user, pass);
      timer.run();


    // This sketch displays information every time a new sentence is correctly encoded.
      // while (SerialGPS.available() > 0)
      //   if (gps.encode(SerialGPS.read()))
      //       if (gps.location.isValid())
      //       {
      //         flat = gps.location.lat();
      //         flon = gps.location.lng();
      //         satellites = gps.satellites.value();
      //         GPSSpeed = gps.speed.kmph();
      //       }
            // displayInfo();

      // if (millis() > 5000 && gps.charsProcessed() < 10)
      // {
      //   Serial.println(F("No GPS detected: check wiring."));
      //   while(true);
      // }
  }

#endif