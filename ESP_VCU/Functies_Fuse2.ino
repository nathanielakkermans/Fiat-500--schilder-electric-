#ifdef DeviceType_Fuse2
  void Outputs()
  {
    if (timer_Outputs.check())
    {
      digitalWrite(OUT1, CAN781RX[0] > 0);
      digitalWrite(OUT2, CAN781RX[1] > 0);
      digitalWrite(OUT3, CAN781RX[2] > 0);
      digitalWrite(OUT4, CAN781RX[3] > 0);
      digitalWrite(OUT5, CAN781RX[4] > 0);
      digitalWrite(OUT6, CAN781RX[5] > 0);  
      // digitalWrite(OUT1, true);
      // digitalWrite(OUT2, true);
      // digitalWrite(OUT3, true);
      // digitalWrite(OUT4, true);
      // digitalWrite(OUT5, true);
      // digitalWrite(OUT6, true);  
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

        // contact uitgangen
        Serial.print("OUT 1_Status: ");
        Serial.println(CAN781RX[0] > 0);
        Serial.print("OUT 2_Status: ");
        Serial.println(CAN781RX[1] > 0);
        Serial.print("OUT 3_Status: ");
        Serial.println(CAN781RX[2] > 0);
        Serial.print("OUT 4_Status: ");
        Serial.println(CAN781RX[3] > 0);
        Serial.print("OUT 5_Status: ");
        Serial.println(CAN781RX[4] > 0);
        Serial.print("OUT 6_Status: ");
        Serial.println(CAN781RX[5] > 0);
        Serial.println();
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
      tx_frame.id = 0x791;
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