#define DeviceType_VCU
// #define DeviceType_Fuse      //dash module
// #define DeviceType_Fuse2     //schakel module
// #define DeviceType_Logger
// #define DeviceType_CurrentSensor
// #define DeviceType_BMW_BMS
// #define DeviceType_GSM

#ifdef DeviceType_VCU
  //digitale ingangen
  const int IN1 = 15; // input 1 - high active
  const int IN2 = 14; // input 2- high active
  const int IN3 = 21; // input 1 - high active
  const int IN4 = 22; // input 2- high active
  const int IN5 = 25; // input 2- high active
  const int IN6 = 26; // input 2- high active

  //digitale uitgangen
  const int OUT1 = 13;    // output 1 - high active
  // const int StatusLED = 12;// output 6 - high active
  const int ledPin =  12;// the number of the LED pin
  int SwitchCase = 0;

  //pinnen voor analoog meting
  const int ADC1_IN = 32;
  const int ADC2_IN = 33;
  const int ADC3_IN = 34;
  const int ADC4_IN = 35;
  const int ADC1_Current = 36;
  const int ADC1_VPower = 39;

  //serial 2 pinnen
  #define RXD2 4
  #define TXD2 2

  //deepsleep
  // #define deepsleep
#endif

#ifdef DeviceType_Fuse
  //digitale ingangen
  const int IN1 = 25; // input 1 - high active
  const int IN2 = 33; // input 2- high active
  const int IN3 = 32; // input 1 - high active
  const int IN4 = 35; // input 2- high active
  const int IN5 = 34; // input 2- high active
  const int IN6 = 39; // input 2- high active

  //digitale uitgangen
  const int OUT1 = 16;    // output 1 - high active
  const int OUT2 = 17;    // output 2 - high active
  const int OUT3 = 18;    // output 3 - high active
  const int OUT4 = 19;    // output 4 - high active
  const int OUT5 = 23;    // output 5 - high active
  const int OUT6 = 2;     // output 6 - high active
  const int ledPin =  26;// the number of the LED pin
  int SwitchCase = 0;

  //pinnen voor analoog meting
  const int S0 = 12;
  const int S1 = 13;
  const int S2 = 14;
  const int ADC_IN = 39;
  // setting PWM properties
  const int freq = 5000;
  const int resolution = 8;
  const int OUT1_Channel = 0;    // output 4 - high active
  const int OUT4_Channel = 1;    // output 4 - high active
  const int OUT5_Channel = 2;    // output 5 - high active
  const int OUT6_Channel = 3;     // output 6 - high active

  const int WIT = 0; 
  const int ROOD = 1;
  const int GROEN = 2;
  const int BLAUW = 3;
  const int ORANJE = 4;
  const int PAARS = 5;
  const int GEEL = 6;
  const int OFF = 7; 
#endif

#ifdef DeviceType_Fuse2
  //digitale ingangen
  const int IN1 = 25; // input 1 - high active
  const int IN2 = 33; // input 2- high active
  const int IN3 = 32; // input 1 - high active
  const int IN4 = 35; // input 2- high active
  const int IN5 = 34; // input 2- high active
  const int IN6 = 39; // input 2- high active

  //digitale uitgangen
  const int OUT1 = 16;    // output 1 - high active
  const int OUT2 = 17;    // output 2 - high active
  const int OUT3 = 18;    // output 3 - high active
  const int OUT4 = 19;    // output 4 - high active
  const int OUT5 = 23;    // output 5 - high active
  const int OUT6 = 2;     // output 6 - high active
  const int ledPin =  26;// the number of the LED pin
  int SwitchCase = 0;

  //pinnen voor analoog meting
  const int S0 = 12;
  const int S1 = 13;
  const int S2 = 14;
  const int ADC_IN = 39;

#endif

#ifdef DeviceType_Logger
  // Define CS pin for the SD card module
  #define SD_CS 5
  const int ledPin =  25;// the number of the LED pin
#endif

#ifdef DeviceType_CurrentSensor
  const int ledPin =  23;// the number of the LED pin
  const int freq = 10000;
  const int resolution = 12;
  const int PWM1_Channel = 0;    
  const int PWM2_Channel = 1;    
  const int PWM1 = 17;    
  const int PWM2 = 16;    
#endif 

#ifdef DeviceType_BMW_BMS
  const int ledPin =  25;// the number of the LED pin
  const int OUT1 = 13;    // output 1 - high active
#endif

#ifdef DeviceType_GSM
  const int ledPin =  12;// the number of the LED pin
  #define SerialAT Serial1
  #define SerialGPS Serial2
  #define UART_BAUD   115200
  #define PIN_TX      25//27
  #define PIN_RX      26
  #define PWR_PIN     33//4 
  #define BAT_ADC     35
  #define POWER_PIN   22//25
  #define IND_PIN     36
  #define GPS_RX_PIN  15

  #define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
  #define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */
#endif

int ledState = LOW;              
unsigned long previousMillis = 0;   
long intervalON;   
long intervalOFF;  
int LEDPettern;
#define LED_OFF 0
#define LED_OK 1
#define LED_LOGGING 2
#define LED_ERROR 3
#define LED_ON 4
#define LED_SLEEP 5