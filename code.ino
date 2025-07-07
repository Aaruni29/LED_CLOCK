#include <virtuabotixRTC.h>               // Library for real-time clock
#include <Adafruit_PWMServoDriver.h>      // Library to control servo motors

Adafruit_PWMServoDriver pwmH = Adafruit_PWMServoDriver(0x40);    // Hour servos controller
Adafruit_PWMServoDriver pwmM = Adafruit_PWMServoDriver(0x41);    // Minute servos controller (with A0 jumper)

int servoFrequency = 50;      // Servo working frequency

int segmentHOn[14] = {375,375,375,375,375,375,375,375,375,375,375,375,375,375};   // ON positions for hour servos
int segmentMOn[14] = {382,395,378,315,375,340,345,380,385,365,290,365,315,365};   // ON positions for minute servos
int segmentHOff[14] = {200,200,550,550,200,550,200,200,200,550,550,200,550,200};  // OFF positions for hour servos
int segmentMOff[14] = {200,200,550,440,200,480,200,200,200,550,450,200,430,200};  // OFF positions for minute servos

int digits[10][7] = {       // 7-segment layout for digits 0-9
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

virtuabotixRTC myRTC(6, 7, 8);    // RTC object using pins 6 (CLK), 7 (DAT), 8 (RST)

int hourTens = 0;        // To store tens digit of hours
int hourUnits = 0;       // To store units digit of hours
int minuteTens = 0;      // To store tens digit of minutes
int minuteUnits = 0;     // To store units digit of minutes

int prevHourTens = 8;        // Previous values for comparison
int prevHourUnits = 8;
int prevMinuteTens = 8;
int prevMinuteUnits = 8;

int midOffset = 100;         // Used to slightly move side segments for middle bar

void setup() 
{
  Serial.begin(9600);
  pwmH.begin();   // Start hour controller
  pwmM.begin();   // Start minute controller

  pwmH.setOscillatorFrequency(27000000);    // Set frequency for calibration
  pwmM.setOscillatorFrequency(27000000);

  pwmH.setPWMFreq(servoFrequency);          // Set frequency for servos
  pwmM.setPWMFreq(servoFrequency);

  // Set all segments to ON to display 88:88 at start
  for(int i = 0; i <= 13; i++)    
  {
    pwmH.setPWM(i, 0, segmentHOn[i]);
    delay(10);
    pwmM.setPWM(i, 0, segmentMOn[i]);
    delay(10);
  }

  delay(2000);  // Short pause
}

void loop()
{
  myRTC.updateTime();     // Get current time

  int temp = myRTC.hours;
  hourTens = temp / 10;   // Split hours into two digits
  hourUnits = temp % 10;

  temp = myRTC.minutes;
  minuteTens = temp / 10; // Split minutes into two digits
  minuteUnits = temp % 10;

  if(minuteUnits != prevMinuteUnits)    // If minute changed, update display
    updateDisplay();

  // Print current digits to serial monitor
  Serial.println(hourTens); 
  Serial.println(hourUnits);
  Serial.println(minuteTens); 
  Serial.println(minuteUnits); 
  Serial.println("");

  // Save current digits for next check
  prevHourTens = hourTens;
  prevHourUnits = hourUnits;
  prevMinuteTens = minuteTens;
  prevMinuteUnits = minuteUnits;

  delay(1000); // Wait for 1 second
}

void updateDisplay ()
{
  updateMid();  // Handle middle segments

  for (int i = 0; i <= 5; i++)
  {
    // Hour tens update
    if(digits[hourTens][i] == 1)
      pwmH.setPWM(i + 7, 0, segmentHOn[i + 7]);
    else
      pwmH.setPWM(i + 7, 0, segmentHOff[i + 7]);
    delay(10);

    // Hour units update
    if(digits[hourUnits][i] == 1)
      pwmH.setPWM(i, 0, segmentHOn[i]);
    else
      pwmH.setPWM(i, 0, segmentHOff[i]);
    delay(10);

    // Minute tens update
    if(digits[minuteTens][i] == 1)
      pwmM.setPWM(i + 7, 0, segmentMOn[i + 7]);
    else
      pwmM.setPWM(i + 7, 0, segmentMOff[i + 7]);
    delay(10);

    // Minute units update
    if(digits[minuteUnits][i] == 1)
      pwmM.setPWM(i, 0, segmentMOn[i]);
    else
      pwmM.setPWM(i, 0, segmentMOff[i]);
    delay(10);
  }
}

void updateMid()
{
  // Check if minute units middle bar changed
  if(digits[minuteUnits][6] != digits[prevMinuteUnits][6])
  {
    if(digits[prevMinuteUnits][1] == 1)
      pwmM.setPWM(1, 0, segmentMOn[1] - midOffset);
    if(digits[prevMinuteUnits][6] == 1)
      pwmM.setPWM(5, 0, segmentMOn[5] + midOffset);
  }

  delay(100);

  if(digits[minuteUnits][6] == 1)
    pwmM.setPWM(6, 0, segmentHOn[6]);
  else
    pwmM.setPWM(6, 0, segmentHOff[6]);

  // Minute tens middle bar change
  if(digits[minuteTens][6] != digits[prevMinuteTens][6])
  {
    if(digits[prevMinuteTens][1] == 1)
      pwmM.setPWM(8, 0, segmentMOn[8] - midOffset);
    if(digits[prevMinuteTens][6] == 1)
      pwmM.setPWM(12, 0, segmentMOn[12] + midOffset);
  }

  delay(100);

  if(digits[minuteTens][6] == 1)
    pwmM.setPWM(13, 0, segmentHOn[13]);
  else
    pwmM.setPWM(13, 0, segmentHOff[13]);

  // Hour units middle bar change
  if(digits[hourUnits][6] != digits[prevHourUnits][6])
  {
    if(digits[prevHourUnits][1] == 1)
      pwmH.setPWM(1, 0, segmentHOn[1] - midOffset);
    if(digits[prevHourUnits][6] == 1)
      pwmH.setPWM(5, 0, segmentHOn[5] + midOffset);
  }

  delay(100);

  if(digits[hourUnits][6] == 1)
    pwmH.setPWM(6, 0, segmentHOn[6]);
  else
    pwmH.setPWM(6, 0, segmentHOff[6]);

  // Hour tens middle bar change
  if(digits[hourTens][6] != digits[prevHourTens][6])
  {
    if(digits[prevHourTens][1] == 1)
      pwmH.setPWM(8, 0, segmentHOn[8] - midOffset);
    if(digits[prevHourTens][6] == 1)
      pwmH.setPWM(12, 0, segmentHOn[12] + midOffset);
  }

  delay(100);

  if(digits[hourTens][6] == 1)
    pwmH.setPWM(13, 0, segmentHOn[13]);
  else
    pwmH.setPWM(13, 0, segmentHOff[13]);
}
