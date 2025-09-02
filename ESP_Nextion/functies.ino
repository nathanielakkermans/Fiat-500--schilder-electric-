  void Debug()
  {
    if (timer_Debug.check())
    {
     
      
      // //vcu state
      Serial.print("VCU_State: ");
      Serial.println(VCU_State);
      Serial.println();

      // Serial.println("********************");

   

      Serial.print("Inverter Temp 1: ");
      Serial.println(inverterTemp1);
      Serial.print("Inverter Temp 2: ");
      Serial.println(inverterTemp2);
      Serial.print("Avg Inverter Temp: ");
      Serial.println(avgInverterTemp);
      // Serial.print("  Torque Request: ");
      // Serial.println(torqueRequest);
      Serial.print("RPM: ");
      Serial.println(motorRPM);
      Serial.print("motorPower: ");
      Serial.println(motorPower);
      Serial.print("Mtr Temp 1: ");
      Serial.println(motorTemp1);
      Serial.print("Mtr Temp 2: ");
      Serial.println(motorTemp2);
      Serial.print("Avg motor Temp: ");
      Serial.println(avgMotorTemp);
      Serial.print("Motor HV: ");
      Serial.println(motorHVbatteryVolts);
      Serial.print("motor Torque: ");
      Serial.println(motorTorque);
      Serial.print("Motor Amps1: ");
      Serial.println(motorCurrent1);
      Serial.print("Motor amps2: ");
      Serial.println(motorCurrent2);
      Serial.println();

      // Serial.println("********************");

      // //BMS info
      Serial.print("BMS_SOC: ");
      Serial.println(BMS_SOC);
      Serial.print("BMS_Voltage: ");
      Serial.println(BMS_Voltage / 1000);
      Serial.print("BMS_Current: ");
      Serial.println(BMS_Current / 1000);
      // Serial.print("BMS_Temperature: ");
      // Serial.println(BMS_Temperature);
      // Serial.print("BMS_MinCellVoltage: ");
      // Serial.println(BMS_MinCellVoltage);
      // Serial.print("BMS_MaxCellVoltage: ");
      // Serial.println(BMS_MaxCellVoltage);
      // Serial.print("BMS_MinTemperature: ");
      // Serial.println(BMS_MinTemperature);
      // Serial.print("BMS_MaxTemperature: ");
      // Serial.println(BMS_MaxTemperature);
      // Serial.print("BMS_Status: ");
      // Serial.println(BMS_Status);
      // Serial.print("BMS_ConnectedModules: ");
      // Serial.println(BMS_ConnectedModules);
      // Serial.print("BMS_Power: ");
      // Serial.println(BMS_Power);

      Serial.print("ContactAan: ");
      Serial.println(ContactAan);
      Serial.print("DeurContact: ");
      Serial.println(DeurContact);
      Serial.print("Inverter_Enable: ");
      Serial.println(Inverter_Enable);
      Serial.print("StartPuls: ");
      Serial.println(StartPuls);
      Serial.print("RemContact: ");
      Serial.println(RemContact);
      Serial.print("DriveBlockCharging: ");
      Serial.println(DriveBlockCharging);
    
      Serial.print("Speed: ");
      Serial.println(Speed);
    

      Serial.print("Current sensor 1 Miliamps : ");
      Serial.println(CurrentSensor1.Miliamps);
      Serial.print("Current sensor 1 voltage 1 : ");
      Serial.println(CurrentSensor1.Voltage1);    
      Serial.print("Current sensor 1 voltage 2 : ");
      Serial.println(CurrentSensor1.Voltage2);  
      Serial.print("Current sensor 2 Miliamps : ");
      Serial.println(CurrentSensor2.Miliamps);
      Serial.print("Current sensor 2 voltage 1 : ");
      Serial.println(CurrentSensor2.Voltage1);  
      Serial.print("BMS_SOC : ");
      Serial.println(BMS_SOC);
      Serial.print("SOCCorrected : ");
      Serial.println(SOCCorrected);
      Serial.print("SOCCorrected : ");
      Serial.println(SOCCorrected);
      Serial.print("BatteryResistanceValue : ");
      Serial.println(BatteryResistanceValue);
      
      
      Serial.print("LV_Volts: ");
      Serial.println(LV_Volts);
      Serial.print("LV_Amps: ");
      Serial.println(LV_Amps);
      Serial.print("ACVolts: ");
      Serial.println(ACVolts);
      Serial.print("ACAmps: ");
      Serial.println(ACAmps);
      Serial.print("DCAmps: ");
      Serial.println(DCAmps);
      Serial.print("chgStatus: ");
      Serial.println(chgStatus);
      Serial.print("evseDuty: ");
      Serial.println(evseDuty);
      Serial.print("currentRamp: ");
      Serial.println(currentRamp);
      Serial.print("dcBusV: ");
      Serial.println(dcBusV);
      Serial.print("temp_1: ");
      Serial.println(temp_1);
      Serial.print("temp_2: ");
      Serial.println(temp_2);
      Serial.print("temp_3: ");
      Serial.println(temp_3);
      Serial.print("temp_4: ");
      Serial.println(temp_4);
      Serial.print("temp_5: ");
      Serial.println(temp_5);
      Serial.print("clearToStart: ");
      Serial.println(clearToStart);
      Serial.print("ChargePlugDetected: ");
      Serial.println(ChargePlugDetected);

      

      // Serial.println("********************");
      // Serial.print("CANTimer_351.Frequentie: ");
      // Serial.println(CANTimer_351.Frequentie);
      // Serial.print("CANTimer_351.Online: ");
      // Serial.println(CANTimer_351.Online);
      // Serial.print("CycleMax: ");
      // Serial.println(CycleMax);
      // Serial.println("********************");
      // TaskPrint(TimerMsgs100ms, "TimerMsgs100ms");
      // TaskPrint(Timercheckforinput, "Timercheckforinput");
      // TaskPrint(TimerInputs, "TimerInputs");
      // TaskPrint(TimerADC_Read, "TimerADC_Read");
      // TaskPrint(TimerDebug, "TimerDebug");
      // TaskPrint(TimerTeslaCharger, "TimerTeslaCharger");
      // TaskPrint(TimerNextionUpdate, "TimerNextionUpdate");
      // TaskPrint(TimerNextionListen, "TimerNextionListen");mas
      Serial.println();

    


    }
  }
  void NextionUpdate()
  {
    if (timer_Nextion.check())
    {
      // Serial2.write(0x22);
      // Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      // Serial2.write(0xff);
      // Serial2.write(0xff);

      myNex.writeNum("soc.val", SOCCorrectedFilt);
      myNex.writeNum("current.val", BMS_Current / 100);
      myNex.writeNum("temp.val", BMS_Temperature);
      myNex.writeNum("templow.val", BMS_MinTemperature);
      myNex.writeNum("temphigh.val", BMS_MaxTemperature);
      myNex.writeNum("volt.val", BMS_Voltage / 100);
      myNex.writeNum("lowcell.val", BMS_MinCellVoltage);
      myNex.writeNum("highcell.val", BMS_MaxCellVoltage);
      myNex.writeNum("celldelta.val", BMS_MaxCellVoltage - BMS_MinCellVoltage);
      myNex.writeStr("stat.txt", BMS_StatusTXT);
      myNex.writeNum("motorpower.val", motorPower);
      myNex.writeNum("bmspower.val", ((CurrentSensor1.Miliamps / 1000) * (CurrentSensor1.Voltage2 / 1000))/100);

      // myNex.writeNum("tps.val", TPS);
      // myNex.writeNum("set_nm.val", TPS / 10);
      myNex.writeNum("get_nm.val", motorTorque);
      myNex.writeNum("rpm.val", motorRPM);
      myNex.writeNum("m1_current.val", motorCurrent1);
      myNex.writeNum("m2_current.val", motorCurrent2);
      myNex.writeNum("inv_hv.val", motorHVbatteryVolts/10);

      myNex.writeNum("temp_inv1.val", inverterTemp1);
      myNex.writeNum("temp_inv2.val", inverterTemp2);
      myNex.writeNum("temp_mot1.val", motorTemp1);
      myNex.writeNum("temp_mot2.val", motorTemp2);
      myNex.writeNum("vcu_voltage.val", FiltertVCU_Voltage);
      myNex.writeNum("speed.val", Speed);
      //charger DCDC
      myNex.writeNum("LV_Volts.val", LV_Volts * 10);
      myNex.writeNum("LV_Amps.val", LV_Amps * 10);
      myNex.writeNum("ACVolts.val", ACVolts * 10);
      myNex.writeNum("ACAmps.val", ACAmps * 10);
      myNex.writeNum("DCAmps.val", DCAmps * 10);
      myNex.writeNum("chgStatus.val", chgStatus);
      myNex.writeNum("evseDuty.val", evseDuty);
      myNex.writeNum("chgTemp.val", tempMax);
      // myNex.writeNum("clearToStart.val", clearToStart);
      myNex.writeNum("chgDetect.val", ChargePlugDetected);
     
      

      if (chgStatus == 8)
        {
          myNex.writeStr("char_status.txt", "Charging");
        }
        else
        {
          myNex.writeStr("char_status.txt", "Off");
        }

       


    }
  }

  void NextionGraphUpdate()
  {
    if (timer_NextionGraph.check())
    {
      String randomtest = "add 1,0,";
      randomtest += random(10, 50);
      myNex.writeStr(randomtest);

      randomtest = "add 1,1,";
      randomtest += random(60, 100);
      myNex.writeStr(randomtest);

      randomtest = "add 1,2,";
      randomtest += random(120, 200);
      myNex.writeStr(randomtest);

      randomtest = "add 1,3,";
      randomtest += random(200, 250);
      myNex.writeStr(randomtest);    
    }
  }

void easyNexReadCustomCommand(){

  switch(myNex.cmdGroup){
    
    case 'S': // Or <case 0x53:>  If 'S' matches 
      // read the next byte that determines the position on the table
      SetDCcurrent = myNex.readByte();
      Serial.print("SetDCcurrent HMI");
      Serial.println(SetDCcurrent);
      break;
  }
}
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