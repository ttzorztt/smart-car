// SDCC 4.0.0 #11528 (Linux) + python3.9.7
#include <8052.h>
#define leftWheelFront P2_4=1;P2_5=0;
#define rightWheelFront P2_6=1;P2_7=0;
#define carStop P2_4=1;P2_5=1;P2_6=1;P2_7=1;
#define carTurnRight P2_4=0;P2_5=1;P2_6=1;P2_7=0;
#define carTurnLeft P2_4=1;P2_5=0;P2_6=0;P2_7=1;
#define leftUp P1_0
#define rightUp P1_1
#define leftDown P1_2
#define rightDown P1_3
#define center P1_4
#define sound P2_0
#define alertLed P1_0
int count = 0;
int time = 0;
char i = 0;
char table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82,
                0xf8, 0x80, 0x90};
char End = 0;
// car go front
void go(char speed)
{
    for (char a = 0; a < speed; ++a)
    {
        carStop
    }
    leftWheelFront
        rightWheelFront
}
// alert sound
void Sound()
{
    sound = 0;
    for (char a = 0; a <= 10; ++a)
        ;
    sound = 1;
}
// alert Led
void AlertLed()
{
    alertLed = 0;
}
void interrupt_() __interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x67;
    ++count;
    if (leftUp == 0 || rightUp == 0)
    {
        Sound();
        AlertLed();
    }
    else
        alertLed = 1;
    if (count >= 1000)
    {
        count = 0;
        if (!End)
            time++;
    }
    switch (i)
    {
    case 0:
        P2_0 = 1;
        P0 = table[time % 10];
        P2_1 = 0;
        ++i;
        break;
    case 1:
        P2_1 = 1;
        P0 = table[time % 100 / 10];
        P2_0 = 0;
        --i;
        break;
    }
}
void main()
{
    // open interrupt
    TMOD = 0x01;
    ET0 = 1;
    EA = 1;
    // set base data
    TH0 = 0xFC;
    TL0 = 0x67;
    TR0 = 1;
    while (End == 0)
    {
        if (center == 0 && rightDown == 0 && leftDown == 0)
        {
            End = 1;
            while (1)
            {
                carStop
            }
        }
        else if (center == 1 && rightDown == 1)
        {
            carTurnLeft for (char a = 0; a <= 10; ++a)
            {
                carStop
            }
        }
        else if (center == 1 && leftDown == 1)
        {
            carTurnRight for (char a = 0; a <= 10; ++a)
            {
                carStop
            }
        }
        else
            go(7);
    }
}
