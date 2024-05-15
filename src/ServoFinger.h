#ifndef SERVOFINGER_H
#define SERVOFINGER_H

#include <Servo.h>
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
    Finger(int pin, int closeVal, int openVal, bool isReverse = false);
    void write(int pos);
    void toggleByte(int val);
    void open();
    void close();
    void setPos(int pos);
    int getPos();
    void setPosRaw(int pos);
    void printSettings();
};

#endif