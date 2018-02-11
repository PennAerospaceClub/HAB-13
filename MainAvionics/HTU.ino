void readHTU() {
  htu.begin();
  
  //Temp/Hum
  temp = htu.readTemperature()*1.8 + 32;
  humidity = htu.readHumidity();
  delay(10);
}

