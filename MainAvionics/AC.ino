void checkAltitudeTrigger(){
  if (alt > 7200 && !servoOpened){
    servo.write(0);
    delay(6000);
    servo.write(90);
    servoOpened = true;
    String dataString = "Opening Alt: " + String(alt) + "Time: " + String(gpstime);
    Serial.println("hi, open");
    writeSD(dataString);
  }

//  if(alt > 30 && !servoClosed){
//    servo.write(180);
//    delay(6000);  
//    servo.write(90);
//    servoClosed = true;
//    String dataString = "Closing Alt: " + String(alt) + "Time: " + String(gpstime);
//    Serial.println("hi, closed");
//    writeSD(dataString);
//  }
}
