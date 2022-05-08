#ifndef TILE_H
#define TILE_H

#include <string>
#include "cell.h"

class Tile
{
public:
    Tile(int Size_w = 64,
         int Size_h = 64,
         int cellType = 0,
         int CellPrecision = 1,
         float Area = 7.5632);
    ~Tile();
    int getTileHeight();
    int getTileWidth();
    int getCellValue(int row, int col);
    int getCellPrecision(int row, int col);
    void enableRow(int row_start, int row_end, bool enable);
    void setRowVoltage(int row, float VDD);
    float getCellPartialSum(int row, int col);
    void writeSingleWeight(int input, int row, int col);
    void programWeights(std::string inFileName,
                        int kernel_w = 3,
                        int kernel_h = 3,
                        int weight_precision = 8);
    void printFloorPlan(int option);
    float getPower(float VDD);

private:
    int size_w;
    int size_h;
    Cell **cellArray;
};

#endif