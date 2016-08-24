/* ==================================================================================
 *  RemainingTimeClock
 *
 *  Simple client that measures time to go to sleep or time to wake up respectively
 *
 *  August 2016
 *  By Pavol Cesek
 *  ================================================================================== */

#include <Time.h>
#include <TimeAlarms.h>

#define DEFAUL_LOOP_DEALY 0
#define DEFAUL_USER_INPUT_TIMEOUT 20000
#define REPEAT_TIMES 50

#define debug 0


/* ========================================================== Global variables ========================================================== */
const int sensorPin = 0; //The analog sensor is connected to analog pin 0 of the arduino

//ABCDEFG,dp
const int numeral[10] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B00111110, //6
  B11100000, //7
  B11111110, //8
  B11100110, //9
};

//pins for decimal point and each segment
//dp, G, F, E, D, C, B, A
const int segmentPins[] = { 4, 7, 8, 6, 5, 3, 2, 9};

//digits 1, 2, 3, 4
const int numberofDigits = 4;
const int digitPins[numberofDigits] = { 10, 11, 12, 13}; 

byte timeCorreclySet;
byte cur_hour;
byte cur_minute;
byte cur_second;


/* ========================================================== Program setup ========================================================== */
void setup(){

  Serial.begin(19200);
  delay(500);
  
  Serial.println(F("\n\n\n====   Setup procedure started    ====\n"));

  initTimer();
  Alarm.timerRepeat(0, 0, 1, doSendDataJob);
  
  for (int i = 0; i < 8; i++)
    pinMode(segmentPins[i], OUTPUT); //set segment and DP pins to output

  //sets the digit pins as outputs
  for (int i = 0; i < numberofDigits; i++)
    pinMode(digitPins[i], OUTPUT);
    
   Serial.println(F("\n====   Setup procedure finished    ====\n\n\n"));
}
int numberToDisplay;


/* ========================================================== Program main loop ========================================================== */
void loop()
{ 
  showHour(cur_hour);
  showMinute(cur_minute);
  
  Alarm.delay(DEFAUL_LOOP_DEALY);
}

/* ========================================================== Callback Functions ========================================================== */

void doSendDataJob() {
  if (debug) Serial.println(F("\n\n == doSendDataJob callback function started ==\n"));
  if (debug) logTime();
  
  cur_hour = getHour();
  cur_minute = getMinute();
  cur_second = getSecond();


  if (debug) Serial.println(F("\n == doSendDataJob callback function finished ==\n\n"));
}

/* ========================================================== Functions ========================================================== */

void showHour(int number) {
  showDigit(number % 10, 1);
  showDigit((number / 10) % 10, 0);
}

void showMinute(int number) {
  showDigit(number % 10, 3);
  showDigit((number / 10) % 10, 2);
}

void showNumber (int number)
{
  if (number == 0)
    showDigit (0, numberofDigits - 1); //display 0 in the rightmost digit
  else
  {
    for (int digit = numberofDigits - 1; digit >= 0; digit--)
    {
      if (number > 0)
      {
        showDigit(number % 10, digit);
        number = number / 10;
      }
    }
  }
}

//Displays given number on a 7-segment display at the given digit position
void showDigit (int number, int digit)
{
  digitalWrite(digitPins[digit], HIGH);
  for (int segment = 0; segment < 8; segment++)
  {
    boolean isBitSet = bitRead(numeral[number], segment);

    isBitSet = ! isBitSet; //remove this line if common cathode display
    digitalWrite(segmentPins[segment], isBitSet);
  }
  delay(5);
  digitalWrite(digitPins[digit], LOW);
}

