/*
 * Main Flight Code for the Penn Aerospace Club's
 * High Altitude Balloon Project
 * 
 * Integrations:
 * SD Card, 9DOF IMU, Temperature, Humidity,
 * GPS, Geiger Counter Logging, Altitude Control,
 * Comprehensive Sanity System, Anemometer
 * 
*/
//======================================
// Libraries ===========================
#include <Wire.h>               //Temp/Humidity/IMU/OLED
#include <SPI.h>                //SD
#include <SD.h>                 //SD
#include <TinyGPS++.h>          //GPS
#include <Servo.h>
#include <Adafruit_SSD1306.h>   //OLED
#include <Adafruit_HTU21DF.h>   //Temp/Humidity
#include <Adafruit_Sensor.h>    //IMU
#include <Adafruit_BNO055.h> 
#include <Adafruit_MPL3115A2.h>  //barometer
//#include <Adafruit_SI1145.h> //UV
// #include <Adafruit_LSM303_U.h>  //IMU
// #include <Adafruit_L3GD20_U.h>  //IMU
// #include <Adafruit_9DOF.h>      //IMU


//=====================================
//IMU =================================
//Adafruit_9DOF                   dof   = Adafruit_9DOF();
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();

//UV =================================
//Adafruit_SI1145 uv = Adafruit_SI1145();
//float vis;
//float ir;
//float uvx;

//pressure ============================
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

//IMU variables =========================
float eulerx;
float eulery;
float eulerz;

//pressure variables ====================
float pascals;
float altm;
float tempC;

//=======================================
// GPS Variables ========================
TinyGPSPlus gps;
double latit;   //degrees
double longit;  //degrees
double alt;     //meters
double alto;
double velDiff;
double vel[] = {0,0,0,0,0}; //meters 
long gpstime;   //HHMMSSCC
long gpsdate;   //DDMMYY
int numsats;
double course;  //degrees 
double speed;   //mph

//AC
Servo servo;
boolean servoOpened = false;
boolean servoClosed = false;

//OLED =====================================
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//SD Card ==================================
#define chipSelect 53

//Temp/Humidity ============================
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
float temp;                 //farenehit
float humidity;             //percentage

//Anemometer ===============================
#define ANEM A0
#define DIFF A1
#define SOLAR A2

double atmDiff;
float windspeed;            //mph
float solarvalue;

//Sanity ===================================
boolean sane = false;
#define BUTTON 9
//==========================================

void setup() {
  //Serial
  Serial.begin(115200); //Computer
  Serial1.begin(9600); //GPS

  servo.attach(11); //PIN 11
  servo.write(90);

  pinMode(DIFF, INPUT);
  pinMode(ANEM, INPUT);
  pinMode(SOLAR, INPUT);

  //Sanity
  pinMode(BUTTON,INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Hello");
  display.display();
  delay(500);
  
}

//=======================================
void loop() {
  while(!sane){ sanity(); }
  
  unsigned long nextloop = millis() + 1000;

  checkAltitudeTrigger();
  
  readIMU();
  readGPS();
  readATM();
  readHTU();
  anemometer();
  solarvalue = analogRead(SOLAR)*5/1023.0;

  //Data Logging
  String data = mkdata();
  writeSD(data);
  Serial.println(data);
  Serial.flush();

  while(millis() < nextloop);
}

void anemometer(){
  //Takes an analog input from 0.4V and 2V and maps it to 0m/s to 32m/s then to mph
  windspeed = ((analogRead(ANEM) - 82)/328.0 * 32.4)*2.23694;
}

void differential() {
  atmDiff = 0.00986923 * (analogRead(DIFF) * 200.0 * 4.6) / (9.0 * 1023.0) - 4.44;
}


