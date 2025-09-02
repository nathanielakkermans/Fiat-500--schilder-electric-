// #ifdef DeviceType_Logger || DeviceType_VCU
  //callback BMS Limits
  //callback BMS Limits
  void canRX_351(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_351);
  }

  //callback BMS SOC
  void canRX_355(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_355);
    BMS_SOC = ((frame->data.byte[1] * 256) + frame->data.byte[0]) / 100;
    SOCCorrected = ((frame->data.byte[3] * 256) + frame->data.byte[2]) / 100;
    SOCCorrectedFilt = ((frame->data.byte[5] * 256) + frame->data.byte[4]) / 100;
    BatteryResistanceValue = ((frame->data.byte[7] * 256) + frame->data.byte[6]);
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

  //callback BMS Info
  void canRX_372(CAN_FRAME *frame)
  {
    CANMillisCalculator(&CANTimer_372);
    BMS_ConnectedModules = ((frame->data.byte[1] * 256) + frame->data.byte[0]);
    BMS_Status = frame->data.byte[4];
    switch (BMS_Status)
    {
      case (BMS_Boot):
        BMS_StatusTXT = "Boot";
        break;

      case (BMS_Drive):
        BMS_StatusTXT = "BMS Drive";
        break;

      case (BMS_Precharge):
        BMS_StatusTXT = "Precharge";
        break;

      case (BMS_Ready):
        if (!Inverter_Enable){
          BMS_StatusTXT = "Ready";
        }
        else
        {
          BMS_StatusTXT = "Drive";
        }
        break;

      case (BMS_Charge):
        BMS_StatusTXT = "Charge";
        break;

      case (BMS_Error):
        BMS_StatusTXT = "Error";
        break;
    }
  }


// Inverter Set status
  void canRX_278(CAN_FRAME *frame)
  {
    // CANMillisCalculator(&CANTimer_278);
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
    // CANMillisCalculator(&CANTimer_28B);
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
    // CANMillisCalculator(&CANTimer_734);
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

 //DC-DC converter status
  void canRX_377(CAN_FRAME *frame)
  {
    LV_Volts = ((frame->data.byte[0]<<8) | (frame->data.byte[1]))*0.01;
    LV_Amps = ((frame->data.byte[2]<<8) | (frame->data.byte[3]))*0.1;
    temp_1 = frame->data.byte[4]-45;//degC bias -45
    temp_2 = frame->data.byte[5]-45;//degC bias -45
    temp_3 = frame->data.byte[6]-45;//degC bias -45
    tempMax = max(temp_1,temp_2);
    tempMax = max(tempMax,temp_3);
    tempMax = max(tempMax,temp_4);
    tempMax = max(tempMax,temp_5);
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
    dcBusV = frame->data.byte[2]*2;// Volts scale 2
    temp_4 = frame->data.byte[0]-45;//degC bias -45
    temp_5 = frame->data.byte[1]-45;//degC bias -45
    
  }
  
void canRX_521(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_521);  
  CurrentSensor1.Miliamps = (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_522(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_522);
  CurrentSensor1.Voltage1 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_523(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_523);
  CurrentSensor1.Voltage2 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0); 
} 

void canRX_524(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_524);
  CurrentSensor1.Voltage3 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_525(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_525);
  CurrentSensor1.Temperature =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_526(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_526);
  CurrentSensor1.PowerW =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_527(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_527);
  CurrentSensor1.Current_Counter =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_528(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_528);
  CurrentSensor1.Energy_Counter =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}




void canRX_531(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_531);  
  CurrentSensor2.Miliamps = (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_532(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_532);
  CurrentSensor2.Voltage1 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_533(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_533);
  CurrentSensor2.Voltage2 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0); 
} 

void canRX_534(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_534);
  CurrentSensor2.Voltage3 =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
} 

void canRX_535(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_535);
  CurrentSensor2.Temperature =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_536(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_536);
  CurrentSensor2.PowerW =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_537(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_537);
  CurrentSensor2.Current_Counter =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}

void canRX_538(CAN_FRAME *frame)
{
  CANMillisCalculator(&CANTimer_538);
  CurrentSensor2.Energy_Counter =  (frame->data.byte[5] << 24) + (frame->data.byte[4] << 16) + (frame->data.byte[3] << 8) + (frame->data.byte[2] << 0);
}


  // VCU status
  void canRX_780(CAN_FRAME *frame)
  {
    byte buffer = frame->data.byte[0]; 
    // Serial.print("VCU_State: ");
    // Serial.println(buffer);
    ContactAan = (buffer && 1);
    DeurContact = ((buffer >> 1) & 1);
    Inverter_Enable = ((buffer >> 2) & 1);
    StartPuls = ((buffer >> 3) & 1);
    RemContact = ((buffer >> 4) & 1);
    DriveBlockCharging = ((buffer >> 5) & 1);
    clearToStart =  ((buffer >> 6) & 1);
    ChargePlugDetected = ((buffer >> 7) & 1);
  }

  // fuse 2 status
  void canRX_791(CAN_FRAME *frame)
  {
    Speed = frame->data.byte[1]; 
    
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

//bekijk of de wanneer het laatste bericht binnen was gekomen en of dit nog binnen de timeout valt
void CANCheckAlive(CANTimer *Value)
{
  unsigned long Timeout = Value->ReceivedMillis + Value->Timeout + 2;
  Value->Online = Timeout > millis();
}
void CANCheck()
{
  CANCheckAlive(&CANTimer_521);
  CANCheckAlive(&CANTimer_522);
  CANCheckAlive(&CANTimer_523);
  CANCheckAlive(&CANTimer_524);
  CANCheckAlive(&CANTimer_525);
  CANCheckAlive(&CANTimer_526);
  CANCheckAlive(&CANTimer_527);
  CANCheckAlive(&CANTimer_528);
  CANCheckAlive(&CANTimer_531);
  CANCheckAlive(&CANTimer_532);
  CANCheckAlive(&CANTimer_533);
  CANCheckAlive(&CANTimer_534);
  CANCheckAlive(&CANTimer_535);
  CANCheckAlive(&CANTimer_536);
  CANCheckAlive(&CANTimer_537);
  CANCheckAlive(&CANTimer_538);
  

  if(!CANTimer_521.Online)
  {
    CurrentSensor1.Miliamps = 0;
  }
  if(!CANTimer_522.Online)
  {
    CurrentSensor1.Voltage1 = 0;
  }
  if(!CANTimer_523.Online)
  {
    CurrentSensor2.Voltage2 = 0;
  }
  if(!CANTimer_524.Online)
  {
    CurrentSensor1.Voltage3 = 0;
  }
  if(!CANTimer_525.Online)
  {
    CurrentSensor1.Temperature = 0;
  }
  if(!CANTimer_526.Online)
  {
    CurrentSensor1.PowerW = 0;
  }
  if(!CANTimer_527.Online)
  {
    CurrentSensor1.Current_Counter = 0;
  }
  if(!CANTimer_528.Online)
  {
    CurrentSensor1.Energy_Counter = 0;
  }
  if(!CANTimer_531.Online)
  {
    CurrentSensor2.Miliamps = 0;
  }
  if(!CANTimer_532.Online)
  {
    CurrentSensor2.Voltage1 = 0;
  }
  if(!CANTimer_533.Online)
  {
    CurrentSensor2.Voltage2 = 0;
  }
  if(!CANTimer_534.Online)
  {
    CurrentSensor2.Voltage3 = 0;
  }
  if(!CANTimer_535.Online)
  {
    CurrentSensor2.Temperature = 0;
  }
  if(!CANTimer_536.Online)
  {
    CurrentSensor2.PowerW = 0;
  }
  if(!CANTimer_537.Online)
  {
    CurrentSensor2.Current_Counter = 0;
  }
  if(!CANTimer_538.Online)
  {
    CurrentSensor2.Energy_Counter = 0;
  }
}

  