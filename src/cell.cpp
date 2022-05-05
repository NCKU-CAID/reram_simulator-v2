#include "cell.h"

Cell::Cell(float Area = 7.5632,
           string cellType = 'SRAM',
           float VDD = 2.5,
           bool enable = 0,
           int cellBit = '1')
    : area(Area), type(cellType), numBit(cellBit)
{
    setVoltage(VDD);
    setEnable(enable);
}
Cell::~Cell() {}

float Cell::getPower()
{
    return /* formula */;
}

int Cell::getValue()
{
    return value;
}

float Cell::getArea()
{
    return area;
}

float Cell::getPartialSum()
{
    // SL = BL*value; //temporary
    // return SL;
    return BL * value;
}

void Cell::setVoltage(float VDD)
{
    BL = VDD;
}

void Cell::setEnable(bool enable)
{
    WL = enable;
}