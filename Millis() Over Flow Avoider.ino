bool checkTime(unsigned long *prevMillis, unsigned int range) {
  /*
   * 50 gun sonra millis() sifilaniyor. Bundan kacinmak icin.
   */
  unsigned long currentMillis = millis();

  if((unsigned long)(currentMillis - *prevMillis) > range) {
    return true;
  } else if(*prevMillis > currentMillis) {
    *prevMillis = millis();
    return false;
  } else return false;
}
