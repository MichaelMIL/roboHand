
#include <Arduino.h>

#include "ServoFinger.h"

Finger::Finger(int pin, int closeVal, int openVal, bool isReverse) : pin(pin), openVal(openVal), closeVal(closeVal), isReverse(isReverse)
{
    servo.attach(pin, 500, 2500);
}

void Finger::write(int pos)
{
    if (isReverse)
    {
        pos = 180 - pos;
    }
    servo.write(pos);
}

void Finger::toggleByte(int val)
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

void Finger::open()
{
    write(openVal);
}

void Finger::close()
{
    write(closeVal);
}

void Finger::setPos(int pos)
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

void Finger::setPosRaw(int pos)
{
    write(pos);
}

int Finger::getPos()
{
    return pos;
}

void Finger::printSettings()
{
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.print("openVal: ");
    Serial.println(openVal);
    Serial.print("closeVal: ");
    Serial.println(closeVal);
    Serial.print("isReverse: ");
    Serial.println(isReverse);
}
