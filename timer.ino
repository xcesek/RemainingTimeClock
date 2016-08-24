/* ==================================================================================
 *  iSarfia - Weather station project
 *
 *  Timer helper funcions
 *
 *  ================================================================================== */
 
 // todo: get time from web service
 
void initTimer() {
  int time;
  
  askUserForDateTime(); 
  logTime();
    
  Serial.println(F(" - timer sensor initialized"));
}

void askUserForDateTime() {
  int y, m, d, hour, min, sec;
  int time; 
  String readString;
  
  Serial.println(F("    Please enter current date and time: (hh mm dd mm yy)")); 
  time = millis();
  
  
  while (!Serial.available()) { // wait
    delay(1000);
    
    if (millis() - time > DEFAUL_USER_INPUT_TIMEOUT) {  // timeout, set defaul time
     setTime(7, 1, 12,    10, 8, 22);
     if (debug) {
       Serial.println(F("    Timeout elapsed. Time set automatically!\n"));  
     }
     timeCorreclySet = 0;
     
     return;
   } 
    
  }
    
  while (Serial.available()) {  // read to str
    char c = Serial.read();  
    readString += c; 
    delay(4);
  }

  hour = 10 * (readString[0]  - '0') + (readString[1]  - '0');
  min = 10 * (readString[3]  - '0') + (readString[4]  - '0');
  sec = 0;
  
  d = 10 * (readString[6]  - '0') + (readString[7]  - '0');
  m = 10 * (readString[9]  - '0') + (readString[10]  - '0');
  y = 10 * (readString[12]  - '0') + (readString[13]  - '0');
  
  if (debug) {
    Serial.print("    Read user input: "); Serial.println(readString);  
  }
   
  setTime(hour, min, sec, d, m, y);
  timeCorreclySet = 1;
}

void logTime() {
  Serial.print(F("    Current time is: ")); 
  Serial.print(hour()); Serial.print(F(":")); 
  Serial.print(minute()); Serial.print(F(":")); 
  Serial.print(second()); 
  Serial.print(" ("); 
  Serial.print(year()); Serial.print(F("/"));
  Serial.print(month()); Serial.print(F("/")) ;
  Serial.print(day()); 
  Serial.println(")");
}

void digitalClockDisplay() {
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits) {
  Serial.print(F(":"));
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

int getHour() {
  return hour();
}

int getMinute() {
  return minute();
}

int getSecond() {
  return second();
}
  




