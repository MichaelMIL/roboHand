#ifndef NUMBERFUNCTIONS_H
#define NUMBERFUNCTIONS_H
#include <fingers.h>

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

int setFingerPos(int val)
{
    val = map(val, 0, 1023, 0, 5); // scale it for use with the servo (value between 0 and 180)
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
    return val;
}

int setFingerNumber(int val)
{
    val = map(val, 0, 1023, 0, 5); // scale it for use with the servo (value between 0 and 180)

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
    return val;
}
int setPosVal(int val)
{
    val = map(val, 0, 1023, 0, 180); // scale it for use with the servo (value between 0 and 180)
    thumbFinger.setPos(val);
    indexFinger.setPos(val);
    middleFinger.setPos(val);
    ringFinger.setPos(val);
    pinkyFinger.setPos(val);
    return val;
}
#endif