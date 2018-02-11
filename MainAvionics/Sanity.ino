
void sanity(){
  //========================================
  //Sanity Declarations ====================
  static boolean sd = false;  
  static boolean imu = false;
  static boolean temphum = false;
  static boolean gps_attached = false;
  static boolean pressure = false;
  //static boolean uv_sane = false;
  
  //==========================================
  //Sanity Checks ============================
  
  if (!sd){ if (SD.begin(chipSelect)) { sd = true; } }
  if (!imu){ if(initSensors()){ imu = true; } }
  if (!temphum){ if (htu.begin()) { temphum = true; } }
  if (!pressure) { if (baro.begin()) { pressure = true; } }
  //if (!uv_sane) { if(uv.begin()) { uv_sane = true; }}

  //GPS
  if(Serial1.available()){ gps_attached = true; }
  
  //========================================
  //Data Verification ======================
  if(gps_attached){ readGPS(); }
  if(imu){ readIMU(); }
  if(pressure){ readATM(); }
  if(temphum) { readHTU(); }
  //if(uv_sane) { readUV(); }
  anemometer();
  differential();
  solarvalue = analogRead(SOLAR)*5/1023.0;
  
 //==========================================
  //Display Information ======================
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  
  if(!sd) { display.print("SD- "); } else{ display.print("SD+ "); }
  if(!imu){ display.print("IMU- "); } else{ display.print("IMU+ "); }
  if(!temphum){ display.print("HT- "); } else{ display.print("HT+ "); }
  if(!pressure){ display.print("BA- "); } else{ display.print("BA+ "); }
//  if(!uv_sane){ display.println("UV- "); } else{ display.println("UV+ "); }

  if(gps_attached){
    display.println("NS" + String(numsats));

    display.print("Alt:" + String(alt,1));
    display.println(" Altm:" + String(altm,1));
    display.println("Lat: " + String(latit,6));
    display.println("Long: " + String(longit,6));
    
  } else { display.println("GPS-"); }

  if(imu){
    display.print(String(eulerx,2) + ",");
    display.print(String(eulery,2) + ",");
    display.println(String(eulerz,2));
  }

  if(pressure) {
    display.print(String(pascals/101325.01, 2) + " ");
    display.print(String(atmDiff, 2) + " ");
    display.print(String(solarvalue, 2) + " ");
    display.println(String(windspeed, 2));
  }

  if(temphum) {
    display.print(String(temp) + "*F ");
    display.print(String(humidity) + "%");
    //display.println(); 
  }

//  if(uv_sane) {
//    display.print(String(vis, 2));
//  }

  //==========================================
  //Ending Sanity ============================
  if(sd && imu && gps_attached && pressure && temphum && digitalRead(BUTTON) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Button Pressed\nEnding Sanity\n\nHave a Great\nFlight!");
    display.display();
    sane = true;
    delay(3000);
    display.clearDisplay();
  }
  
  display.display();

  if (sd) {
      //Data Logging
  String data = mkdata();
  writeSD("IN_SANITY_CHECKS," + data); 
  }
}
  //==========================================


