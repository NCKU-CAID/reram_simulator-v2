#include "cell.h"
#include <iostream>
// #include "param.h"
#include "Definition.h"
using namespace std;

Cell::Cell(int cellType, int cellBit) : cellType(cellType), numBit(cellBit)
{
    area = param->CellArea;
    BL = 0;
    WL = 0;
    value = 0;
}
Cell::~Cell() {}


int Cell::getValue()
{
    return value;
}

int Cell::getCellPrecision()
{
    return numBit;
}

bool Cell::getEnable()
{
    return WL;
}

float Cell::getArea()
{
    return area;
}

float Cell::getPartialSum()
{
    if (cellType == 0) {  // SRAM
        if (BL != 0)
            return value;
    } else {  // RRAM SL
        return BL * value;
    }
}

float Cell::getVoltage()
{
    return BL;
}

bool Cell::isWLON()
{
    return WL;
}

int Cell::getCellType()
{
    return cellType;
}

void Cell::setVoltage(float VDD)
{
    switch (cellType) {
    case 0:  // SRAM
        BL = VDD;
        if (VDD >= 1)
            setValue(1);
        else
            setValue(0);
        break;
    case 1:  // RRAM
        BL = VDD;
        break;
    default:
        cout << "ERROR: Incorrect cell type" << endl;
    }
}

void Cell::setEnable(bool enable)
{
    WL = enable;
}

void Cell::setValue(int Value)
{
    value = Value;
}
