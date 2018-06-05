#include <iostream>
#include <graphics.h>
#include <mattcore.h>
#include <mattmark.h>
#include "functions.h"

int main()
{
    initwindow(1000,1000,"Game of life",100,100);
    ///Grid will be 100x100 10px x 10px each cell;
    board a;
    a.randomConstructs();
    a.initDraw();
    for(;true;)
    {
        a.draw();
        a.nextStep();
    }
    _getch();


    return 0;
}
