#include <esp32_can.h>
#include <Metro.h>
#include "EasyNextionLibrary.h" // Include EasyNextionLibrary

//serial 1 pinnen
#define RXD2 44
#define TXD2 43
const int ledPin = 21;// the number of the LED pin

Metro timer_Nextion = Metro(300);
Metro timer_NextionGraph = Metro(100);
Metro timer_Debug = Metro(1000);


EasyNex myNex(Serial1);   // Create an object of EasyNex class with the name < myNex >

CAN_FRAME tx_frame;
CAN_FRAME rx1_Frame;

 //current sensor
class CurrentSensor {       
  public: 
    signed long Miliamps;     //mA
    signed long Voltage1;     //mV
    signed long Voltage2;
    signed long Voltage3;
    signed long PowerW;
    signed long Temperature;
    signed long Current_Counter;
    signed long Energy_Counter;
  };
  
class CANTimer {       
    public:       
      unsigned long ReceivedMillis;      
      unsigned long previousMillis;
      unsigned long Interval;
      unsigned long Timeout = 500;
      bool Online;
      float Frequentie;
  };

CurrentSensor CurrentSensor1;
CurrentSensor CurrentSensor2;

  CANTimer CANTimer_521;
  CANTimer CANTimer_522;
  CANTimer CANTimer_523;
  CANTimer CANTimer_524;
  CANTimer CANTimer_525;
  CANTimer CANTimer_526;
  CANTimer CANTimer_527;
  CANTimer CANTimer_528;

  CANTimer CANTimer_531;
  CANTimer CANTimer_532;
  CANTimer CANTimer_533;
  CANTimer CANTimer_534;
  CANTimer CANTimer_535;
  CANTimer CANTimer_536;
  CANTimer CANTimer_537;
  CANTimer CANTimer_538;

  CANTimer CANTimer_351;
  CANTimer CANTimer_355;
  CANTimer CANTimer_356;
  CANTimer CANTimer_35A;
  CANTimer CANTimer_373;
  CANTimer CANTimer_372;

  CANTimer CANTimer_298;
  CANTimer CANTimer_735;


float ADC_ValueVCU_Voltage;
float FiltertVCU_Voltage;

bool VCU_Aan;
int VCU_State = 0;

bool ContactAan;
bool StartPuls;
bool DeurContact;
bool RemContact;
bool Inverter_Enable;
bool Dash_licht_Button;
bool Cruise;
bool Waterpomp;
bool Oliepomp;

float BatteryResistanceValue; //ohm
float SOCCorrectedFilt;
int SOCCorrected;

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

//charger
int MaxDCvoltage;
int MaxDCcurrent;
int DCvoltage;
int DCcurrent;
int Charging;
signed int ChargerTemp;
int SetDCcurrent = 30;
 bool DriveBlockCharging;

//DC-DC converter
uint16_t setVolts = 398, actVolts , termAmps;
int16_t actAmps;
uint8_t currentRamp;
bool clearToStart;
bool ChargePlugDetected;
static uint8_t chgStatus , evseDuty;
static float dcBusV , tempMax, temp_1 , temp_2 , temp_3 , temp_4 , temp_5 , ACVolts , DCAmps , ACAmps;
static float LV_Volts , LV_Amps;
static float Voltspnt = 398;

//BMS
float BMS_Power;
int BMS_SOC;
long BMS_Voltage;
long BMS_Current;
int BMS_Temperature;
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

int Speed;

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

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(500000);
  Serial.println("Initializing ...");
  myNex.begin(250000); // Begin the object with a baud rate of 115200
  Serial1.begin(250000, SERIAL_8N1, RXD2, TXD2);
  CAN0.setCANPins(GPIO_NUM_37, GPIO_NUM_38);  //RX, TX
  CAN0.begin(500000);
  Serial.println("Ready ...!");
  LEDPettern = LED_OK; 

  CAN0.watchFor(0x521); //IVT_Msg_Result_I
  CAN0.watchFor(0x522); //IVT_Msg_Result_U1
  CAN0.watchFor(0x523); //IVT_Msg_Result_U2
  CAN0.watchFor(0x524); //IVT_Msg_Result_U3
  CAN0.watchFor(0x525); //IVT_Msg_Result_T
  CAN0.watchFor(0x526); //IVT_Msg_Result_W
  CAN0.watchFor(0x527); //IVT_Msg_Result_As
  CAN0.watchFor(0x528); //IVT_Msg_Result_Wh

  // CAN0.watchFor(0x531); //IVT_Msg_Result_I
  // CAN0.watchFor(0x532); //IVT_Msg_Result_U1
  // CAN0.watchFor(0x533); //IVT_Msg_Result_U2
  // CAN0.watchFor(0x534); //IVT_Msg_Result_U3
  // CAN0.watchFor(0x535); //IVT_Msg_Result_T
  // CAN0.watchFor(0x536); //IVT_Msg_Result_W
  // CAN0.watchFor(0x537); //IVT_Msg_Result_As
  // CAN0.watchFor(0x538); //IVT_Msg_Result_Wh

  CAN0.watchFor(0x780); //VCU status

  CAN0.watchFor(0x351); //setup a special filter
  CAN0.watchFor(0x355); //setup a special filter
  CAN0.watchFor(0x356); //setup a special filter
  CAN0.watchFor(0x35A); //setup a special filter
  CAN0.watchFor(0x373); //setup a special filter
  CAN0.watchFor(0x372); //setup a special filter

  CAN0.watchFor(0x791); //VCU status

  //inverter
  CAN0.watchFor(0x287); //setup a special filter
  CAN0.watchFor(0x289); //setup a special filter
  CAN0.watchFor(0x299); //setup a special filter
  CAN0.watchFor(0x732); //setup a special filter
  CAN0.watchFor(0x733); //setup a special filter

  //dcdc
  CAN0.watchFor(0x377); //DC-DC converter status
  CAN0.watchFor(0x389); //DC-DC converter status
  CAN0.watchFor(0x38A); //DC-DC converter status

  CAN0.watchFor(); //then let everything else through anyway
  CAN0.setCallback(0, canRX_521); //callback current sensor stroom
  CAN0.setCallback(1, canRX_522); //callback current sensor v1
  CAN0.setCallback(2, canRX_523); //callback current sensor v2
  CAN0.setCallback(3, canRX_524); //callback current sensor v3
  CAN0.setCallback(4, canRX_525); //IVT_Msg_Result_T
  CAN0.setCallback(5, canRX_526); //IVT_Msg_Result_W
  CAN0.setCallback(6, canRX_527); //IVT_Msg_Result_As
  CAN0.setCallback(7, canRX_528); //IVT_Msg_Result_Wh

  // CAN0.setCallback(8, canRX_531); //callback current sensor stroom
  // CAN0.setCallback(9, canRX_532); //callback current sensor v1
  // CAN0.setCallback(10, canRX_533); //callback current sensor v2
  // CAN0.setCallback(11, canRX_534); //callback current sensor v3
  // CAN0.setCallback(12, canRX_535); //IVT_Msg_Result_T
  // CAN0.setCallback(13, canRX_536); //IVT_Msg_Result_W
  // CAN0.setCallback(14, canRX_537); //IVT_Msg_Result_As
  // CAN0.setCallback(15, canRX_538); //IVT_Msg_Result_Wh

  CAN0.setCallback(8, canRX_780); //VCU status

  CAN0.setCallback(9, canRX_351); //callback BMS Limits
  CAN0.setCallback(10, canRX_355); //callback BMS SOC
  CAN0.setCallback(11, canRX_356); //callback BMS Status
  CAN0.setCallback(12, canRX_35A); //callback BMS Warnings
  CAN0.setCallback(13, canRX_373); //callback BMS Low and High
  CAN0.setCallback(14, canRX_372); //callback BMS Info

  CAN0.setCallback(15, canRX_791); //fuse 2 status

  CAN0.setCallback(16, canRX_278); //callback Inverter Set function and torque
  CAN0.setCallback(17, canRX_288); //callback Inverter RPM Battery and Torque
  CAN0.setCallback(18, canRX_298); //callback Inverter Temps
  CAN0.setCallback(19, canRX_75A); //callback Inverter current
  CAN0.setCallback(20, canRX_75B); //callback Motor Temps

  CAN0.setCallback(21, canRX_377);  //DC-DC converter status
  CAN0.setCallback(22, canRX_389);  //DC-DC converter status
  CAN0.setCallback(23, canRX_38A);  //DC-DC converter status

}

void loop() {
  NextionUpdate();
  myNex.NextionListen();
  easyNexReadCustomCommand();
  Debug();
  LEDBlink();
  CANCheck();
  
}
