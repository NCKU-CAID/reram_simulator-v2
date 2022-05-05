#ifndef TILE_H
#define TILE_H

#include "cell.h"

class Tile
{
public:
    Tile(int Size = 64);
    ~Tile();
    void enableRow(int row, bool enable);
    void setRowVoltage(int row, float VDD);
    void computePartialSum(int col);
    void writeWeight(int input, int tile_w, int tile_h, int channel);

private:
    int size;
    Cell **cellArray;
}