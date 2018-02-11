void writeSD(String dataString){
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
}

String mkdata(){
  String data = 
  //Times
  String(gpstime) + "," + 
  String(gpsdate) + "," + 
  String(millis()) + "," + 
  //IMU Data
  String(eulerx,4) + "," + 
  String(eulery,4) + "," +
  String(eulerz,4) + "," +
  //GPS
  String(latit,6) + "," + 
  String(longit,6) + "," + 
  String(alt,6) + "," + 
  String(course,2) + "," + 
  String(speed,2) + "," + 
  String(numsats) + "," + 
  String(velDiff,3) + "," + 
  //Temperature
  String(temp,4) + "," +
  String(humidity, 4) + "," +
  //Windspeed
  String(windspeed, 4) + "," +
  String(atmDiff, 4) + "," +
  String(solarvalue, 4) + "," +
  //Pressure data
  String(pascals/101325.01, 2) + "," +
  String(altm, 2) + "," +
  String(tempC, 2);
  
  return data;
}

