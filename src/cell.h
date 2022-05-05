#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell(float Area = 7.5632, string cellType = 'SRAM', int cellBit = '1');
    ~Cell();
    float getPower();
    int getValue();
    float getArea();
    float getPartialSum();
    void setVoltage(float VDD);
    void setEnable(bool enable);

private:
    float area;       // unit: nm^2
    string cellType;  // RRAM (1T1R), SRAM (standard 6T SRAM)
    float BL;         // input voltage (V)
    bool WL;          // enable
    // float SL; // RRAM partial sum output
    int value;  // stored weight
    int numBit;
}