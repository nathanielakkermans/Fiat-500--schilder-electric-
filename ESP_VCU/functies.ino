 void LEDBlink() {
    switch (LEDPettern) {
      case 0:  
        intervalON = 0;
        intervalOFF = 0;
        break;
      case 1:  //ok
        intervalON = 100;
        intervalOFF = 1000;
        break;
      case 2:  //logging
        intervalON = 10;
        intervalOFF = 400;
        break;
      case 3:  //error
        intervalON = 1000;
        intervalOFF = 100;
        break;
      case 4:  
        intervalON = 1000;
        intervalOFF = 0;
        break;
      case 5:  
        intervalON = 100;
        intervalOFF = 5000;
        break;
    }
    unsigned long currentMillis = millis();
    if (((currentMillis - previousMillis >= intervalON) && ledState == HIGH) || ((currentMillis - previousMillis >= intervalOFF) && ledState == LOW)){
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState);
    }
  }

  /*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

// #ifdef DeviceType_Logger || DeviceType_VCU
  //bekijk of de wanneer het laatste bericht binnen was gekomen en of dit nog binnen de timeout valt
  void CANCheckAlive(CANTimer *Value)
  {
    unsigned long Timeout = Value->ReceivedMillis + Value->Timeout + 2;
    Value->Online = Timeout > millis();
  }

  //bereken wanneer het bericht komt en wanneer het vorige bericht kwam en de frequentie berekenen
  void CANMillisCalculator (CANTimer *Value)
  {
    Value->previousMillis = Value->ReceivedMillis;
    Value->ReceivedMillis = millis();
    Value->Interval = Value->ReceivedMillis - Value->previousMillis;
    Value->Frequentie = 1000 / (float)Value->Interval;
    return;
  }

  void TaskCounter(TaskTimer &Timer, bool Run)
  {
    if(Run)
    {
      Timer.StartMillis = micros();
    }
    else
    {
      Timer.StopMillis = micros();
      Timer.Duration = Timer.StopMillis - Timer.StartMillis;  
      if(Timer.MaxMillis < Timer.Duration){
        Timer.MaxMillis = Timer.Duration;
      }
      if(Timer.MinMillis > Timer.Duration){
        Timer.MinMillis = Timer.Duration;
      }
    }
  }
  
  void TaskPrint(TaskTimer &Timer, String name)
  {
    Serial.print(name);
    Serial.print(", Duration: ");
    Serial.print(Timer.Duration);
    Serial.print(", Max: ");
    Serial.print(Timer.MaxMillis);
    Serial.print(", Min: ");
    Serial.println(Timer.MinMillis);
  }


// #endif