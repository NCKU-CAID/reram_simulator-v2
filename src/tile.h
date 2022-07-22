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
         int CellPrecision = 1);
    Tile(const Tile &tile);
    ~Tile();
    void initializeCell(int Width, int Height, int cellType, int cellPrecision);
    int getTileHeight();
    int getTileWidth();
    int getCellValue(int row, int col);
    int getCellType(int row, int col);
    int getCellPrecision(int row, int col);
    void enableRow(int row_start, int row_end, bool enable);
    void setRowVoltage(int row, float VDD);
    float getCellPartialSum(int row, int col);
    void writeSingleWeight(int input, int row, int col);
    void programWeights(std::string inFileName,
                        int kernel_w = 3,
                        int kernel_h = 3,
                        int kernel_c = 7,
                        int weight_precision = 8);
    void printFloorPlan(std::string name, int option);
    void originalWeight(int NumCellPerWeight,
                        int maxNumWeightPerRow,
                        int weightPrecision,
                        int sign = 1);
    float getPower(int input, float VDD = 0.9, int bitNum = 6);

private:
    int size_w;
    int size_h;
    Cell **cellArray;

    // SRAM power table for 6-bit output
    float powerTable6[3][7] =  // *E-05
        {
            {0.258, 2.39, 3.22, 4.06, 4.94, 5.99, 6.94},  // 0.9V
            {0.18, 1.84, 2.48, 3.14, 3.83, 4.64, 5.39},   // 0.8V
            {0.0897, 0.942, 1.26, 1.6, 1.96, 2.4, 2.8}    // 0.7V
    };
    // SRAM power table for 7-bit output
    float powerTable7[3][8] =  // *E-05 // not used for current design (64x64)
        {
            {0.401, 2.96, 3.76, 4.84, 5.57, 6.67, 8.02, 9.47},  // 0.9V
            {0.277, 2.27, 2.9, 3.74, 4.32, 5.17, 6.22, 7.36},   // 0.8V
            {0.132, 1.15, 1.48, 1.93, 2.22, 2.66, 3.22, 3.82}   // 0.7V
    };
};

#endif