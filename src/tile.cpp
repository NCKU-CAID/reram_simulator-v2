#include "tile.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include "cell.h"
using namespace std;

int separateBits(int value, int CellPrecision);

Tile::Tile(int Size_w, int Size_h, int cellType, int CellPrecision)
    : size_w(Size_w), size_h(Size_h)
{
    if (cellType == 0 && CellPrecision > 1) {
        cout << "ERROR: SRAM can only store one bit" << endl;
        exit(1);
    }

    cellArray = new Cell *[Size_h];
    for (int i = 0; i < Size_h; ++i) {
        cellArray[i] = new Cell[Size_w];
    }

    cout << "Tile size = " << Size_h << "x" << Size_w << endl;

    initializeCell(Size_w, Size_h, cellType, CellPrecision);
}

Tile::Tile(const Tile &tile) : size_w(tile.size_w), size_h(tile.size_h)
{
    // cout << "copy constructor tile" << endl;

    cellArray = new Cell *[size_h];
    for (int i = 0; i < size_h; ++i) {
        cellArray[i] = new Cell[size_w];
    }

    for (int i = 0; i < size_h; ++i) {
        for (int j = 0; j < size_h; ++j) {
            cellArray[i][j] = Cell(tile.cellArray[i][j].getCellType(),
                                   tile.cellArray[i][j].getCellPrecision());
        }
    }
}

Tile::~Tile()
{
    for (int i = 0; i < size_h; ++i) {
        delete[] cellArray[i];
    }
    delete[] cellArray;

    // cout << "tile destructor" << endl;
}

void Tile::initializeCell(int Width,
                          int Height,
                          int cellType,
                          int cellPrecision)
{
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            cellArray[i][j] = Cell(cellType, cellPrecision);
        }
    }
}

int Tile::getTileHeight()
{
    return size_h;
}

int Tile::getTileWidth()
{
    return size_w;
}

int Tile::getCellValue(int row, int col)
{
    if (cellArray[row][col].isWLON())
        return cellArray[row][col].getValue();
    else
        return 0;
}

int Tile::getCellPrecision(int row, int col)
{
    return cellArray[row][col].getCellPrecision();
}

int Tile::getCellType(int row, int col)
{
    return cellArray[row][col].getCellType();
}

void Tile::enableRow(int row_start, int row_end, bool enable)
{
    for (int row = 0; row < size_h; ++row) {
        for (int col = 0; col < size_w; ++col) {
            if (row >= row_start && row <= row_end)
                cellArray[row][col].setEnable(enable);
            else
                cellArray[row][col].setEnable(0);
        }
    }
}

void Tile::setRowVoltage(int row, float VDD)
{
    for (int j = 0; j < size_w; ++j) {
        cellArray[row][j].setVoltage(VDD);
    }
}

void Tile::writeSingleWeight(int input, int row, int col)
{  // assuming that WLs are all on
    int CellPrecision = cellArray[row][col].getCellPrecision();
    if (input >= pow(2, CellPrecision))
        cout << "ERROR: The input value for the synapse at row " << row
             << " and column " << col << "exceed its cell precision" << endl;
    else
        cellArray[row][col].setValue(input);
}

void Tile::programWeights(string inFileName,
                          int kernel_w,
                          int kernel_h,
                          int weight_precision)
{
    int CellPrecision = cellArray[0][0].getCellPrecision();
    int NumCellPerWeight = ceil(weight_precision / CellPrecision);
    int maxNumKernelPerColumn = int(floor(size_h / (kernel_h * kernel_w)));
    int maxNumWeightPerRow = int(floor(size_w / NumCellPerWeight));
    int kernelSize = kernel_w * kernel_h;

    ifstream inFile(inFileName, ios::in);
    if (!inFile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    cout << "Weight precision = " << weight_precision << endl;
    cout << "Cell precision = " << CellPrecision << endl;
    cout << "Number of cells per weight = " << NumCellPerWeight << endl;
    cout << "Kernel size = " << kernel_w << "x" << kernel_h << endl;
    cout << "Maximum number of set of weights (kernels) stored per column = "
         << maxNumKernelPerColumn << endl;
    cout << "Maximum number of weights stored per row = " << maxNumWeightPerRow
         << endl;

    if (kernelSize > size_h) {
        cout << "ERROR: Kernel size should be smaller than number of weights "
                "that can be stored in a column"
             << endl;
        exit(1);
    }

    int weight;
    int cellValue;
    int kernelCount = 1;
    int weightCount = 0;
    for (int col = 0; col < size_w; col = col + NumCellPerWeight) {
        for (int row = 0; row < size_h; ++row) {
            if (row == kernelSize) {
                cout << "Finished programming " << kernelCount << " kernel(s)"
                     << endl;
                kernelCount++;
                if (size_h - row <
                    kernelSize)  // check if the remaining rows can
                                 // accomodate the next kernel
                    break;
            }
            inFile >> weight;
            if (inFile.eof())
                goto DONE;

            cout << endl
                 << "[" << row << "][" << col << "]: Weight " << weightCount
                 << " = " << weight << endl;
            for (int cell = 0; cell < NumCellPerWeight; ++cell) {  // LSB -> MSB
                if (weight == 0)
                    break;
                cellValue = separateBits(weight, CellPrecision);
                weight = weight >> CellPrecision;
                cellArray[row][cell + col].setValue(cellValue);
            }
            weightCount++;
        }
    }

DONE:
    cout << "Done mapping all the weights" << endl;
    printFloorPlan(0);
}

int separateBits(int value, int CellPrecision)
{
    int mask = pow(2, CellPrecision) - 1;
    int cellValue = value & mask;
    // cout << "mask = "<< mask << endl;
    cout << "cell value = " << cellValue << endl;
    return cellValue;
}

void Tile::printFloorPlan(int option)
{
    if (cellArray[0][0].getCellType() == 0)
        cout << "Cell Type = SRAM" << endl;
    else
        cout << "Cell Type = RRAM" << endl;

    switch (option) {
    case 0:
        cout << "Crossbar's stored weights" << endl;
        break;
    case 1:
        cout << "Crossbar's wordline status" << endl;
        break;
    default:
        cout << "Crossbar's input voltage" << endl;
        break;
    }

    cout << " \t";
    for (int j = 0; j < size_w; ++j) {
        cout << j << "\t";
    }
    cout << endl;



    for (int i = 0; i < size_h; ++i) {
        cout << i << "\t";
        for (int j = 0; j < size_w; ++j) {
            switch (option) {
            case 0:
                cout << cellArray[i][j].getValue() << "\t";
                break;
            case 1:
                cout << cellArray[i][j].getEnable() << "\t";
                break;
            default:
                cout << cellArray[i][j].getVoltage() << "\t";
                break;
            }
        }
        cout << endl;
    }
}


float Tile::getCellPartialSum(int row, int col)
{
    return cellArray[row][col].getPartialSum();
}

float Tile::getPower(float VGG) {}