#include <Arduino.h>

#include <fingers.h>

#include <numberFunctions.h>

int potpin = 26; // analog pin used to connect the potentiometeru
int val, rev;    // variable to read the value from the analog pin

bool usePot = true;
bool usePose = true;
bool useRaw = false;
bool useAI = false;
bool printPotVal = false;

void printHelp()
{
  Serial.println("0: zero");
  Serial.println("1: one");
  Serial.println("2: two");
  Serial.println("3: three");
  Serial.println("4: four");
  Serial.println("5: five");
  Serial.println("p: toggle potentiometer control");
  Serial.println("f: toggle finger pose control");
  Serial.println("r: toggle raw potentiometer control");
  Serial.println("a: toggle AI - used with AI control app");
}

void setup()
{
  delay(1000);
  Serial.begin(115200); //  setup serial

  thumbFinger.printSettings();
  indexFinger.printSettings();
  middleFinger.printSettings();
  ringFinger.printSettings();
  pinkyFinger.printSettings();
  delay(1000);
  printHelp();
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
        usePose = !usePose;
      }
      else if (c == 'r')
      {
        useRaw = !useRaw;
      }
      else if (c == 'a')
      {
        useAI = !useAI;
      }
      else if (c == 'h')
      {
        printHelp();
      }
      else if (c == 'd')
      {
        printPotVal = !printPotVal;
      }
    }

    if (usePot)
    {
      val = analogRead(potpin); // reads the value of the potentiometer (value between 0 and 1023)
      int newVal;
      if (useRaw)
      {
        newVal = setPosVal(val);
      }
      else if (usePose)
      {
        newVal = setFingerPos(val);
      }
      else
      {
        newVal = setFingerNumber(val);
      }
      if (printPotVal)
      {
        Serial.print("potRaw/ modifed: ");
        Serial.print(val);
        Serial.print(" / ");
        Serial.println(newVal);
      }
    }
  }
  else
  {
    if (Serial.available())
    {
      byte fingerValues[30];
      Serial.readBytesUntil('\n', fingerValues, 30);
      Serial.print("fingerValues: "); // print the value
      int ns = 0;
      for (int i = 0; i < 5; i++)
      {
        if (fingerValues[i] == 110)
        {
          ns++;
        }
        Serial.print(fingerValues[i]);
        Serial.print(" ");
      }
      Serial.println();

      if (ns == 5)
      {
        zero();
        useAI = false;
      }
      // Assign each finger value
      thumbFinger.toggleByte(fingerValues[0]);
      indexFinger.toggleByte(fingerValues[1]);
      middleFinger.toggleByte(fingerValues[2]);
      ringFinger.toggleByte(fingerValues[3]);
      pinkyFinger.toggleByte(fingerValues[4]);
    }

    delay(15); // waits for the servo to get there                  // waits for the servo to get there
  }
}
