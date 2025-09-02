// #ifdef DeviceType_Logger || DeviceType_VCU
  //callback BMS Limits
  void canRX_351(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_351);
  }

  //callback BMS SOC
  void canRX_355(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_355);
    BMS_SOC = ((frame->data.byte[1] * 256) + frame->data.byte[0]);
  }

  //callback BMS Status
  void canRX_356(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_356);
    BMS_Voltage = (frame->data.byte[3] << 24) + (frame->data.byte[2] << 16) + (frame->data.byte[1] << 8) + (frame->data.byte[0] << 0);
    BMS_Current = (frame->data.byte[7] << 24) + (frame->data.byte[6] << 16) + (frame->data.byte[5] << 8) + (frame->data.byte[4] << 0);
    BMS_Power = (float(BMS_Voltage) / 1000) * (float(BMS_Current) / 1000);
  }

  //callback BMS Warnings
  void canRX_35A(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_35A);
  }

  //callback BMS Low and High
  void canRX_373(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_373);
    BMS_MinCellVoltage = ((frame->data.byte[1] * 256) + frame->data.byte[0]);
    BMS_MaxCellVoltage = ((frame->data.byte[3] * 256) + frame->data.byte[2]);
    BMS_MinTemperature = ((frame->data.byte[5] * 256) + frame->data.byte[4]) - 273;
    BMS_MaxTemperature = ((frame->data.byte[7] * 256) + frame->data.byte[6]) - 273;
  }

  //callback BMS Info hoi
  void canRX_372(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_372);
    BMS_ConnectedModules = ((frame->data.byte[1] * 256) + frame->data.byte[0]);
    BMS_Status = frame->data.byte[4];
    switch (BMS_Status)
    {
      case (BMS_Boot):
        BMS_StatusTXT = " Boot ";
        break;

      case (BMS_Ready):
        BMS_StatusTXT = " Ready ";
        break;

      case (BMS_Precharge):
        BMS_StatusTXT = " Precharge ";
        break;

      case (BMS_Drive):
        if (!Inverter_Enable){
          BMS_StatusTXT = " Ready ";
        }
        else
        {
          BMS_StatusTXT = " Drive ";
        }
        break;

      case (BMS_Charge):
        BMS_StatusTXT = " Charge ";
        break;

      case (BMS_Error):
        BMS_StatusTXT = " Error ";
        break;
    }
  }


  // Inverter Set status
  void canRX_278(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_278);
    if (frame->data.byte[6] > 0)
      {
        InverterInDrive = true;
      }
      else
      {
        InverterInDrive = false;
      } 
  }
  
  // Inverter RPM Battery and Torque
  void canRX_288(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_28B);
    motorTorque = ((((frame->data.byte[0] * 256) + frame->data.byte[1]) - 10000) / 10); // Motor Torque -200 / + 200nm
    motorRPM = (frame->data.byte[2] * 256 + frame->data.byte[3] - 20000);               // 289_RrRPM,Rear RPM,220289,C*256+D-20000,-10000,10000,RPM,
    motorHVbatteryVolts = (frame->data.byte[4] * 256 + frame->data.byte[5]);            // Inverter HV
    motorPower = float(motorTorque *  motorRPM / 9.5488);
  }

  // Inverter Temps
  void canRX_298(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_298);
    // inverter Temps
    inverterTemp1 = (frame->data.byte[1] - 40);
    inverterTemp2 = (frame->data.byte[4] - 40);

    avgInverterTemp = (inverterTemp1 + inverterTemp2) / 2;
  } 

  // Inverter current
  void canRX_75A(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_734);
    // inverter Current
    motorCurrent1 = (frame->data.byte[0] * 256 + frame->data.byte[1] - 1000);
    motorCurrent2 = (frame->data.byte[2] * 256 + frame->data.byte[3] - 1000);
  } 

  // motor Temps
  void canRX_75B(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_735);
    // inverter Temps
    motorTemp1 = (frame->data.byte[0] - 40);
    motorTemp2 = (frame->data.byte[2] - 40);
    avgMotorTemp = (motorTemp1 + motorTemp2) / 2;
  } 

  
  void canRX_521(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_521);  
    Miliamps = (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
    BMS_Power = ((float(Miliamps) / 1000) * float(Voltage1)) / 1000;
  } 
  
  void canRX_522(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_522);
    Voltage1 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
    BMS_Power = ((float(Miliamps) / 1000) * float(Voltage1)) / 1000;
    SOC = map((float(Voltage1)/96),3400, 4150, 0, 100);
  } 

  void canRX_523(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_523);
    Voltage2 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0); 
  } 

  void canRX_524(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_524);
    Voltage3 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
  } 

  // VCU status
  void canRX_780(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_780);
    byte buffer = frame->data.byte[0]; 
    // Serial.print("VCU_State: ");
    // Serial.println(buffer);
    // ContactAan = (buffer && 1);
    // DeurContact = ((buffer >> 1) & 1);
    // Inverter_Enable = ((buffer >> 2) & 1);
    // StartPuls = ((buffer >> 3) & 1);
    // RemContact = ((buffer >> 4) & 1);
    // ChargePlugDetected = ((buffer >> 5) & 1);
  }

  // Fuse status
  void canRX_790(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_790);
    byte buffer = frame->data.byte[0]; 
    // Serial.print("Fuse_State: ");
    // Serial.println(buffer);
    //  = (buffer && 1);
    //  = ((buffer >> 1) & 1);
    //  = ((buffer >> 2) & 1);
    //  = ((buffer >> 3) & 1);
    //  = ((buffer >> 4) & 1);
    Dash_licht_Button = ((buffer >> 5) & 1);
  }

  // Fuse status2
  void canRX_781(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_781);
    CAN781RX[0] = frame->data.byte[0];
    CAN781RX[1] = frame->data.byte[1];
    CAN781RX[2] = frame->data.byte[2];
    CAN781RX[3] = frame->data.byte[3];
    CAN781RX[4] = frame->data.byte[4];
    CAN781RX[5] = frame->data.byte[5];
    CAN781RX[6] = frame->data.byte[6];
    CAN781RX[7] = frame->data.byte[7];
    
  }



  //DC-DC converter status
  void canRX_377(CAN_FRAME *frame)
  {
    LV_Volts = ((frame->data.byte[0]<<8) | (frame->data.byte[1]))*0.01;
    LV_Amps = ((frame->data.byte[2]<<8) | (frame->data.byte[3]))*0.1;
    temp_1 = frame->data.byte[4]-45;//degC bias -45
    temp_2 = frame->data.byte[5]-45;//degC bias -45
    temp_3 = frame->data.byte[6]-45;//degC bias -45
    
  }

   //DC-DC converter status
  void canRX_389(CAN_FRAME *frame)
  {
    ACVolts = frame->data.byte[1]; //AC voltage measured at charger. Scale 1 to 1.
    ACAmps = frame->data.byte[6] * 0.1; //Current in Amps from mains. scale 0.1.
    DCAmps = frame->data.byte[2] * 0.1; //Current in Amps from charger to battery. scale 0.1.
  }

   //DC-DC converter status
  void canRX_38A(CAN_FRAME *frame)
  {
    chgStatus = frame->data.byte[4];
    evseDuty = frame->data.byte[3];
    dcBusV = frame->data.byte[2];// Volts scale 2
    temp_4 = frame->data.byte[0]-45;//degC bias -45
    temp_5 = frame->data.byte[1]-45;//degC bias -45
  }

  void gotHundred(CAN_FRAME *frame)
  {
  //  Serial.println("Got special frame!  ");
    Serial.println(frame->id, HEX);
  //  printFrame(frame);
  }

  void printFrame(CAN_FRAME *message)
  {
    Serial.print(message->id, HEX);
    if (message->extended) Serial.print(" X ");
    else Serial.print(" S ");   
    Serial.print(message->length, DEC);
    Serial.print(" ");
    for (int i = 0; i < message->length; i++) {
      Serial.print(message->data.byte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  //zet de timeout waarden voor de can berichten
  void SetCANTimeout()
  {
    CANTimer_321.Timeout = 2000;
    CANTimer_322.Timeout = 2000;
    CANTimer_323.Timeout = 2000;
    CANTimer_324.Timeout = 2000;
    CANTimer_351.Timeout = 2000;
    CANTimer_355.Timeout = 2000;
    CANTimer_356.Timeout = 2000;
    CANTimer_35A.Timeout = 2000;
    CANTimer_373.Timeout = 2000;
    CANTimer_372.Timeout = 2000;
    CANTimer_278.Timeout = 1000;
    CANTimer_28B.Timeout = 1000;
    CANTimer_298.Timeout = 1000;
    CANTimer_734.Timeout = 1000;
    CANTimer_735.Timeout = 1000;
    CANTimer_108.Timeout = 2000;
    CANTimer_109.Timeout = 2000;
    CANTimer_110.Timeout = 2000;
    CANTimer_780.Timeout = 2000;
    CANTimer_781.Timeout = 2000;
    CANTimer_790.Timeout = 2000;
    CANTimer_3B4.Timeout = 2000;
  }

  //
  void CANCheck()
  {
    CANCheckAlive(&CANTimer_321);
    CANCheckAlive(&CANTimer_322);
    CANCheckAlive(&CANTimer_323);
    CANCheckAlive(&CANTimer_324);
    CANCheckAlive(&CANTimer_351);
    CANCheckAlive(&CANTimer_355);
    CANCheckAlive(&CANTimer_356);
    CANCheckAlive(&CANTimer_35A);
    CANCheckAlive(&CANTimer_373);
    CANCheckAlive(&CANTimer_372);
    CANCheckAlive(&CANTimer_278);
    CANCheckAlive(&CANTimer_28B);
    CANCheckAlive(&CANTimer_298);
    CANCheckAlive(&CANTimer_734);
    CANCheckAlive(&CANTimer_735);
    CANCheckAlive(&CANTimer_108);
    CANCheckAlive(&CANTimer_109);
    CANCheckAlive(&CANTimer_110);
    CANCheckAlive(&CANTimer_780);
    CANCheckAlive(&CANTimer_781);
    CANCheckAlive(&CANTimer_790);
    CANCheckAlive(&CANTimer_3B4);

    BMSOnline = CANTimer_355.Online && CANTimer_356.Online && CANTimer_373.Online && CANTimer_372.Online;
    CurrentSensorOnline = true;//CANTimer_321.Online && CANTimer_322.Online && CANTimer_323.Online && CANTimer_324.Online;
    
    if(!CANTimer_351.Online)
    {

    }

    if(!CANTimer_355.Online)
    {
      BMS_SOC = 0;
    }

    if(!CANTimer_356.Online)
    {
      BMS_Voltage = 0;
      BMS_Current = 0;
    }

    if(!CANTimer_35A.Online)
    {
      
    }

    if(!CANTimer_373.Online)
    {
      BMS_MinCellVoltage = 0;
      BMS_MaxCellVoltage = 0;
      BMS_MinTemperature = 0;
      BMS_MaxTemperature = 0;
    }

    if(!CANTimer_372.Online)
    {
      BMS_ConnectedModules = 0;
      BMS_Status = 0;
    }

    if(!CANTimer_28B.Online)
    {
      motorTorque = 0;
      motorRPM = 0;
      motorHVbatteryVolts = 0;
    }

    if(!CANTimer_298.Online)
    {
      motorTempPeak = 0;
      inverterTemp1 = 0;
      inverterTemp2 = 0;
    }

    if(!CANTimer_734.Online)
    {
      motorCurrent1 = 0;
      motorCurrent2 = 0 ;
    }

    if(!CANTimer_735.Online)
    {
      motorTemp1 = 0;
      motorTemp2 = 0;
      avgMotorTemp = 0;
    }



    

  }
// #endif