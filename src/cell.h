#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell(int cellType = 0, int cellBit = 1, float Area = 7.5632);
    ~Cell();

    bool isWLON();
    int getValue();
    int getCellType();
    int getCellPrecision();
    bool getEnable();
    float getArea();
    float getVoltage();
    float getPartialSum();        // for RRAM's matrix multiplication
    void setVoltage(float VDD);   // SRAM: VDD determines the written value,
                                  // RRAM: VDD is the input data
    void setEnable(bool enable);  // turn on/off the WL
    void setValue(int Value);     // program weight

private:
    float area;    // unit: nm^2
    int cellType;  // 0: SRAM (standard 6T SRAM), 1: RRAM (1T1R)
    float BL;      // input voltage (V)
    bool WL;       // enable
    // float SL; // RRAM partial sum output
    int value;  // stored weight
    int numBit;
};

#endif