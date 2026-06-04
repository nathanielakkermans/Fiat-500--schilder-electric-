  long prev = 0;
  long CycleMax = 0;

  bool ContactAan;
  bool StartPuls;
  bool DeurContact;
  bool RemContact;
  bool Inverter_Enable;
  bool Dash_licht_Button;
  bool Cruise;
  bool Waterpomp;
  bool Vacuumpomp;
  bool Oliepomp;

  bool ForwardRequest;
  bool ReverseRequest;
  bool Reverse;

  int VCU_StartState;

  byte ACcur=0;
  byte CABlim=0;
  byte Pilot=0;
  bool PP=false;

  byte CAN781RX[8];
  
 #ifdef DeviceType_VCU
  float ADC_Value1;
  float ADC_Value2;
  float ADC_Value3;
  float ADC_Value4;
  float ADC_ValueVCU_Voltage;
  float FiltertVCU_Voltage;

  bool VCU_Aan;
  int VCU_State = 0;
  bool InverterDirection;   //false voor vooruit


  //contact timer
  unsigned long startMillis;  //some global variables available anywhere in the program
  unsigned long ReverseMillis;
  unsigned long ChargeMillis;
  unsigned long currentMillis;
  const unsigned long StartPeriod = 15000;  //the value is a number of milliseconds
  const unsigned long UitstapPeriod = 5000;  //the value is a number of milliseconds

  uint16_t TorqueVal=10000;
  uint16_t TorqueReq=0;
  byte  TorqueLo=0;
  byte  TorqueHi=0;
  byte  function=0x00; 

  float TPS;
  float TPS1;
  float TPS2;
  float Clutch;
  int TPS_Diff;
  int TPS_DiffMin;
  int TPS_DiffMax;
  int ADC1_Min = 0;
  int ADC2_Min = 0;
  int ADC4_Min = 120;
  int ADC1_Max = 2000;
  int ADC2_Max = 2000;
  int ADC4_Max = 180;
  int TorqueCommandMin = 0;
  int TorqueCommandMax = 1100;//2100 = 210Nm
  int TorqueCommandRegen = 300;
  
  float PP_Voltage;
  float PP_Ref = 4600;
  float PP_PullUp = 1000;
  float PP_Res = 0;
  bool ChargePlugDetected;
  bool ChargePlugWasDisconnected;



  ////////sleep parameters//////////////
  #define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
  #define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */
  //#define BUTTON_PIN_BITMASK 0xC000 // pin 14 en 15
  #define BUTTON_PIN_BITMASK 0x8000 // pin 15
  RTC_DATA_ATTR int bootCount = 0;
#endif

#ifdef DeviceType_Fuse
  bool IN1_Status;
  bool IN2_Status;
  bool IN3_Status;
  bool IN4_Status;
  bool IN5_Status;
  bool IN6_Status;
  int LED_Color;
  bool Buzzer;
#endif  

#ifdef DeviceType_Fuse2
  bool IN1_Status;
  bool IN2_Status;
  bool IN3_Status;
  bool IN4_Status;
  bool IN5_Status;
  bool IN6_Status;
#endif  

#ifdef DeviceType_Logger
  #define servername "CAN Logger" //Define the name to your server... 
  bool   SD_present = false; //Controls if the SD card is present or not

  const char* NameLOW    = "/datalow%05d.csv";
  const char* NameHIGH    = "/datahigh%05d.csv";
  char FileNameLow[20];
  char FileNameHigh[20];

  unsigned long StartMillis = 0; 
  unsigned long StopMillis = 0; 

  int readingID = 0;

  String dataMessage;

  #define NumberLowLOG 5
  #define NumberLoHIGH 10

  struct LOG_Message {          
      String Name;
      float Value;
  };
  LOG_Message LOG_LOW[NumberLowLOG];
  LOG_Message LOG_HIGH[NumberLoHIGH];

  // Temperature Sensor variables
  float temperature1;
  float temperature2;
  float temperature3;
  float temperature4;
  float temperature5;
  float temperature6;
  float temperature7;
  float temperature8;
  float temperature9;
  float temperature10;
#endif

#ifdef DeviceType_CurrentSensor
  int ADS1115_Case;
  byte i=0;
  float Amps;       //A
  // signed long Miliamps;     
  // signed long Voltage1;
  // signed long Voltage2;
  // signed long Voltage3;
  signed long Temperature;
  signed long Power;
  signed long Current_Counter;
  signed long Energy_Counter;
  float VoltageScale = (5.1/605.1) * 8; //HV voltrage deler R1 = 600k, R2 = 5.1k, 0,08428 versterking
  // float AmpeScale = 15.2;
  float AmpeScale = 53;
  int RAW_ADC_Offset = 19900;
  //buffer voor adc waarden
  int ADC_voltage[4];


#endif

#ifdef DeviceType_BMW_BMS
  uint8_t nextmes = 0;
  uint8_t mescycle = 0;
  uint8_t testcycle = 0;
  unsigned long balancetimer = 0;
  int debug = 1;
  bool balancepauze = 0;
  int balancecells;
  const uint8_t finalxor [12] = {0xCF, 0xF5, 0xBB, 0x81, 0x27, 0x1D, 0x53, 0x69, 0x02, 0x38, 0x76, 0x4C};
#endif

#ifdef DeviceType_GSM
    /* Fill-in your Template ID (only if using Blynk.Cloud) */
  #define BLYNK_TEMPLATE_ID "TMPLzmg8Rk1-"
  #define BLYNK_TEMPLATE_NAME "auto"
  #define BLYNK_AUTH_TOKEN "wjuxkde3KSWFJQgf9TBVYfY8zmuHITbD"
  // Select your modem:
  #define TINY_GSM_MODEM_SIM7080
  // You should get Auth Token in the Blynk App.
  // Go to the Project Settings (nut icon).
  char auth[] = BLYNK_AUTH_TOKEN;

  // Your WiFi credentials.
  // Set password to "" for open networks.
  // char ssid[] = "VodafoneMobileWiFi-C09989";
  // char pass[] = "0639943116";

  // Your GPRS credentials
  // Leave empty, if missing user or pass
  char apn[]  = "internet";
  char user[] = "";
  char pass[] = "";

  bool reply = false;
  int satellites;
  int GPSSpeed;
  float flat, flon;
  unsigned long age;
#endif

//  #ifdef DeviceType_VCU || DeviceType_Logger
  //motor status
  int motorRPM = 0;
  int motorTempPeak = 0;
  int motorTemp1 = 0;
  int motorTemp2 = 0;
  int motorHVbatteryVolts = 0;
  int motorTorque = 0;
  int motorCurrent1 = 0;
  int motorCurrent2 = 0;
  int avgMotorTemp = 0;
  int motorPower = 0;
  bool InverterInDrive = 0;

  int inverterTemp1 = 0;
  int inverterTemp2 = 0;
  int avgInverterTemp = 0;

  //BMS
  float BMS_Power;
  int BMS_SOC;
  int BMS_Voltage;
  signed int BMS_Current;
  int BMS_MinCellVoltage;
  int BMS_MaxCellVoltage;
  int BMS_MinTemperature;
  int BMS_MaxTemperature;
  int BMS_ConnectedModules;
  int BMS_Status;
  #define BMS_Boot 0
  #define BMS_Ready 1
  #define BMS_Drive 2
  #define BMS_Charge 3
  #define BMS_Precharge 4
  #define BMS_Error 5
  String BMS_StatusTXT;

  //DC-DC converter
  uint16_t setVolts = 398, actVolts , termAmps;
  int16_t actAmps;
  uint8_t currentRamp;
  bool clearToStart=true;
  static uint8_t chgStatus , evseDuty;
  static float dcBusV , temp_1 , temp_2 , temp_3 , temp_4 , temp_5 , ACVolts , DCAmps , ACAmps;
  static float LV_Volts , LV_Amps;
  static float Voltspnt = 398400;


  // //tesla charger
  // int MaxDCvoltage;
  // int MaxDCcurrent;
  // int DCvoltage;
  // int DCcurrent;
  // int Charging;
  // bool ChargePlugDetected;
  // int SetDCvoltage = 398;
  // int SetDCcurrent = 30;
  // int SetDCcurrentMax = 30;
  // byte SetACcurrent;
  // int SetCharging;
  // signed int ChargerTemp;
  int MaxCellVoltageCharge = 4180;
  int MacSOCCharge = 10000;
  signed long MinChargeCurrent = 30;  //3 amp
  int ACChargeState;
  bool ChargeFinished;


  //current sensor
  signed long Miliamps;     //mA
  signed long Voltage1;     //mV
  signed long Voltage2;
  signed long Voltage3;
  int SOC;
  signed long MiliampsLast;  //mA
  signed long Voltage1Last;  //mV   
  signed long MiliampsDelta;  //mA
  signed long MiliampsThreshold = -50000;  //mA
  signed long Voltage1Delta;   //mV
  float BatteryResistanceValue = 0.07; //ohm
  signed long Voltage1Corrected;  //mV  
  float SOCCorrectedFilt;
  int SOCCorrected;
  bool BMSOnline;
  bool CurrentSensorOnline;

  class CANTimer {       
    public:       
      unsigned long ReceivedMillis;      
      unsigned long previousMillis;
      unsigned long Interval;
      unsigned long Timeout;
      bool Online;
      float Frequentie;
  };
  class TaskTimer {       
    public:       
      unsigned long StartMillis;      
      unsigned long StopMillis;
      unsigned long MaxMillis;
      unsigned long MinMillis = 100000000;
      unsigned long Duration;
  };

  CANTimer CANTimer_321;
  CANTimer CANTimer_322;
  CANTimer CANTimer_323;
  CANTimer CANTimer_324;
  CANTimer CANTimer_351;
  CANTimer CANTimer_355;
  CANTimer CANTimer_356;
  CANTimer CANTimer_35A;
  CANTimer CANTimer_373;
  CANTimer CANTimer_372;
  CANTimer CANTimer_278;
  CANTimer CANTimer_28B;
  CANTimer CANTimer_298;
  CANTimer CANTimer_734;
  CANTimer CANTimer_735;
  CANTimer CANTimer_108;
  CANTimer CANTimer_109;
  CANTimer CANTimer_110;
  CANTimer CANTimer_521;
  CANTimer CANTimer_522;
  CANTimer CANTimer_523;
  CANTimer CANTimer_524;
  CANTimer CANTimer_780;
  CANTimer CANTimer_781;
  CANTimer CANTimer_790;
  CANTimer CANTimer_3B4;

  TaskTimer TimerMsgs100ms;
  TaskTimer Timercheckforinput;
  TaskTimer TimerInputs;
  TaskTimer TimerADC_Read;
  TaskTimer TimerDebug;
  TaskTimer TimerAC_Charger;
  TaskTimer TimerNextionUpdate;
  TaskTimer TimerNextionListen;   
// #endif


