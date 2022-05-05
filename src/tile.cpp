#include "tile.h"
#include "cell.h"

Tile::Tile(int Size = 64) : size(Size)
{
    cellArray = new Cell *[Size];
    for (int i = 0; i < Size; i++) {
        cellArray[i] = new Cell[Size];
    }
}

Tile::~Tile()
{
    for (int i = 0; i < size; i++) {
        delete[] Cell[i];
    }
}

void Tile::enableRow(int row, bool enable)
{
    for (int j = 0; j < size; j++) {
        cellArray[row][j].setEnable(enable);
    }
}

void Tile::setRowVoltage(int row, float VDD)
{
    for (int j = 0; j < size; j++) {
        cellArray[row][j].setVoltage(VDD);
    }
}
void Tile::computePartialSum(int col) {}