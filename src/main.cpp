#include <Arduino.h>
/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include "Common.h"

// Servo myservo1; // create servo object to control a servo
// Servo myservo2; // create servo object to control a servo
// Servo myservo3; // create servo object to control a servo
// Servo myservo4; // create servo object to control a servo
// Servo myservo5; // create servo object to control a servo

class Finger
{
private:
  const int pin;
  int pos = 0;
  const int openVal;
  const int closeVal;
  bool isReverse = false;
  Servo servo;

public:
  Finger(int pin, int closeVal, int openVal, bool isReverse = false) : pin(pin), openVal(openVal), closeVal(closeVal), isReverse(isReverse)
  {
    servo.attach(pin, 500, 2500);
  }
  ~Finger(){};

  void write(int pos)
  {
    if (isReverse)
    {
      pos = 180 - pos;
    }
    servo.write(pos);
  }

  void toggleByte(int val)
  {
    if (val == 48)
    {
      close();
    }
    else if (val == 49)
    {
      open();
    }
  }

  void open()
  {

    write(openVal);
  }

  void close()
  {
    write(closeVal);
  }

  void setPos(int pos)
  {
    if (pos > openVal)
    {
      pos = openVal;
    }
    if (pos < closeVal)
    {
      pos = closeVal;
    }
    write(pos);
  }
  void printSettings()
  {
    Serial.print("pin: ");
    Serial.print(pin);
    Serial.print(" openVal: ");
    Serial.print(openVal);
    Serial.print(" closeVal: ");
    Serial.print(closeVal);
    Serial.print(" isReverse: ");
    Serial.print(isReverse);
    Serial.print(" pos: ");
    Serial.println(pos);
  }

  int getPos()
  {
    return pos;
  }
};

int potpin = 26; // analog pin used to connect the potentiometeru
int val, rev;    // variable to read the value from the analog pin

Finger thumbFinger(17, 42, 180);
Finger indexFinger(18, 35, 180, true);
Finger middleFinger(19, 0, 180);
Finger ringFinger(21, 30, 177, true);
Finger pinkyFinger(20, 13, 160);

bool usePot = true;
bool usePot2 = false;
bool useRaw = false;
bool useAI = false;

void zero()
{
  thumbFinger.close();
  indexFinger.close();
  middleFinger.close();
  ringFinger.close();
  pinkyFinger.close();
}

void one()
{
  thumbFinger.close();
  indexFinger.open();
  middleFinger.close();
  ringFinger.close();
  pinkyFinger.close();
}

void two()
{
  thumbFinger.close();
  indexFinger.open();
  middleFinger.open();
  ringFinger.close();
  pinkyFinger.close();
}

void three()
{
  thumbFinger.close();
  indexFinger.open();
  middleFinger.open();
  ringFinger.open();
  pinkyFinger.close();
}

void four()
{
  thumbFinger.close();
  indexFinger.open();
  middleFinger.open();
  ringFinger.open();
  pinkyFinger.open();
}

void five()
{
  thumbFinger.open();
  indexFinger.open();
  middleFinger.open();
  ringFinger.open();
  pinkyFinger.open();
}

void setFingerPos(int val)
{
  val = map(val, 0, 1023, 0, 5); // scale it for use with the servo (value between 0 and 180)
  Serial.print("val: ");         // print the value
  Serial.println(val);           // print the value

  if (val == 0)
  {
    zero();
  }
  else if (val == 1)
  {
    zero();
    thumbFinger.open();
  }
  else if (val == 2)
  {
    zero();
    indexFinger.open();
  }
  else if (val == 3)
  {
    zero();
    middleFinger.open();
  }
  else if (val == 4)
  {
    zero();
    ringFinger.open();
  }
  else if (val == 5)
  {
    zero();
    pinkyFinger.open();
  }
}

void setFingerNumber(int val)
{
  val = map(val, 0, 1023, 0, 5); // scale it for use with the servo (value between 0 and 180)
  Serial.print("val: ");         // print the value
  Serial.println(val);           // print the value

  if (val == 0)
  {
    zero();
  }
  else if (val == 1)
  {
    one();
  }
  else if (val == 2)
  {
    two();
  }
  else if (val == 3)
  {
    three();
  }
  else if (val == 4)
  {
    four();
  }
  else if (val == 5)
  {
    five();
  }
}

void setPosVal(int val)
{
  val = map(val, 0, 1023, 0, 180); // scale it for use with the servo (value between 0 and 180)
  Serial.print("val: ");           // print the value
  Serial.println(val);             // print the value
  thumbFinger.setPos(val);
  indexFinger.setPos(val);
  middleFinger.setPos(val);
  ringFinger.setPos(val);
  pinkyFinger.setPos(val);
}
void setup()
{
  delay(1000);
  Serial.begin(115200); //  setup serial

  // myservo1.attach(21, 500, 2500); // attaches the servo on pin 9 to the servo object
  // myservo2.attach(20, 500, 2500); // attaches the servo on pin 9 to the servo object
  // myservo3.attach(19, 500, 2500); // attaches the servo on pin 9 to the servo object
  // myservo4.attach(18, 500, 2500); // attaches the servo on pin 9 to the servo object
  // myservo5.attach(17, 500, 2500); // attaches the servo on pin 9 to the servo object
  thumbFinger.printSettings();
  indexFinger.printSettings();
  middleFinger.printSettings();
  ringFinger.printSettings();
  pinkyFinger.printSettings();
}

void loop()
{
  if (!useAI)
  {

    if (Serial.available())
    {
      char c = Serial.read();
      if (c == '0')
      {
        zero();
      }
      else if (c == '1')
      {
        one();
      }
      else if (c == '2')
      {
        two();
      }
      else if (c == '3')
      {
        three();
      }
      else if (c == '4')
      {
        four();
      }
      else if (c == '5')
      {
        five();
      }
      else if (c == 'p')
      {
        usePot = !usePot;
      }
      else if (c == 'f')
      {
        usePot2 = !usePot2;
      }
      else if (c == 'r')
      {
        useRaw = !useRaw;
      }
      else if (c == 'a')
      {
        useAI = !useAI;
      }
    }

    if (usePot)
    {
      val = analogRead(potpin); // reads the value of the potentiometer (value between 0 and 1023)
      if (useRaw)
      {
        setPosVal(val);
        return;
      }
      if (usePot2)
      {
        setFingerPos(val);
      }
      else
      {
        setFingerNumber(val);
      }
      // setPosVal(val);
    }
  }
  else
  {
    if (Serial.available())
    {
      byte fingerValues[30];
      Serial.readBytesUntil('\n', fingerValues, 30);
      Serial.print("fingerValues: "); // print the value
      for (int i = 0; i < 5; i++)
      {
        Serial.print(fingerValues[i]);
        Serial.print(" ");
      }
      Serial.println();
      // Assign each finger value
      thumbFinger.toggleByte(fingerValues[0]);
      indexFinger.toggleByte(fingerValues[1]);
      middleFinger.toggleByte(fingerValues[2]);
      ringFinger.toggleByte(fingerValues[3]);
      pinkyFinger.toggleByte(fingerValues[4]);
    }
    // setFingerPos(val);
    // Serial.print(" rev: "); // print the value
    // Serial.println(rev);    // print the value
    // thumbFinger.setPos(val);
    // indexFinger.setPos(val);
    // middleFinger.setPos(val);
    // ringFinger.setPos(val);
    // pinkyFinger.setPos(val);

    // Serial1.print("val: ");               // print the value
    // Serial1.println(ringFinger.getPos()); // print the value

    // myservo1.write(rev);    // sets the servo position according to the scaled value
    // myservo2.write(val);    // sets the servo position according to the scaled value
    // myservo3.write(val);    // sets the servo position according to the scaled value
    // myservo4.write(rev);    // sets the servo position according to the scaled value
    // myservo5.write(val);    // sets the servo position according to the scaled value
    //   myservo1.writeMicroseconds(rev);                  // sets the servo position according to the scaled value
    // myservo2.writeMicroseconds(val);                  // sets the servo position according to the scaled value
    // myservo3.writeMicroseconds(val);                  // sets the servo position according to the scaled value
    // myservo4.writeMicroseconds(rev);                  // sets the servo position according to the scaled value
    // myservo5.writeMicroseconds(val);                  // sets the servo position according to the scaled value

    delay(15); // waits for the servo to get there                  // waits for the servo to get there
  }
}
