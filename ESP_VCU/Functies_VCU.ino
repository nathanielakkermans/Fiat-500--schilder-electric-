
#ifdef DeviceType_VCU  

  ////100ms messages here
  void Msgs100ms()                      
    {
      
    if(timer_Frames100.check())
    {
      // digitalWrite(StatusLED, !digitalRead(StatusLED)); //toggle led everytime we fire the 100ms messages.
      tx_frame.rtr = 0;
      tx_frame.id = 0x371;
      tx_frame.extended = false;
      tx_frame.length = 8;
      tx_frame.data.uint8[0] = 0x30;
      tx_frame.data.uint8[1] = 0x00; //seems to be a fixed msg.
      tx_frame.data.uint8[2] = 0x00;
      tx_frame.data.uint8[3] = 0x00;
      tx_frame.data.uint8[4] = 0x00;
      tx_frame.data.uint8[5] = 0x00;
      tx_frame.data.uint8[6] = 0x00;
      tx_frame.data.uint8[7] = 0x00;
      CAN0.sendFrame(tx_frame);
      
      // tx_frame.rtr = 0;
      // tx_frame.id = 0x286;
      // tx_frame.extended = false;
      // tx_frame.length = 8;
      // tx_frame.data.uint8[0] = 0x00;
      // tx_frame.data.uint8[1] = 0x00; //seems to only change a small amount. picking a common value for testing...
      // tx_frame.data.uint8[2] = 0x00;
      // tx_frame.data.uint8[3] = 0x3d;
      // tx_frame.data.uint8[4] = 0x00;
      // tx_frame.data.uint8[5] = 0x00;
      // tx_frame.data.uint8[6] = 0x21;
      // tx_frame.data.uint8[7] = 0x00;
      // CAN0.sendFrame(tx_frame);
      
      // tx_frame.rtr = 0;
      // tx_frame.id = 0x285;
      // tx_frame.extended = false;
      // tx_frame.length = 8;
      // tx_frame.data.uint8[0] = 0x00;
      // tx_frame.data.uint8[1] = 0x00; //seems to only change a small amount. picking a common value for testing...
      // tx_frame.data.uint8[2] = 0x14;
      // tx_frame.data.uint8[3] = 0x39;
      // tx_frame.data.uint8[4] = 0x91;
      // tx_frame.data.uint8[5] = 0xfe;
      // tx_frame.data.uint8[6] = 0x0c;
      // tx_frame.data.uint8[7] = 0x10;
      // CAN0.sendFrame(tx_frame);
    
            
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Torque Command = 0x287 
    //0x2710=0mm
    //0x2710=10000 decimal
    //torque band = +/- 200nm
    //200/10000= 0.02nm/bit
    /////////////////////////////////////////////////////   
    
      // TorqueVal = 10000-TorqueReq;
      TorqueLo=lowByte(TorqueVal);
      TorqueHi=highByte(TorqueVal);
      tx_frame.rtr = 0;
      tx_frame.id = 0x287;
      tx_frame.extended = false;
      tx_frame.length = 8;
      tx_frame.data.uint8[0] = TorqueHi; //front motor torque part 1
      tx_frame.data.uint8[1] = TorqueLo; //front motor torque part 2
      tx_frame.data.uint8[2] = TorqueHi; //rear motor torque part 1 0x2710=10000=0NM
      tx_frame.data.uint8[3] = TorqueLo; //rear motor torque part 2
      tx_frame.data.uint8[4] = TorqueHi; //generator torque part 1
      tx_frame.data.uint8[5] = TorqueLo; //generator torque part 2
      tx_frame.data.uint8[6] = function; //0x00,0x02=no inverter response to torque
                                      //0x03=front motor responds (possibly rear also)
                                      //0x04=generator only responds to torque
                                      //0x05=generator and front motor respond to torque.
      tx_frame.data.uint8[7] = 0x00;
      CAN0.sendFrame(tx_frame);   


      //bericht voor openinverter inverter
      // Inverter_Enable
      
      // Bit 0: cruise
      // Bit 1: start
      // Bit 2: brake
      // Bit 3: forward
      // Bit 4: reverse
      // Bit 5: bms

      // byte buffer;
      // buffer = Cruise;
      // buffer |= (StartPuls << 1);
      // buffer |= ((Clutch < 50 && RemContact) << 2);
      // buffer |= ((InverterDirection && Inverter_Enable) << 3);
      // buffer |= ((!InverterDirection && Inverter_Enable) << 4);
      // buffer |= (false << 5);
      

      // int intTPS = TPS;
      // TorqueLo=lowByte(intTPS);
      // TorqueHi=highByte(intTPS);
      // tx_frame.rtr = 0;
      // tx_frame.id = 100;
      // tx_frame.extended = false;
      // tx_frame.length = 8;
      // tx_frame.data.uint8[0] = TorqueLo; 
      // tx_frame.data.uint8[1] = TorqueHi; 
      // tx_frame.data.uint8[2] = buffer; 
      // tx_frame.data.uint8[3] = 0x00; 
      // tx_frame.data.uint8[4] = 0x00;
      // tx_frame.data.uint8[5] = 0x00; 
      // tx_frame.data.uint8[6] = 0x00; 
      // tx_frame.data.uint8[7] = 0x00;
      // CAN0.sendFrame(tx_frame); 


    }
    
  }

  void checkforinput()
  { 
    //Checks for keyboard input from Native port 
    if (Serial.available()) 
      {
        int inByte = Serial.read();
        switch (inByte)
          {
            // case 'f':            
            // Serial.print("Torque set to: ");
            // TorqueReq=Serial.parseInt();
            // TorqueVal=TorqueVal+TorqueReq;//add for forward dir
            //   Serial.print(TorqueReq/10);
            //   Serial.println("NM Forward");
            //   Serial.print(TorqueVal);
            //   Serial.println(" TorqueVal");
            //   break;

            // case 'r':            
            // Serial.print("Torque set to: ");
            // TorqueReq=Serial.parseInt();
            // TorqueVal=TorqueVal-TorqueReq;//subtract for reverse dir
            //   Serial.print(TorqueReq/10);
            //   Serial.println("NM Reverse");
            //   Serial.print(TorqueVal);
            //   Serial.println(" TorqueVal");
            //   break;

            // case 's':            
            // Serial.println("Zero Torque Commanded");
            // TorqueVal=10000;//0nm
            // Serial.print(TorqueVal);
            // Serial.println(" TorqueVal");
              // break;

            // case 't':            
            // Serial.print("Function Commanded:");
            // function=Serial.parseInt();
            // if(function==0x00) Serial.println("Stop");
            // if(function==0x03) Serial.println("Motors Only");
            // if(function==0x04) Serial.println("Generator Only"); 
            // if(function==0x05) Serial.println("Generator and Motors");    
            //   break;

           


            
            case 's':            
            Serial.print("clearToStart");
            clearToStart = !clearToStart;
            break;

            case 'R':            
            Serial.print("reset max cycle tijd");
            CycleMax = 0;
            break;

          }
      }
  }

  void CheckCAN()
  {

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  //read incomming data from inverter//////////////////
  //////////////////////////////////////////////////////
    
  }

  void Outputs()
  {
    if (timer_Outputs.check())
    {
      
    }
  }

  void ADC_Read()
  {
    #ifdef DeviceType_VCU
      if (timer_ADC.check())
      {
        ADC_Value1 = analogRead(ADC1_IN);
        ADC_Value2 = analogRead(ADC2_IN);
        ADC_Value3 = analogRead(ADC3_IN);
        ADC_Value4 = analogRead(ADC4_IN);
        ADC_ValueVCU_Voltage = float(analogRead(ADC1_VPower)) / 112,8374656;
        FiltertVCU_Voltage = (FiltertVCU_Voltage * 0.9) + (ADC_ValueVCU_Voltage * 0.1);

        //PP meting
        PP_Voltage = float(ADC_Value3) * 1.7;
        ChargePlugDetected = PP_Voltage < 2500;

        if(!ChargePlugDetected)
        {
          ChargePlugWasDisconnected = true;
          ChargeFinished = false;
        }

        PP_Res = PP_Voltage / PP_Ref;

  //  PP_PullUp;

    
        //achteruit
        // if (motorRPM == 0 && StartPuls && (ReverseMillis + 1000) < millis())
        // {
        //   ReverseMillis = millis();
        //   Reverse = !Reverse;
        // }

  


        //als de motor nog draait dan regen inschakelen
        int TorqueMIN;      
        // if(motorRPM > 100)
        // {
        //   TorqueMIN = TorqueCommandRegen;
        // }
        // else
        // {
          TorqueMIN = TorqueCommandMin;         
        // }
        if(ADC_Value1 < ADC1_Max + 500){
          TPS1 = map(ADC_Value1,ADC1_Min,ADC1_Max,TorqueMIN,TorqueCommandMax);
        }else
        {
          TPS1 = 0;
        }
        if(ADC_Value2 < ADC2_Max + 500){
          TPS2 = map(ADC_Value2,ADC2_Min,ADC2_Max,TorqueMIN,TorqueCommandMax);
        }else{
          TPS2 = 0;
        }
        TPS_Diff = TPS1 - TPS2;
        Clutch = map(ADC_Value4,ADC4_Min,ADC4_Max,0,100);
        if (Clutch < 0)Clutch = 0;
        if (Clutch > 100)Clutch = 100;


        //koppeling
        TPS = (((TPS1 + TPS2) / 2) * ((100-Clutch) /100)) + (TorqueCommandRegen * (Clutch / 100));   

        if (TPS < TorqueMIN)
          {
            TPS = TorqueMIN;
          }
        if (TPS > TorqueCommandMax)
          {
            TPS = TorqueCommandMax;
          }
        // if (TPS_Diff > 80 || TPS_Diff < -80)
        //     {
        //       TPS = TorqueCommandRegen;
        //     }
        if(Reverse){
          TorqueVal = 10000 + (TPS * -1);
        }
        else{
          TorqueVal = 10000 + TPS;
        }
        

        if (TPS_Diff < TPS_DiffMin)
        {
          TPS_DiffMin = TPS_Diff;
        }
        if (TPS_Diff > TPS_DiffMax)
        {
          TPS_DiffMax = TPS_Diff;
        }
        if(StartPuls)
        {
          TPS_DiffMin = 0;
          TPS_DiffMax = 0;
        }
          
      }
    #endif
  }

  void Inputs()
  {
    #ifdef DeviceType_VCU
      if (timer_Input.check())
      {
        ContactAan = digitalRead(IN1);
        ForwardRequest = digitalRead(IN2);
        ReverseRequest = digitalRead(IN3);
        RemContact = digitalRead(IN4); 
        DeurContact =  0;   
      }
    #endif
  }

  void Debug()
  {
    if (timer_Debug.check())
    {
      //contact ingangen
      Serial.print("ContactAan 1: ");
      Serial.println(ContactAan);
      Serial.print("ForwardRequest: ");
      Serial.println(ForwardRequest);
      Serial.print("ReverseRequest: ");
      Serial.println(ReverseRequest);
      Serial.print("RemContact 4: ");
      Serial.println(RemContact);
      Serial.println();


      // //analoog input
      // Serial.print("ADC 1: ");
      // Serial.println(ADC_Value1);
      // Serial.print("ADC 2: ");
      // Serial.println(ADC_Value2);
      // Serial.print("ADC 3: ");
      // Serial.println(ADC_Value3);
      // Serial.print("ADC 4: ");
      // Serial.println(ADC_Value4);
      // Serial.print("TPS1: ");      
      // Serial.println(TPS1);
      // Serial.print("TPS2: ");      
      // Serial.println(TPS2);
      Serial.print("TPS: ");      
      Serial.println(TPS);
      // Serial.print("TPS diff: ");      
      // Serial.println(TPS_Diff);
      // Serial.print("TPS diff min: ");      
      // Serial.println(TPS_DiffMin);
      // Serial.print("TPS diff max ");      
      // Serial.println(TPS_DiffMax);

      Serial.print("PP_Voltage: ");
      Serial.println(PP_Voltage);
      Serial.print("PP_Res: ");
      Serial.println(PP_Res);

      
      // Serial.print("TorqueVal: ");      
      // Serial.println(TorqueVal);

      // Serial.print("Clutch: ");      
      // Serial.println(Clutch);

      // Serial.print("FiltertVCU_Voltage: ");      
      // Serial.println(FiltertVCU_Voltage);
      
      // //vcu state
      Serial.print("VCU_State: ");
      Serial.println(VCU_State);
      Serial.print("VCU_StartState: ");
      Serial.println(VCU_StartState);
      
      Serial.println();

      // Serial.println("********************");

      // //inverter state
      Serial.print("Inverter_Enable: ");
      Serial.println(Inverter_Enable);
      Serial.print("function: ");
      Serial.println(function);
      Serial.println();

      // Serial.print("Inverter Temp 1: ");
      // Serial.println(inverterTemp1);
      // Serial.print("Inverter Temp 2: ");
      // Serial.println(inverterTemp2);
      // Serial.print("Avg Inverter Temp: ");
      // Serial.println(avgInverterTemp);
      Serial.print("TorqueVal: ");
      Serial.println(TorqueVal);
      // Serial.print("Reverse: ");
      // Serial.println(Reverse); 
      Serial.print("RPM: ");
      Serial.println(motorRPM);
      // Serial.print("motorPower: ");
      // Serial.println(motorPower);
      // Serial.print("Mtr Temp 1: ");
      // Serial.println(motorTemp1);
      // Serial.print("Mtr Temp 2: ");
      // Serial.println(motorTemp2);
      // Serial.print("Avg motor Temp: ");
      // Serial.println(avgMotorTemp);
      // Serial.print("Motor HV: ");
      // Serial.println(motorHVbatteryVolts);
      // Serial.print("motor Torque: ");
      // Serial.println(motorTorque);
      // Serial.print("Motor Amps1: ");
      // Serial.println(motorCurrent1);
      // Serial.print("Motor amps2: ");
      // Serial.println(motorCurrent2);
      // Serial.println();

      // Serial.println("********************");

      // //BMS info
      Serial.print("BMS_SOC: ");
      Serial.println(BMS_SOC);
      Serial.print("BMS_Voltage: ");
      Serial.println(BMS_Voltage);
      // Serial.print("BMS_Current: ");
      // Serial.println(BMS_Current);
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
      Serial.print("BMSOnline: ");
      Serial.println(BMSOnline);
      // Serial.print("CurrentSensorOnline: ");
      // Serial.println(CurrentSensorOnline);

      // Serial.print("CANTimer_351.Online: ");
      // Serial.println(CANTimer_351.Online);
      // Serial.print("CANTimer_355.Online: ");
      // Serial.println(CANTimer_355.Online);
      // Serial.print("CANTimer_356.Online: ");
      // Serial.println(CANTimer_356.Online);
      // Serial.print("CANTimer_373.Online: ");
      // Serial.println(CANTimer_373.Online);
      // Serial.print("CANTimer_372.Online: ");
      // Serial.println(CANTimer_372.Online);
      // Serial.print("CANTimer_35A.Online: ");
      // Serial.println(CANTimer_35A.Online);
      // Serial.print("CANTimer_321.Online: ");
      // Serial.println(CANTimer_321.Online);
      // Serial.print("CANTimer_322.Online: ");
      // Serial.println(CANTimer_322.Online);
      // Serial.print("CANTimer_323.Online: ");
      // Serial.println(CANTimer_323.Online);
      // Serial.print("CANTimer_324.Online: ");
      // Serial.println(CANTimer_324.Online);


      // Serial.print("CANTimer_321.Frequentie: ");
      // Serial.println(CANTimer_321.Frequentie);
      // Serial.print("CANTimer_321.Online: ");
      // Serial.println(CANTimer_321.Online);

      
      // Serial.print("Current sensor Miliamps : ");
      // Serial.println(Miliamps);
      // Serial.print("Current sensor voltage 1 : ");
      // Serial.println(Voltage1);    
      // Serial.print("Current sensor voltage 2 : ");
      // Serial.println(Voltage2);
      // Serial.print("Current sensor voltage 3 : ");
      // Serial.println(Voltage3);
      // Serial.print("SOC : ");
      // Serial.println(SOC);
      // Serial.print("BatteryResistanceValue : ");
      // Serial.println(BatteryResistanceValue,4);
      // Serial.print("Voltage1Corrected : ");
      // Serial.println(Voltage1Corrected);
      // Serial.print("SOCCorrected : ");
      // Serial.println(SOCCorrected);
      // Serial.print("SOCCorrectedFilt : ");
      // Serial.println(SOCCorrectedFilt);

      Serial.print("ChargePlugWasDisconnected : ");
      Serial.println(ChargePlugWasDisconnected);
      Serial.print("ChargeFinished : ");
      Serial.println(ChargeFinished);
   

          
      
      Serial.print("ACChargeState : ");
      Serial.println(ACChargeState);
      
      // Serial.println("********************");
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
  
      
      
      // Serial.print("Dash_licht_Button: ");
      // Serial.println(Dash_licht_Button);
      Serial.println();

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
      // TaskPrint(TimerAC_Charger, "TimerAC_Charger");
      // TaskPrint(TimerNextionUpdate, "TimerNextionUpdate");
      // TaskPrint(TimerNextionListen, "TimerNextionListen");
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
      myNex.writeNum("soc.val", SOC);
      myNex.writeNum("soc1.val", SOC);
      myNex.writeNum("current.val", Miliamps / 100);
      myNex.writeNum("templow.val", BMS_MinTemperature);
      myNex.writeNum("temphigh.val", BMS_MaxTemperature);
      myNex.writeNum("volt.val", Voltage1 / 100);
      myNex.writeNum("lowcell.val", BMS_MinCellVoltage);
      myNex.writeNum("highcell.val", BMS_MaxCellVoltage);
      myNex.writeNum("celldelta.val", BMS_MaxCellVoltage - BMS_MinCellVoltage);
      myNex.writeStr("stat.txt", BMS_StatusTXT);
      myNex.writeNum("motorpower.val", SOCCorrectedFilt*10);
      myNex.writeNum("bmspower.val", BMS_Power/100);
      myNex.writeNum("tps.val", TPS);
      myNex.writeNum("set_nm.val", TPS / 10);
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



void AC_Charger()
{
  if(timer_AC_Charger.check())
      {
        tx_frame.rtr = 0;
        tx_frame.id = 0x285;
        tx_frame.extended = false;
        tx_frame.length = 8;
        tx_frame.data.uint8[0] = 0x00;
        tx_frame.data.uint8[1] = 0x00; //seems to only change a small amount. picking a common value for testing...
        // tx_frame.data.uint8[2] = 0x14;
        tx_frame.data.uint8[3] = 0x39;
        tx_frame.data.uint8[4] = 0x91;
        tx_frame.data.uint8[5] = 0xfe;
        tx_frame.data.uint8[6] = 0x0c;
        tx_frame.data.uint8[7] = 0x10;
        if(clearToStart)
        {
          tx_frame.data.uint8[2] = 0xB6;//oxb6 in byte 3 enables charger
        }else
        {
          tx_frame.data.uint8[2] = 0x14;
        }
        CAN0.sendFrame(tx_frame);

        tx_frame.rtr = 0;
        tx_frame.id = 0x286;
        tx_frame.extended = false;
        tx_frame.length = 8;
        tx_frame.data.uint8[0] = setVolts >> 8;
        tx_frame.data.uint8[1] = setVolts & 0xff;//B1+B2   = voltage setpoint    (0E74=370.0V, 0,1V/bit)
        tx_frame.data.uint8[2] = currentRamp;//B3  = current setpoint DC-side  (78=12A -> 0,1A/bit)
        tx_frame.data.uint8[3] = 0x3d;
        tx_frame.data.uint8[4] = 0x00;
        tx_frame.data.uint8[5] = 0x00;
        tx_frame.data.uint8[6] = 0x21;
        tx_frame.data.uint8[7] = 0x00;
        CAN0.sendFrame(tx_frame);
        if(clearToStart)
        {
          if(currentRamp > 120) currentRamp = 120;//clamp to max of 12A
        }
        else
        {
          currentRamp=0;
        }
      }
}

void ACChargerLoop()
{
  if(timer_ACChargerLoop.check())
    {
      //als de bms een fout krijgt dan laden stoppen
      if (BMS_Status == BMS_Error){
          ChargeFinished = true;
          ACChargeState = 0;
          clearToStart = false;
        }

      switch (ACChargeState)
      {
        case 0:
        //als de plug gedetecteerd word mag het laden beginnen
        if (!ChargeFinished && ChargePlugDetected && ChargePlugWasDisconnected && VCU_State == 3 && BMS_Status == BMS_Ready && BMSOnline && CurrentSensorOnline)
        {
          ChargePlugWasDisconnected = false;
          ChargeFinished = false;
          clearToStart = true;
          ACChargeState = 1;
        }
        //als de stroom gaat oplopen beschouw laden gestart
        case 1:
          currentRamp = 100;
          if (chgStatus == 8 )//&& (Miliamps > MinChargeCurrent))
          {
            ACChargeState = 2;
          }
        break;
        //laden in gestart
        case 2:
          //als de accu de SOC of max cel spanning bereikt de stroom gaan afbouwen
          if ((BMS_MaxCellVoltage > MaxCellVoltageCharge) || (BMS_SOC > MacSOCCharge))
          {
            currentRamp--;
          }
          
          //als het laden klaar is
          if (currentRamp < MinChargeCurrent || StartPuls)
          {
            ACChargeState = 3;
          }
        break;

        case 3:
          ChargeFinished = true;
          ACChargeState = 0;
          clearToStart = false;
        break;
      }

  


       if (!ChargePlugDetected)
       {
          ACChargeState = 0;
          clearToStart = false;
       }

       if (VCU_State > 2 && VCU_State > 5)
       {
          ACChargeState = 0;
          clearToStart = false;
       }


       if (!BMSOnline)
       {
          ACChargeState = 0;
          clearToStart = false;
       }

       if (!CurrentSensorOnline)
       {
          ACChargeState = 0;
          clearToStart = false;
       }
    }
  
}

void BatteryResistanceCalc()
{
  if(timer_BatteryResistance.check())
  {
    MiliampsDelta = Miliamps - MiliampsLast;
    Voltage1Delta = Voltage1 - Voltage1Last;
    //bereken de accu weerstand op basis van delta u en i
    if(MiliampsDelta < MiliampsThreshold)
    {
      BatteryResistanceValue = float(Voltage1Delta) / float(MiliampsDelta);
    }

    MiliampsLast = Miliamps;
    Voltage1Last = Voltage1;
    //bereken de accu spanning zonder iR accus
    Voltage1Corrected = ((BatteryResistanceValue * (float(Miliamps*-1) / 1000))*1000) + float(Voltage1);
    SOCCorrected = map((float(Voltage1Corrected)/96),3400, 4150, 0, 100);
    if(SOCCorrectedFilt<=0)
    {
      SOCCorrectedFilt = SOCCorrected;
    }
    else
    {
      SOCCorrectedFilt = (SOCCorrectedFilt * 0.9) + (float(SOCCorrected) * 0.1);
    }
    
  }
}

void VCU_Status()
{
  if(timer_VCU_Status.check())
      {
        byte buffer;
        buffer = ContactAan;
        buffer |= (DeurContact << 1);
        buffer |= (Inverter_Enable << 2);
        buffer |= (StartPuls << 3);
        buffer |= (RemContact << 4);
        buffer |= (ChargePlugDetected << 5);
        buffer |= (clearToStart << 6);
        buffer |= (ChargePlugDetected << 7);
        
        // Serial.print("VCU_State: ");
        // Serial.println(buffer);
        tx_frame.rtr = 0;
        tx_frame.id = 0x780;
        tx_frame.extended = false;
        tx_frame.length = 8;
        tx_frame.data.uint8[0] = buffer;
        tx_frame.data.uint8[1] = 0; 
        tx_frame.data.uint8[2] = 0;
        tx_frame.data.uint8[3] = 0;
        tx_frame.data.uint8[4] = 0;
        tx_frame.data.uint8[5] = 0;   
        tx_frame.data.uint8[6] = 0;
        tx_frame.data.uint8[7] = 0;
        CAN0.sendFrame(tx_frame);

        tx_frame.rtr = 0;
        tx_frame.id = 0x781;
        tx_frame.extended = false;
        tx_frame.length = 8;
        tx_frame.data.uint8[0] = 1;          //BMS /DCDC      
        tx_frame.data.uint8[1] = Inverter_Enable;          //actief    
        tx_frame.data.uint8[2] = Waterpomp;         //waterpomp
        tx_frame.data.uint8[3] = 0;         //fentilator
        tx_frame.data.uint8[4] = Vacuumpomp;         //vacuum pomp 
        tx_frame.data.uint8[5] = 0;         //kachel klep 
        tx_frame.data.uint8[6] = 0x00;        
        tx_frame.data.uint8[7] = 0x00;          
        CAN0.sendFrame(tx_frame); 
      
      }
}

#endif