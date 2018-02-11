void readATM() {
  
  //Pressure/Alt/Temp
  pascals = baro.getPressure();
  altm = baro.getAltitude();
  tempC = baro.getTemperature();
  delay(10);
  

}
