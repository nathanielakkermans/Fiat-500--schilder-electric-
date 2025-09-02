#ifdef DeviceType_CurrentSensor 
  void DebugCurrentSensor()
  {
    if (timer_Debug.check())
    {
      Serial.print("Amps : ");
      Serial.println(Amps);

      Serial.print("voltage 1 : ");
      Serial.println(Voltage1);    

      Serial.print("voltage 2 : ");
      Serial.println(Voltage2);


      Serial.print("voltage 3 : ");
      Serial.println(Voltage3);


    }
  }


  void ReadADC()
  {
    if (timer_ADC.check())
      {
        switch (ADS1115_Case) {
          case 0:
            ADC_voltage[0] =  adc.getRawResult(); // alternative: getResult_mV for Millivolt
            adc.setCompareChannels(ADS1115_COMP_1_GND);
            Amps = (ADC_voltage[0] - RAW_ADC_Offset);
            Amps = (Amps / AmpeScale) * -1;
            // Amps = Amps -0.75;
            Miliamps = Amps * 1000;
            ADS1115_Case = 1;
            break;
          case 1:
            ADC_voltage[1] =  adc.getRawResult(); // alternative: getResult_mV for Millivolt
            adc.setCompareChannels(ADS1115_COMP_2_GND);
            Voltage1 = ADC_voltage[1] / VoltageScale;
            ADS1115_Case = 2;
            break;
          case 2:
            ADC_voltage[2] =  adc.getRawResult(); // alternative: getResult_mV for Millivolt
            adc.setCompareChannels(ADS1115_COMP_3_GND);
            Voltage2 = ADC_voltage[2] / VoltageScale;
            ADS1115_Case = 3;
            break;
          case 3:
            ADC_voltage[3] =  adc.getRawResult(); // alternative: getResult_mV for Millivolt
            adc.setCompareChannels(ADS1115_COMP_0_GND);
            Voltage3 = (ADC_voltage[3] / VoltageScale) / 1000;
            ADS1115_Case = 0;
            break;
          default:
          
            break;
        }
        int Temp1;
        if (Voltage3 < 500)
        {
          Temp1 = map(Voltage3,0,500,908,3030); // 0 tot 500 volt in, 1,42 tot 4,8 volt uit
          ledcWrite(PWM1_Channel, Temp1);
          ledcWrite(PWM2_Channel, Temp1);
          // Serial.println(Temp1);
        }
       else
       {
         Serial.println("bug");
       }

        // //lees 4x ADC, 5,5ms voor alle kanalen uit te kunnen lezen met 3x een delay van 350us. als er input waarden "lekken" naar elkaar dan de delay tijd verhogen
        // ADC_voltage[3] = ADC_readChannel(ADS1115_COMP_0_GND);
        // delayMicroseconds(350);
        // ADC_voltage[0] = ADC_readChannel(ADS1115_COMP_1_GND);
        // delayMicroseconds(350);
        // ADC_voltage[1] = ADC_readChannel(ADS1115_COMP_2_GND);
        // delayMicroseconds(350);
        // ADC_voltage[2] = ADC_readChannel(ADS1115_COMP_3_GND); 

      }
  }
    

  void SendSensorCAN()
  {
    if (timer_FastSendCAN.check())
    {
      //IVT_Msg_Result_I
      tx_frame.rtr = 0;
      tx_frame.id = 0x521;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Miliamps >> 0 & 0xff;
      tx_frame.data.uint8[3] = Miliamps >> 8 & 0xff;
      tx_frame.data.uint8[4] = Miliamps >> 16 & 0xff;
      tx_frame.data.uint8[5] = Miliamps >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

      //IVT_Msg_Result_U1
      tx_frame.rtr = 0;
      tx_frame.id = 0x522;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Voltage1 >> 0 & 0xff;
      tx_frame.data.uint8[3] = Voltage1 >> 8 & 0xff;
      tx_frame.data.uint8[4] = Voltage1 >> 16 & 0xff;
      tx_frame.data.uint8[5] = Voltage1 >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

      //IVT_Msg_Result_U2
      tx_frame.rtr = 0;
      tx_frame.id = 0x523;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Voltage2 >> 0 & 0xff;
      tx_frame.data.uint8[3] = Voltage2 >> 8 & 0xff;
      tx_frame.data.uint8[4] = Voltage2 >> 16 & 0xff;
      tx_frame.data.uint8[5] = Voltage2 >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);


      //IVT_Msg_Result_U3
      tx_frame.rtr = 0;
      tx_frame.id = 0x524;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00;
      tx_frame.data.uint8[2] = Voltage3 >> 0 & 0xff;
      tx_frame.data.uint8[3] = Voltage3 >> 8 & 0xff;
      tx_frame.data.uint8[4] = Voltage3 >> 16 & 0xff;
      tx_frame.data.uint8[5] = Voltage3 >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);
    }
    
    if (timer_SlowSendCAN.check())
    {
      //VT_Msg_Result_T
      tx_frame.rtr = 0;
      tx_frame.id = 0x525;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Temperature & 0xff;
      tx_frame.data.uint8[3] = Temperature >> 8 & 0xff;
      tx_frame.data.uint8[4] = Temperature >> 16 & 0xff;
      tx_frame.data.uint8[5] = Temperature >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

      //IVT_Msg_Result_W
      tx_frame.rtr = 0;
      tx_frame.id = 0x526;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Power & 0xff;
      tx_frame.data.uint8[3] = Power >> 8 & 0xff;
      tx_frame.data.uint8[4] = Power >> 16 & 0xff;
      tx_frame.data.uint8[5] = Power >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

      //IVT_Msg_Result_As
      tx_frame.rtr = 0;
      tx_frame.id = 0x527;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Current_Counter & 0xff;
      tx_frame.data.uint8[3] = Current_Counter >> 8 & 0xff;
      tx_frame.data.uint8[4] = Current_Counter >> 16 & 0xff;
      tx_frame.data.uint8[5] = Current_Counter >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

      //IVT_Msg_Result_Wh
      tx_frame.rtr = 0;
      tx_frame.id = 0x528;
      tx_frame.extended = false;
      tx_frame.length = 6;
      tx_frame.data.uint8[0] = 0x00;
      tx_frame.data.uint8[1] = 0x00; 
      tx_frame.data.uint8[2] = Energy_Counter & 0xff;
      tx_frame.data.uint8[3] = Energy_Counter >> 8 & 0xff;
      tx_frame.data.uint8[4] = Energy_Counter >> 16 & 0xff;
      tx_frame.data.uint8[5] = Energy_Counter >> 24 & 0xff;
      CAN0.sendFrame(tx_frame);

    }
  }

  float ADC_readChannel(ADS1115_MUX channel) {
    int voltage = 0.0;
    adc.setCompareChannels(channel);
    voltage =  adc.getRawResult(); // alternative: getResult_mV for Millivolt
    return voltage;
  }
#endif