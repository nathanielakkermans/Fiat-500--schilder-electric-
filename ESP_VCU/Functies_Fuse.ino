#ifdef DeviceType_Fuse
  void Outputs()
  {
    if (timer_Outputs.check())
    {
    switch (LED_Color)
        {
          case ROOD:  
            ledcWrite(OUT4_Channel, 0);   //blauw
            ledcWrite(OUT5_Channel, 0);   //groen
            ledcWrite(OUT6_Channel, 255);   //rood
            // LED_Color = GROEN;
            break;

          case GROEN:  
            ledcWrite(OUT4_Channel, 0);   //blauw
            ledcWrite(OUT5_Channel, 255);   //groen
            ledcWrite(OUT6_Channel, 0);   //rood
            // LED_Color = BLAUW;
            break;

          case BLAUW:  
            ledcWrite(OUT4_Channel, 255);   //blauw
            ledcWrite(OUT5_Channel, 0);   //groen
            ledcWrite(OUT6_Channel, 0);   //rood
            // LED_Color = GEEL;
            break;

          case GEEL:  
            ledcWrite(OUT4_Channel, 0);   //blauw
            ledcWrite(OUT5_Channel, 255);   //groen
            ledcWrite(OUT6_Channel, 255);   //rood
            // LED_Color = ORANJE;
            break;

          case ORANJE:  
            ledcWrite(OUT4_Channel, 0);   //blauw
            ledcWrite(OUT5_Channel, 50);   //groen
            ledcWrite(OUT6_Channel, 255);   //rood
            // LED_Color = PAARS;
            break;

          case PAARS:  
            ledcWrite(OUT4_Channel, 255);   //blauw
            ledcWrite(OUT5_Channel, 0);   //groen
            ledcWrite(OUT6_Channel, 255);   //rood
            // LED_Color = WIT;
            break;

          case WIT:  
            ledcWrite(OUT4_Channel, 255);   //blauw
            ledcWrite(OUT5_Channel, 255);   //groen
            ledcWrite(OUT6_Channel, 255);   //rood
            // LED_Color = OFF;
            break;

          case OFF:  
            ledcWrite(OUT4_Channel, 0);   //blauw
            ledcWrite(OUT5_Channel, 0);   //groen
            ledcWrite(OUT6_Channel, 0);   //rood
            // LED_Color = ROOD;
            break;
        }
    
      digitalWrite(OUT3, DeurContact && Inverter_Enable);

    }
  }

  void Debug()
    {
      if (timer_Debug.check())
      {
        // contact ingangen
        Serial.print("IN1_Status: ");
        Serial.println(IN1_Status);
        Serial.print("IN2_Status: ");
        Serial.println(IN2_Status);
        Serial.print("IN3_Status: ");
        Serial.println(IN3_Status);
        Serial.print("IN4_Status: ");
        Serial.println(IN4_Status);
        Serial.print("IN5_Status: ");
        Serial.println(IN5_Status);
        Serial.print("IN6_Status: ");
        Serial.println(IN6_Status);
        Serial.println();

        //analoog input
        // Serial.print("ADC 1: ");
        // Serial.println(ADC_Value1);
        // Serial.print("ADC 2: ");
        // Serial.println(ADC_Value2);
        Serial.print("ADC 3: ");
        Serial.println(ADC_Value3);
        // Serial.print("ADC 4: ");
        // Serial.println(ADC_Value4);
        // Serial.print("TPS: ");      
        // Serial.println(TPS);
        // Serial.print("TPS diff: ");      
        // Serial.println(TPS_Diff);
        
        // Serial.print("TorqueVal: ");      
        // Serial.println(TorqueVal);
        // Serial.print("FiltertVCU_Voltage: ");      
        // Serial.println(FiltertVCU_Voltage);
        
        // //vcu state
        // Serial.print("VCU_State: ");
        // Serial.println(VCU_State);
        // Serial.println();

        // Serial.println("********************");

        // //inverter state
        // Serial.print("Inverter_Enable: ");
        // Serial.println(Inverter_Enable);
        // Serial.println();

        // Serial.print("Inverter Temp 1: ");
        // Serial.println(inverterTemp1);
        // Serial.print("Inverter Temp 2: ");
        // Serial.println(inverterTemp2);
        // Serial.print("Avg Inverter Temp: ");
        // Serial.println(avgInverterTemp);
        // // Serial.print("  Torque Request: ");
        // // Serial.println(torqueRequest);
        // Serial.print("RPM: ");
        // Serial.println(motorRPM);
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
        // Serial.print("BMS_SOC: ");
        // Serial.println(BMS_SOC);
        // Serial.print("BMS_Voltage: ");
        // Serial.println(BMS_Voltage);
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
        Serial.print("BMS_Status: ");
        Serial.println(BMS_Status);
        // Serial.print("BMS_ConnectedModules: ");
        // Serial.println(BMS_ConnectedModules);
        // Serial.print("BMS_Power: ");
        // Serial.println(BMS_Power);

        // Serial.print("Current sensor Miliamps : ");
        // Serial.println(Miliamps);
        // Serial.print("Current sensor voltage 1 : ");
        // Serial.println(Voltage1);    
        // Serial.print("Current sensor voltage 2 : ");
        // Serial.println(Voltage2);
        // Serial.print("Current sensor voltage 3 : ");
        // Serial.println(Voltage3);

        

        // Serial.println("********************");
        // //tesla charger
        // Serial.print("MaxDCvoltage: ");
        // Serial.println(MaxDCvoltage);
        // Serial.print("MaxDCcurrent: ");
        // Serial.println(MaxDCcurrent);
        // Serial.print("DCvoltage: ");
        // Serial.println(DCvoltage);
        // Serial.print("DCcurrent: ");
        // Serial.println(DCcurrent);
        // Serial.print("Charging: ");
        // Serial.println(Charging);
        // Serial.print("ChargerTemp: ");
        // Serial.println(ChargerTemp);
        

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
        // Serial.println();

      }
    }

void Inputs()
  {
    if (timer_Input.check())
    {
      IN1_Status = digitalRead(IN1);
      IN2_Status = digitalRead(IN2);
      IN3_Status = digitalRead(IN3);
      IN4_Status = digitalRead(IN4);  
      IN5_Status = digitalRead(IN5); 
      IN6_Status = digitalRead(IN6);   
    }
  }


void Fuse_Status()
  {
  if(timer_Fuse_Status.check())
    {
      byte buffer;
      buffer = IN1_Status;
      buffer |= (IN2_Status << 1);
      buffer |= (IN3_Status << 2);
      buffer |= (IN4_Status << 3);
      buffer |= (IN5_Status << 4);
      buffer |= (IN6_Status << 5);
      tx_frame.rtr = 0;
      tx_frame.id = 0x790;
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
    }
  }
#endif