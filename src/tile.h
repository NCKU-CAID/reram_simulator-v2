#ifndef TILE_H
#define TILE_H

#include <string>
#include "cell.h"

class Tile
{
public:
    Tile(int Size = 64,
         int cellType = 0,
         int CellPrecision = 1,
         float Area = 7.5632);
    ~Tile();
    int getSize();
    void enableRow(int row, bool enable);
    void setRowVoltage(int row, float VDD);
    void computePartialSum(int col);
    void writeSingleWeight(int input, int row, int col);
    void programWeights(std::string inFileName,
                        int kernel_w = 3,
                        int kernel_h = 3,
                        int weight_precision = 8);
    void printWeightFloorPlan();
    float getPower(float VDD);

private:
    int size;
    Cell **cellArray;
};

#endif