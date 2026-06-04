#include <esp32_can.h>
#include <Metro.h>
#include "config.h"
#include "Variabele.h"

#ifdef DeviceType_Logger
  #include <WiFi.h>              //Built-in
  #include <ESP32WebServer.h>    //https://github.com/Pedroalbuquerque/ESP32WebServer download and place in your Libraries folder
  #include <ESPmDNS.h>
  #include "CSS.h" //Includes headers of the web and de style file
  // Libraries for SD card
  #include "FS.h"
  #include "SD.h"
  #include <SPI.h>
  /* SERVER */
  ESP32WebServer server(80);
  Metro timer_LoggerLowSpeed = Metro(1000);
  Metro timer_LoggerHighSpeed = Metro(1000);
#endif

#ifdef DeviceType_CurrentSensor
  #include <ADS1115_WE.h> 
  #include <Wire.h>
  #include <esp32_can.h>
  #define I2C_ADDRESS 0x48

  /* There are several ways to create your ADS1115_WE object:
  * ADS1115_WE adc = ADS1115_WE()             -> uses Wire / I2C Address = 0x48
  * ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS)  -> uses Wire / I2C_ADDRESS
  * ADS1115_WE adc = ADS1115_WE(&wire2)       -> uses the TwoWire object wire2 / I2C_ADDRESS
  * ADS1115_WE adc = ADS1115_WE(&wire2, I2C_ADDRESS) -> all together
  * Successfully tested with two I2C busses on an ESP32
  */
  ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);
  Metro timer_ADC = Metro(1);
  Metro timer_SlowSendCAN = Metro(1000);
  Metro timer_FastSendCAN = Metro(100);
#endif

Metro timer_Debug = Metro(1000);


CAN_FRAME tx_frame;
CAN_FRAME rx1_Frame;

#ifdef DeviceType_VCU
  Metro timer_Frames100 = Metro(40);
  Metro timer_Outputs = Metro(1000);
  Metro timer_ADC = Metro(10);
  Metro timer_Input = Metro(10);
  Metro timer_Nextion = Metro(300);
  Metro timer_NextionGraph = Metro(100);
  Metro timer_AC_Charger = Metro(100);
  Metro timer_VCU_Status = Metro(100);
  Metro timer_LIM10 = Metro(10);
  Metro timer_LIM100 = Metro(100);
  Metro timer_LIM200 = Metro(200);
  Metro timer_LIM600 = Metro(600);
  Metro timer_LIM1000 = Metro(1000);
  Metro timer_ACChargerLoop = Metro(1000);
  Metro timer_BatteryResistance = Metro(1000);
  byte i=0;
  //nextion
  #include "EasyNextionLibrary.h" // Include EasyNextionLibrary
  EasyNex myNex(Serial2);   // Create an object of EasyNex class with the name < myNex >
  uint16_t voltageGraph;   // a variable to store the reading
#endif

#ifdef DeviceType_Fuse
  Metro timer_Outputs = Metro(10);
  Metro timer_Fuse_Status = Metro(100);
  Metro timer_Input = Metro(100);
#endif

#ifdef DeviceType_Fuse2
  Metro timer_Outputs = Metro(10);
  Metro timer_Fuse_Status = Metro(100);
  Metro timer_Input = Metro(100);
#endif

#ifdef DeviceType_BMW_BMS
  #include "CRC8.h"
  CRC8 crc8;
  Metro timer_BMS_SendCommand = Metro(50);
#endif

#ifdef DeviceType_GSM
  #include <TinyGsmClient.h>
  #include <TinyGPS++.h>
  // #include <WiFi.h>
  // #include <WiFiClient.h>
  // #include <BlynkSimpleEsp32.h>
  #include <BlynkSimpleTinyGSM.h>
  #include <Arduino.h>
  // #include <Wire.h>

  BlynkTimer timer;
  TinyGsm modem(SerialAT);
  // The TinyGPS++ object
  TinyGPSPlus gps;
  Metro timer_GSMTimeout = Metro(3000);
#endif

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(500000);
  Serial.println("Initializing ...");

  #ifdef DeviceType_VCU
    Serial.println("Device type VCU");
    pinMode(IN1, INPUT);
    pinMode(IN2, INPUT);
    pinMode(IN3, INPUT);
    pinMode(IN4, INPUT);
    pinMode(IN5, INPUT);
    pinMode(IN6, INPUT);
    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);
    pinMode(IN5, INPUT_PULLDOWN);
    pinMode(IN6, INPUT_PULLDOWN);
    pinMode(OUT1, OUTPUT); 
    // pinMode(StatusLED, OUTPUT);
    myNex.begin(250000); // Begin the object with a baud rate of 115200
    Serial2.begin(250000, SERIAL_8N1, RXD2, TXD2);
    CAN0.setCANPins(GPIO_NUM_16, GPIO_NUM_17);  //RX, TX
    CAN0.begin(500000);
    Serial.println("Ready ...!");
    LEDPettern = LED_OK;  

    #ifdef deepsleep
    //speep
    //Print the wakeup reason for ESP32
    print_wakeup_reason();
    //deur open wakker worden
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,0); //1 = High, 0 = Low
    //contact aan wakker worden
    esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);
    #endif

    // // Initialize MCP2517FD CAN controller at the specified speed
    // if(CAN1.begin(500000))
    // {
    //   Serial.println("MCP2517FD Init OK ...");
    // } else {
    //   Serial.println("MCP2517FD Init Failed ...");
    // }
    // CAN1.watchFor(); //allow anything through
  #endif  
  
  #ifdef DeviceType_Fuse
    Serial.println("Device type FUSE");
    pinMode(IN1, INPUT);
    pinMode(IN2, INPUT);
    pinMode(IN3, INPUT);
    pinMode(IN4, INPUT);
    pinMode(IN5, INPUT);
    pinMode(IN6, INPUT);
    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);
    pinMode(IN5, INPUT_PULLDOWN);
    pinMode(IN6, INPUT_PULLDOWN);
    // pinMode(OUT1, OUTPUT); 
    pinMode(OUT2, OUTPUT); 
    pinMode(OUT3, OUTPUT); 
    // pinMode(OUT4, OUTPUT); 
    // pinMode(OUT5, OUTPUT); 
    // pinMode(OUT6, OUTPUT); 
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    CAN0.setCANPins(GPIO_NUM_5, GPIO_NUM_4);
    CAN0.begin(500000);  
    LEDPettern = LED_OK;  
    // configure LED PWM functionalitites
    ledcSetup(OUT1_Channel, 2000, resolution);
    ledcSetup(OUT4_Channel, freq, resolution);
    ledcSetup(OUT5_Channel, freq, resolution);
    ledcSetup(OUT6_Channel, freq, resolution);
    ledcAttachPin(OUT1, OUT1_Channel);
    ledcAttachPin(OUT4, OUT4_Channel);
    ledcAttachPin(OUT5, OUT5_Channel);
    ledcAttachPin(OUT6, OUT6_Channel);
    ledcWrite(OUT1_Channel, 127);
  #endif

  #ifdef DeviceType_Fuse2
    Serial.println("Device type FUSE2");
    pinMode(IN1, INPUT);
    pinMode(IN2, INPUT);
    pinMode(IN3, INPUT);
    pinMode(IN4, INPUT);
    pinMode(IN5, INPUT);
    pinMode(IN6, INPUT);
    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);
    pinMode(IN5, INPUT_PULLDOWN);
    pinMode(IN6, INPUT_PULLDOWN);
    pinMode(OUT1, OUTPUT); 
    pinMode(OUT2, OUTPUT); 
    pinMode(OUT3, OUTPUT); 
    pinMode(OUT4, OUTPUT); 
    pinMode(OUT5, OUTPUT); 
    pinMode(OUT6, OUTPUT); 
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    CAN0.setCANPins(GPIO_NUM_5, GPIO_NUM_4);
    CAN0.begin(500000);  
  #endif

  #ifdef DeviceType_Logger
    LOG_LOW[0].Name = "hoi 1";
    LOG_LOW[1].Name = "hoi 2";
    LOG_LOW[2].Name = "hoi 3";
    LOG_LOW[3].Name = "hoi 4";
    LOG_LOW[4].Name = "hoi 5";

    Serial.println("Device type Logger");
    // Initialize SD card
    if(!SD.begin(SD_CS)) {
      LEDPettern = LED_ERROR;
      Serial.println("Card Mount Failed");
      SD_present = false; 
    }
    {
      Serial.println(F("Card initialised... file access enabled..."));
      SD_present = true; 
      LEDPettern = LED_OK;
    }

    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
      LEDPettern = LED_ERROR;
      Serial.println("No SD card attached");
      return;
    }
    Serial.println("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
      LEDPettern = LED_ERROR;
      Serial.println("ERROR - SD card initialization failed!");
      return;    // init failed
    }

    Serial.println("card initialized.");
    //char filename[20]; // make it long enough to hold your longest file name, plus a null terminator
    int n = 0;
    snprintf(FileNameLow, sizeof(FileNameLow), NameLOW, n); // includes a three-digit sequence number in the file name
    while(SD.exists(FileNameLow)) {
      n++;
      snprintf(FileNameLow, sizeof(FileNameLow), NameLOW, n);
    }
    File dataFile = SD.open(FileNameLow,FILE_READ);
    Serial.println(n);
    Serial.println(FileNameLow);
    dataFile.close();
    //now filename[] contains the name of a file that doesn't exist

    // If the data.txt file doesn't exist
    // Create a file on the SD card and write the data labels
    File file = SD.open(FileNameLow);
    if(!file) {
      LEDPettern = LED_OK;
      Serial.println("File doens't exist");
      Serial.println("Creating file low...");
      //maak de index string
      String StringBuffer = SetLogNames();
      Serial.println(StringBuffer);
      writeFile(SD, FileNameLow, "Time, Temperature1, Temperature2, Temperature3, Temperature4, Temperature5, Temperature6, Temperature7, Temperature8, Temperature9, Temperature10 \r\n");
    }
    else {
      Serial.println("File already exists");  
    }
    file.close();

    n = 0;
    snprintf(FileNameHigh, sizeof(FileNameHigh), NameHIGH, n); // includes a three-digit sequence number in the file name
    while(SD.exists(FileNameHigh)) {
      n++;
      snprintf(FileNameHigh, sizeof(FileNameHigh), NameHIGH, n);
    }
    dataFile = SD.open(FileNameHigh,FILE_READ);
    Serial.println(n);
    Serial.println(FileNameHigh);
    dataFile.close();
    // now filename[] contains the name of a file that doesn't exist

    // If the data.txt file doesn't exist
    // Create a file on the SD card and write the data labels
    SD.open(FileNameHigh);
    if(!file) {
      LEDPettern = LED_OK;
      Serial.println("File doens't exist");
      Serial.println("Creating file high...");
      //maak de index string
      String StringBuffer = SetLogNames();
      Serial.println(StringBuffer);
      writeFile(SD, FileNameHigh, "Time, Temperature1, Temperature2, Temperature3, Temperature4, Temperature5, Temperature6, Temperature7, Temperature8, Temperature9, Temperature10 \r\n");
    }
    else {
      Serial.println("File already exists");  
    }
    file.close();

    //Server    
    WiFi.softAP("MyCircuits", "12345678"); //Network and password for the access point genereted by ESP32
    //Set your preferred server name, if you use "mcserver" the address would be http://mcserver.local/
    if (!MDNS.begin(servername)) 
    {          
      Serial.println(F("Error setting up MDNS responder!")); 
      ESP.restart(); 
    } 
    /*********  Server Commands  **********/
    server.on("/",         SD_dir);
    server.on("/upload",   File_Upload);
    server.on("/fupload",  HTTP_POST,[](){ server.send(200);}, handleFileUpload);
    server.begin();
    Serial.println("HTTP server started");
    
  #endif

  #ifdef DeviceType_CurrentSensor
    Wire.begin();
    Serial.println("Device type Current sensor");
    CAN0.setCANPins(GPIO_NUM_5, GPIO_NUM_4);  //RX, TX
    CAN0.begin(500000);
    // CAN0.watchFor(); //allow anything through
    ledcSetup(PWM1_Channel, freq, resolution);
    ledcSetup(PWM2_Channel, freq, resolution);
    ledcAttachPin(PWM1, PWM1_Channel);
    ledcAttachPin(PWM2, PWM2_Channel);
    

    if(!adc.init()){
        Serial.println("ADS1115 not connected!");
        LEDPettern = LED_ERROR;
      }
    else{
        LEDPettern = LED_OK;
      }
    adc.setVoltageRange_mV(ADS1115_RANGE_4096); //comment line/change parameter to change range
    adc.setCompareChannels(ADS1115_COMP_0_GND); //comment line/change parameter to change channel
    adc.setConvRate(ADS1115_860_SPS); 
    adc.setMeasureMode(ADS1115_CONTINUOUS); //comment line/change parameter to change mode
  #endif
 
  #ifdef DeviceType_BMW_BMS
    Serial.println("Device type BMS_BMS");
    CAN0.setCANPins(GPIO_NUM_16, GPIO_NUM_17);  //RX, TX
    CAN0.begin(500000);
    crc8.begin();
    pinMode(OUT1, OUTPUT); 
    digitalWrite(OUT1, true);
    LEDPettern = LED_OK;
  #endif

  #ifdef DeviceType_GSM
    GSMSetup();
  #endif

  // #ifdef DeviceType_VCU
    CAN0.watchFor(0x351); //setup a special filter
    CAN0.watchFor(0x355); //setup a special filter
    CAN0.watchFor(0x356); //setup a special filter
    CAN0.watchFor(0x35A); //setup a special filter
    CAN0.watchFor(0x373); //setup a special filter
    CAN0.watchFor(0x372); //setup a special filter
    
    CAN0.watchFor(0x287); //setup a special filter
    CAN0.watchFor(0x289); //setup a special filter
    CAN0.watchFor(0x299); //setup a special filter
    CAN0.watchFor(0x732); //setup a special filter
    CAN0.watchFor(0x733); //setup a special filter

    CAN0.watchFor(0x521); //IVT_Msg_Result_I
    CAN0.watchFor(0x522); //IVT_Msg_Result_U1
    CAN0.watchFor(0x523); //IVT_Msg_Result_U2
    CAN0.watchFor(0x524); //IVT_Msg_Result_U3

    CAN0.watchFor(0x780); //VCU status
    CAN0.watchFor(0x781); //VCU status
    CAN0.watchFor(0x790); //Fuse status

    CAN0.watchFor(0x377); //DC-DC converter status
    CAN0.watchFor(0x389); //DC-DC converter status
    CAN0.watchFor(0x38A); //DC-DC converter status

    

    CAN0.watchFor(); //then let everything else through anyway
    CAN0.setCallback(0, canRX_351); //callback BMS Limits
    CAN0.setCallback(1, canRX_355); //callback BMS SOC
    CAN0.setCallback(2, canRX_356); //callback BMS Status
    CAN0.setCallback(3, canRX_35A); //callback BMS Warnings
    CAN0.setCallback(4, canRX_373); //callback BMS Low and High
    CAN0.setCallback(5, canRX_372); //callback BMS Info

    CAN0.setCallback(6, canRX_278); //callback Inverter Set function and torque
    CAN0.setCallback(7, canRX_288); //callback Inverter RPM Battery and Torque
    CAN0.setCallback(8, canRX_298); //callback Inverter Temps
    CAN0.setCallback(9, canRX_75A); //callback Inverter current
    CAN0.setCallback(10, canRX_75B); //callback Motor Temps

    CAN0.setCallback(11, canRX_521); //callback current sensor stroom
    CAN0.setCallback(12, canRX_522); //callback current sensor v1
    CAN0.setCallback(13, canRX_523); //callback current sensor v2
    CAN0.setCallback(14, canRX_524); //callback current sensor v3

    CAN0.setCallback(15, canRX_780); //VCU status
    CAN0.setCallback(16, canRX_781); //VCU status
    CAN0.setCallback(17, canRX_790); //Fuse status

    CAN0.setCallback(18, canRX_377);  //DC-DC converter status
    CAN0.setCallback(19, canRX_389);  //DC-DC converter status
    CAN0.setCallback(20, canRX_38A);  //DC-DC converter status

    SetCANTimeout();
  // #endif


}

void loop() {
long us = micros();
long diff = us - prev;
#ifdef DeviceType_VCU  
  //zet de 12 volt en 5 volt bus aan
  digitalWrite(OUT1, VCU_Aan);


  //vcu inschakel statemachine
  switch (VCU_State) {
    case 0:
      LEDPettern = LED_SLEEP;
      //als de deur open gaan of contact aan dan VCU aan
      if (ContactAan || DeurContact || (ChargePlugDetected && !ChargeFinished))
        {
          VCU_State = 1;
          LEDPettern = LED_OK;
        }
      break;

    case 1:
      //zet VCU aan en start timer, als contact aan gaat dan naar de volgende case gaan
      VCU_Aan = true;
      //als de deur dicht gaat begin dan met de timer
      if (!DeurContact)
        {
          startMillis = millis();  //initial start time
          VCU_State = 2;
        } 
      if (ContactAan || ChargePlugDetected)
        {
          VCU_State = 3;
        }
      break;
        
    case 2:
        VCU_Aan = true;
        //timer om de vcu weer uit te zetten als het contact niet word aangezet
        currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
        if (currentMillis - startMillis >= StartPeriod)  //test whether the period has elapsed
        {
          VCU_State = 10;
        }
        if (ContactAan || ChargePlugDetected)
        {
          VCU_State = 3;
        }
      break;
      
    case 3:
        //vcu staat aan
        VCU_Aan = true;
        if (!ContactAan)
        {
          startMillis = millis();  //initial start time
          VCU_State = 4;
        }
      break;

    case 4:
        //uitstappen
        currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
        
        if (currentMillis - startMillis >= UitstapPeriod)
        {
          if (!DeurContact)
          {
            VCU_State = 10;  
          }
        }
        //als contact in deze tijd weer aan gaan dan weer inschakelen
        if (ContactAan || (ChargePlugDetected && !ChargeFinished))
        {
          VCU_State = 3;
        }
      break;
    case 10:
        //vcu uitzetten en gaan slapen
        VCU_Aan = false;
        VCU_State = 0;
        //voorkom dat die niet direct weer aan gaat
        delay(100);
        #ifdef deepsleep
        //slapen
        Serial.println("Going to sleep now");
        Serial.flush(); 
        delay(1000);
        esp_deep_sleep_start();
        #endif
      break;

      
    default:
      // statements
      break;
  }


    switch(VCU_StartState){
      case 0:
        Inverter_Enable = false;
        if(VCU_Aan){
          VCU_StartState = 1;
        }
      break;
      case 1:
        if (!ReverseRequest && !ForwardRequest){
          VCU_StartState = 2;
        }
      break;
      case 2:
        if (ForwardRequest && TPS1 <= 0 && TPS2 <= 0 && BMS_Status == BMS_Ready && !ChargePlugDetected && RemContact) {
          VCU_StartState = 3;
        }
        if (ReverseRequest && TPS1 <= 0 && TPS2 <= 0 && BMS_Status == BMS_Ready && !ChargePlugDetected && RemContact) {
          VCU_StartState = 4;
        }
      break;
      //ga vooruit
      case 3:
        Inverter_Enable = true;
        Reverse = false;
        if (!ForwardRequest){
          VCU_StartState = 0;
        }
      break;
      //ga achteruit
      case 4:
        Inverter_Enable = true;
        Reverse = true;
        if (!ReverseRequest){
          VCU_StartState = 0;
        }
      break;
    default:
      // statements
      break;
    }


    //als de VCU aan staat dan controleren of de inverter gestart mag worden
    if (VCU_Aan)
    {
    //   // if (RemContact && StartPuls && TPS1 <= 0 && TPS2 <= 0 && BMS_Status == BMS_Ready && !ChargePlugDetected)
    //   if (StartPuls && TPS1 <= 0 && TPS2 <= 0 && BMS_Status == BMS_Ready && !ChargePlugDetected)
    //   {
    //     Inverter_Enable = true;
    //     StartPuls = false;
    //   }
    }

    if (VCU_State != 3 || ChargePlugDetected || BMS_Status != BMS_Ready)
    {
      VCU_StartState = 0;
    }

    //zet inverter aan en uit als de VCU in "Enable" staat
    if (Inverter_Enable)
      {
        //0x00,0x02=no inverter response to torque
        //0x03=front motor responds (possibly rear also)
        //0x04=generator only responds to torque
        //0x05=generator and front motor respond to torque.
        function = 3;
      }
    if (!Inverter_Enable)
      {
        function = 0;
      }

  
  

    //waterpomp
    Waterpomp = Inverter_Enable || ChargePlugDetected || motorTemp1 > 50 || motorTemp2 > 50;

    //oliepomp
    // Oliepomp = Inverter_Enable && (TPS > 400 || motorTemp1 > 50 || motorTemp2 > 50);

    //Vacuumpomp
    Vacuumpomp = RemContact;

  //  byte i = 0;
  //  CAN_FRAME message;
  //  if (CAN0.read(message)) {
  
  //    printFrame(&message);
  
  //    // Send out a return message for each one received
  //    // Simply increment message id and data bytes to show proper transmission
  //    // Note: this will double the traffic on the network (provided it passes the filter above)
  // //    message.id++;
  // //    for (i = 0; i < message.length; i++) {
  // //      message.data.uint8[i]++;
  // //    }
  //    //CAN.sendFrame(message);
  //  }



  //   if (CAN0.read(rx1_Frame)) {
  //     Serial.println("berecht op can1: ");
  //     // Print message
  //     Serial.print("ID: ");
  //     Serial.println(rx1_Frame.id,HEX);
  //     Serial.print("Extended: ");
  //     if(rx1_Frame.extended) {
  //       Serial.println("Yes");
  //     } else {
  //       Serial.println("No");
  //     }
  //     Serial.print("Length: ");
  //     Serial.println(rx1_Frame.length,DEC);
  //     for(i = 0;i < rx1_Frame.length; i++) {
  //       Serial.print(rx1_Frame.data.byte[i],HEX);
  //       Serial.print(" ");
  //     }
  //     Serial.println();
  //     Serial.println();



  //   // 	// Send out a return message for each one received
  //   // 	// Simply increment message id and data bytes to show proper transmission
  //   // 	// Note: this will double the traffic on the network (provided it passes the filter above)
  //   // 	rx1_Frame.id++;
  //   // 	for(i = 0;i < rx1_Frame.length; i++) {
  //   // 		rx1_Frame.data.byte[i]++;
  //   // 	}
  //   }

    TaskCounter(TimerInputs, true);
    Inputs();
    TaskCounter(TimerInputs, false);

    TaskCounter(TimerADC_Read, true);
    ADC_Read();
    TaskCounter(TimerADC_Read, false);

    TaskCounter(TimerDebug, true);
    Debug();
    TaskCounter(TimerDebug, false);

    if(VCU_Aan){
      TaskCounter(TimerMsgs100ms, true);
      Msgs100ms();  //fire the 100ms can messages
      TaskCounter(TimerMsgs100ms, false);

      TaskCounter(Timercheckforinput, true);
      checkforinput();
      TaskCounter(Timercheckforinput, false);

      // Outputs();

      
  
      // TaskCounter(TimerDebug, true);
      // Debug();
      // TaskCounter(TimerDebug, false);

      TaskCounter(TimerAC_Charger, true);
      AC_Charger();
      TaskCounter(TimerAC_Charger, false);
    
      TaskCounter(TimerNextionUpdate, true);
      NextionUpdate();
      TaskCounter(TimerNextionUpdate, false);
    
      TaskCounter(TimerNextionListen, true);
      // myNex.NextionListen();
      TaskCounter(TimerNextionListen, false);
    
      // NextionGraphUpdate();

      VCU_Status();

      ACChargerLoop();
      BatteryResistanceCalc();
    }
  #endif
  



  CANCheck();



  
  LEDBlink();
  
prev = micros();
if (diff > CycleMax)
  {
    CycleMax = diff;    
  }
// Serial.println(diff);
}
