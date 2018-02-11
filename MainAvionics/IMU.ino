boolean initSensors() {
  if(!bno.begin()){ return false; }
  bno.setExtCrystalUse(true);
  return true;
}

void readIMU(){
  sensors_event_t event; 
  bno.getEvent(&event);

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
  eulerx = euler.x();
  eulery = euler.y();
  eulerz = euler.z();

  delay(10);
}

