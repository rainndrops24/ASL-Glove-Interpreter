/*
  
  flex pins : A0-A4
  accelerometer : A5-A6
  bluetooth : D4 & D5
  foil button : D3

*/

#include <SoftwareSerial.h>


SoftwareSerial mySerial(5, 4);

char temp = '0';

//accelerometer~~~~

//variable initializtion
int xpin = A5;
int xadc = 0;
int xmax = 0;
int xmin = 1023;

int ypin = A6;
int yadc = 0;
int ymax = 0;
int ymin = 1023;

//accelerometer^^^^^^^

//flex sensors~~~~

int FLEX_PIN1 = A4;
int flexADC1 = 0;
int sensorMin1 = 1023;
int sensorMax1 = 0;

int FLEX_PIN2 = A3;
int flexADC2 = 0;
int sensorMin2 = 1023;
int sensorMax2 = 0;

int FLEX_PIN3 = A2;
int flexADC3 = 0;
int sensorMin3 = 1023;
int sensorMax3 = 0;

int FLEX_PIN4 = A1;
int flexADC4 = 0;
int sensorMin4 = 1023;
int sensorMax4 = 0;

int FLEX_PIN5 = A0;
int flexADC5 = 0;
int sensorMin5 = 1023;
int sensorMax5 = 0;

//flex sensors ^^^^^^


void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect
  }
  Serial.println("initiallized");
  mySerial.println("initiallized");
  // callibrating the sensors for adaptivity with different bends
  while (millis() < 15000)
  {
    if (digitalRead(7) == HIGH)
    {
      //stores flex sensor reading
      float flexADC1 = analogRead(FLEX_PIN1);
      float flexADC2 = analogRead(FLEX_PIN2);
      float flexADC3 = analogRead(FLEX_PIN3);
      float flexADC4 = analogRead(FLEX_PIN4);
      float flexADC5 = analogRead(FLEX_PIN5);

      //checks boundaries
      if (flexADC1 < sensorMin1)
      {
        sensorMin1 = flexADC1;
      }
      if (flexADC1 > sensorMax1)
      {
        sensorMax1 = flexADC1;
      }

      if (flexADC2 < sensorMin2)
      {
        sensorMin2 = flexADC2;
        
      }
      if (flexADC2 > sensorMax2)
      {
        sensorMax2 = flexADC2;
        //Serial.print("Min : ");
        //Serial.println(sensorMin2);
      }

      if (flexADC3 < sensorMin3)
      {
        sensorMin3 = flexADC3;
        
      }
      if (flexADC3 > sensorMax3)
      {
        sensorMax3 = flexADC3;
      }

      if (flexADC5 < sensorMin5)
      {
        sensorMin5 = flexADC5;
      }
      if (flexADC5 > sensorMax5)
      {
        sensorMax5 = flexADC5;
      }

      if (flexADC4 < sensorMin4)
      {
        sensorMin4 = flexADC4;
      }
      if (flexADC4 > sensorMax4)
      {
        sensorMax4 = flexADC4;
      }
    }
    //Serial.println("calibrating");
  }
  Serial.print(sensorMin1);
  Serial.print(" ");
  Serial.println(sensorMax1);
  Serial.print(sensorMin2);
  Serial.print(" ");
  Serial.println(sensorMax2);
  Serial.print(sensorMin3);
  Serial.print(" ");
  Serial.println(sensorMax3);
  Serial.print(sensorMin4);
  Serial.print(" ");
  Serial.println(sensorMax4);
  Serial.print(sensorMin5);
  Serial.print(" ");
  Serial.println(sensorMax5);
  Serial.println("reading");
  mySerial.println("reading");
}


void printfun(char cp) //to avoid printing repeating symbols
{
  if (cp != temp)
  {
    mySerial.print(cp);
    Serial.print(cp);
    temp = cp;
  }
}

void loop()
{
  
  // stores sensor value
  float flexADC1 = analogRead(FLEX_PIN1);
  float flexADC2 = analogRead(FLEX_PIN2);
  float flexADC3 = analogRead(FLEX_PIN3);
  float flexADC4 = analogRead(FLEX_PIN4);
  float flexADC5 = analogRead(FLEX_PIN5);

  //checks boundaries
  flexADC1 = constrain(flexADC1, sensorMin1, sensorMax1);
  flexADC2 = constrain(flexADC2, sensorMin2, sensorMax2);
  flexADC3 = constrain(flexADC3, sensorMin3, sensorMax3);
  flexADC4 = constrain(flexADC4, sensorMin4, sensorMax4);
  flexADC5 = constrain(flexADC5, sensorMin5, sensorMax5);

  //stores angle
  float angle1 = map(flexADC1, sensorMin1, sensorMax1, 0, 90);
  float angle2 = map(flexADC2, sensorMin2, sensorMax2, 0, 90);
  float angle3 = map(flexADC3, sensorMin3, sensorMax3, 0, 90);
  float angle4 = map(flexADC4, sensorMin4, sensorMax4, 0, 90);
  float angle5 = map(flexADC5, sensorMin5, sensorMax5, 0, 90);

  
  xadc = analogRead(xpin);
  yadc = analogRead(ypin);

  Serial.print(angle1);
  Serial.print(" ");
  Serial.print(angle2);
  Serial.print(" ");
  Serial.print(angle3);
  Serial.print(" ");
  Serial.print(angle4);
  Serial.print(" ");
  Serial.println(angle5);

  // checks readings and converts to letter
  if (((angle1 >= 67) && (angle1 <= 90)) && ((angle2 >= 49) && (angle2 <= 92)) && ((angle3 >= 59) && (angle3 <= 92)) && ((angle4 >= 60) && (angle4 <= 95)) && ((angle5 >= 0) && (angle5 <= 55)))
    printfun('A');
  if (((angle1 >= 0) && (angle1 <= 15)) && ((angle2 >= 0) && (angle2 <= 15)) && ((angle3 >= 0) && (angle3 <= 15)) && ((angle4 >= 0) && (angle4 <= 5)) && ((angle5 >= 30) && (angle5 <= 80)))
    printfun('B');
  if (((angle1 >= 0) && (angle1 <= 40)) && ((angle2 >= 17) && (angle2 <= 50)) && ((angle3 >= 35) && (angle3 <= 70)) && ((angle4 >= 28) && (angle4 <= 60)) && ((angle5 >= 8) && (angle5 <= 39)))
    printfun('C');
  if (((angle1 >= 10) && (angle1 <= 45)) && ((angle2 >= 26) && (angle2 <= 60)) && ((angle3 >= 39) && (angle3 <= 72)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 15) && (angle5 <= 52))) //&& !(((xadc >= 412) && (xadc <= 418)) && ((yadc >= 340) && (yadc <= 360))))
    printfun('D');
  if (((angle1 >= 39) && (angle1 <= 70)) && ((angle2 >= 40) && (angle2 <= 75)) && ((angle3 >= 58) && (angle3 <= 90)) && ((angle4 >= 49) && (angle4 <= 88)) && ((angle5 >= 48) && (angle5 <= 90)))
    printfun('E');
  if (((angle1 >= 0) && (angle1 <= 10)) && ((angle2 >= 0) && (angle2 <= 10)) && ((angle3 >= 0) && (angle3 <= 10)) && ((angle4 >= 15) && (angle4 <= 45)) && ((angle5 >= 34) && (angle5 <= 65)))
    printfun('F');
  if (((angle1 >= 75) && (angle1 <= 90)) && ((angle2 >= 75) && (angle2 <= 90)) && ((angle3 >= 65) && (angle3 <= 90)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 0) && (angle5 <= 30)) && (((xadc >= 400) && (xadc <= 420)) && ((yadc >= 340) && (yadc <= 360))))
    printfun('G');
  if (((angle1 >= 70) && (angle1 <= 85)) && ((angle2 >= 75) && (angle2 <= 90)) && ((angle3 >= 0) && (angle3 <= 10)) && ((angle4 >= 0) && (angle4 <= 10)) && ((angle5 >= 50) && (angle5 <= 65)) && !(((xadc >= 410) && (xadc <= 420)) && ((yadc >= 368) && (yadc <= 380))))
    printfun('H');
  if (((angle1 >= 0) && (angle1 <= 10)) && ((angle2 >= 50) && (angle2 <= 70)) && ((angle3 >= 50) && (angle3 <= 70)) && ((angle4 >= 50) && (angle4 <= 70)) && ((angle5 >= 50) && (angle5 <= 85) && ((xadc >= 410) && (xadc <= 420)) && ((yadc >= 330) && (yadc <= 370))))
    printfun('I');
  if (((angle1 >= 0) && (angle1 <= 10)) && ((angle2 >= 50) && (angle2 <= 70)) && ((angle3 >= 50) && (angle3 <= 70)) && ((angle4 >= 50) && (angle4 <= 70)) && ((angle5 >= 50) && (angle5 <= 85)) && (!((xadc >= 410) && (xadc <= 420)) && ((yadc >= 355) && (yadc <= 370))))
    printfun('J');
  if (((angle1 >= 60) && (angle1 <= 75)) && ((angle2 >= 60) && (angle2 <= 85)) && ((angle3 >= 0) && (angle3 <= 10)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 30) && (angle5 <= 55)) && (((xadc >= 404) && (xadc <= 415)) && ((yadc >= 368) && (yadc <= 380))))
    printfun('K');
  if (((angle1 >= 75) && (angle1 <= 90)) && ((angle2 >= 75) && (angle2 <= 90)) && ((angle3 >= 70) && (angle3 <= 90)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 0) && (angle5 <= 30)) && (((xadc >= 390) && (xadc <= 405)) && ((yadc >= 360) && (yadc <= 380))) && !((xadc >= 270) && (xadc <= 300)) && ((yadc >= 360) && (yadc <= 390)))
    printfun('L');
  if (((angle1 >= 40) && (angle1 <= 61)) && ((angle2 >= 72) && (angle2 <= 84)) && ((angle3 >= 45) && (angle3 <= 65)) && ((angle4 >= 62) && (angle4 <= 75)) && ((angle5 >= 65) && (angle5 <= 86)))
    printfun('M');
  if (((angle1 >= 54) && (angle1 <= 70)) && ((angle2 >= 50) && (angle2 <= 61)) && ((angle3 >= 48) && (angle3 <= 66)) && ((angle4 >= 60) && (angle4 <= 76)) && ((angle5 >= 50) && (angle5 <= 65)) && (((xadc >= 400) && (xadc <= 435)) && ((yadc >= 350) && (yadc <= 390))))
    printfun('N');
  if (((angle1 >= 68) && (angle1 <= 88)) && ((angle2 >= 68) && (angle2 <= 90)) && ((angle3 >= 50) && (angle3 <= 80)) && ((angle4 >= 54) && (angle4 <= 80)) && ((angle5 >= 0) && (angle5 <= 30)))
    printfun('O');
  if (((angle1 >= 60) && (angle1 <= 75)) && ((angle2 >= 60) && (angle2 <= 85)) && ((angle3 >= 0) && (angle3 <= 10)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 30) && (angle5 <= 55)) && (((xadc >= 270) && (xadc <= 290)) && ((yadc >= 360) && (yadc <= 380))))
    printfun('P');
  if (((angle1 >= 75) && (angle1 <= 90)) && ((angle2 >= 75) && (angle2 <= 90)) && ((angle3 >= 65) && (angle3 <= 90)) && ((angle4 >= 0) && (angle4 <= 15)) && ((angle5 >= 0) && (angle5 <= 30)) && (((xadc >= 270) && (xadc <= 300)) && ((yadc >= 360) && (yadc <= 390))))
    printfun('Q');
  if (((angle1 >= 40) && (angle1 <= 72)) && ((angle2 >= 45) && (angle2 <= 90)) && ((angle3 >= 20) && (angle3 <= 45)) && ((angle4 >= 0) && (angle4 <= 10)) && ((angle5 >= 45) && (angle5 <= 80)) && (((xadc >= 412) && (xadc <= 418)) && ((yadc >= 340) && (yadc <= 360))))
    printfun('R');
  if (((angle1 >= 70) && (angle1 <= 90)) && ((angle2 >= 80) && (angle2 <= 90)) && ((angle3 >= 80) && (angle3 <= 90)) && ((angle4 >= 80) && (angle4 <= 90)) && ((angle5 >= 60) && (angle5 <= 80)))
    printfun('S');
  if (((angle1 >= 40) && (angle1 <= 61)) && ((angle2 >= 72) && (angle2 <= 84)) && ((angle3 >= 45) && (angle3 <= 65)) && ((angle4 >= 44) && (angle4 <= 63)) && ((angle5 >= 65) && (angle5 <= 86)) && (digitalRead(6) == HIGH))
    printfun('T'); */
  if (((angle1 >= 39) && (angle1 <= 75)) && ((angle2 >= 40) && (angle2 <= 80)) && ((angle3 >= 0) && (angle3 <= 25)) && ((angle4 >= 0) && (angle4 <= 25)) && ((angle5 >= 14) && (angle5 <= 52)) && (digitalRead(3) == HIGH)) //checks if foil button is touching
    printfun('U');
  if (((angle1 >= 39) && (angle1 <= 75)) && ((angle2 >= 40) && (angle2 <= 80)) && ((angle3 >= 0) && (angle3 <= 25)) && ((angle4 >= 0) && (angle4 <= 25)) && ((angle5 >= 14) && (angle5 <= 60)) && ((digitalRead(3) == LOW))) //checks if foil button isnt touching
    printfun('V');
  if (((angle1 >= 70) && (angle1 <= 90)) && ((angle2 >= 0) && (angle2 <= 10)) && ((angle3 >= 0) && (angle3 <= 10)) && ((angle4 >= 0) && (angle4 <= 10)) && ((angle5 >= 60) && (angle5 <= 80)))
    printfun('W');
  if (((angle1 >= 50) && (angle1 <= 72)) && ((angle2 >= 45) && (angle2 <= 90)) && ((angle3 >= 35) && (angle3 <= 75)) && ((angle4 >= 80) && (angle4 <= 89)) && ((angle5 >= 45) && (angle5 <= 80))) //&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
    printfun('X');
  if (((angle1 >= 0) && (angle1 <= 10)) && ((angle2 >= 70) && (angle2 <= 90)) && ((angle3 >= 60) && (angle3 <= 80)) && ((angle4 >= 80) && (angle4 <= 90)) && ((angle5 >= 15) && (angle5 <= 35)))
    printfun('Y');
  if (((angle1 >= 50) && (angle1 <= 72)) && ((angle2 >= 45) && (angle2 <= 90)) && ((angle3 >= 35) && (angle3 <= 75)) && ((angle4 >= 0) && (angle4 <= 10)) && ((angle5 >= 45) && (angle5 <= 80)) && (((xadc >= 412) && (xadc <= 418)) && ((yadc >= 340) && (yadc <= 360))))
    printfun('Z');


  delay(1000);

}
//----------------------END-----------------------------
