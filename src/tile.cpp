#include "tile.h"
#include <math.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include "cell.h"
#include "param.h"

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
                          int kernel_c,
                          int weight_precision)
{
    int kernelSize = kernel_w * kernel_h * kernel_c;
    int CellPrecision = cellArray[0][0].getCellPrecision();
    int NumCellPerWeight = ceil(weight_precision / CellPrecision);
    int maxNumKernelPerColumn = int(floor(size_h / kernelSize));
    int maxNumWeightPerRow = int(floor(size_w / NumCellPerWeight));


    ifstream inFile(inFileName, ios::in);
    if (!inFile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    cout << "Weight precision = " << weight_precision << endl;
    cout << "Cell precision = " << CellPrecision << endl;
    cout << "Number of cells per weight = " << NumCellPerWeight << endl;
    cout << "Kernel size = " << kernel_w << "x" << kernel_h << "x" << kernel_c
         << endl;
    cout << "Maximum number of set of weights (kernels) stored per column = "
         << maxNumKernelPerColumn << endl;
    cout << "Maximum number of weights stored per row = " << maxNumWeightPerRow
         << endl;

    if (kernelSize > size_h) { //this is wrong, should accumulate the result, fix later
        cout << "ERROR: Kernel size should be smaller than number of weights "
                "that can be stored in a column"
             << endl;
        exit(1);
    }

    int weight;
    int cellValue;
    int kernelCount = 1;
    int weightCount = 0;
    for (int rowset = 0; rowset < maxNumKernelPerColumn; ++rowset) {
        if (size_h - rowset * kernelSize <
            kernelSize) {  // check if the remaining rows can
                           // accomodate the next kernel
            cout << "Not enough crossbar cells to map next kernel" << endl;
            goto DONE;
        }
        for (int col = 0; col < size_w; col = col + NumCellPerWeight) {
            for (int row = 0; row < kernelSize; ++row) {
                if (row == kernelSize - 1) {
                    cout << "Finished programming " << kernelCount
                         << " kernel(s)" << endl;
                    kernelCount++;
                }
                inFile >> weight;
                // cout << endl
                //      << "[" << row << "][" << col << "]: Weight " <<
                //      weightCount
                //      << " = " << weight << endl;
                for (int cell = 0; cell < NumCellPerWeight;
                     ++cell) {  // LSB -> MSB
                    if (weight == 0)
                        break;
                    cellValue = separateBits(weight, CellPrecision);
                    weight = weight >> CellPrecision;
                    cellArray[row + rowset * kernelSize][cell + col].setValue(
                        cellValue);
                }
                if (inFile.eof())
                    goto DONE;

                weightCount++;
            }
        }
    }

DONE:
    cout << "Done mapping all the weights" << endl;
    printFloorPlan("WeightFloorPlan", 0);
    originalWeight(NumCellPerWeight, maxNumWeightPerRow);
}

int separateBits(int value, int CellPrecision)
{
    int mask = pow(2, CellPrecision) - 1;
    int cellValue = value & mask;
    // cout << "mask = "<< mask << endl;
    // cout << "cell value = " << cellValue << endl;
    return cellValue;
}

void Tile::originalWeight(int NumCellPerWeight, int maxNumWeightPerRow)
{
    ofstream outfile("./FloorPlan/originalWeight", ios::out);
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    outfile << " \t";
    for (int j = 0; j < maxNumWeightPerRow; ++j) {
        outfile << j << "\t";
    }
    outfile << endl;



    for (int i = 0; i < size_h; ++i) {
        outfile << i << "\t";
        for (int j = 0; j < size_w; j = j + NumCellPerWeight) {
            int weight = 0;
            for (int cnt = 0; cnt < NumCellPerWeight; ++cnt) {
                weight += (cellArray[i][cnt + j].getValue() << cnt);
                if (cnt == NumCellPerWeight - 1) {
                    outfile << weight << "\t";
                }
            }
        }
        outfile << endl;
    }
}

void Tile::printFloorPlan(string name, int option)
{
    if (!experimental::filesystem::is_directory("FloorPlan") ||
        !experimental::filesystem::exists(
            "FloorPlan")) {  // Check if src folder exists
        experimental::filesystem::create_directory(
            "FloorPlan");  // create src folder
    }

    ofstream outfile("./FloorPlan/" + name, ios::out);
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    if (cellArray[0][0].getCellType() == 0)
        outfile << "Cell Type = SRAM" << endl;
    else
        outfile << "Cell Type = RRAM" << endl;

    switch (option) {
    case 0:
        outfile << "Crossbar's stored weights" << endl;
        break;
    case 1:
        outfile << "Crossbar's wordline status" << endl;
        break;
    default:
        outfile << "Crossbar's input voltage" << endl;
        break;
    }

    outfile << " \t";
    for (int j = 0; j < size_w; ++j) {
        outfile << j << "\t";
    }
    outfile << endl;



    for (int i = 0; i < size_h; ++i) {
        outfile << i << "\t";
        for (int j = 0; j < size_w; ++j) {
            switch (option) {
            case 0:
                outfile << cellArray[i][j].getValue() << "\t";
                break;
            case 1:
                outfile << cellArray[i][j].getEnable() << "\t";
                break;
            default:
                outfile << cellArray[i][j].getVoltage() << "\t";
                break;
            }
        }
        outfile << endl;
    }
}


float Tile::getCellPartialSum(int row, int col)
{
    return cellArray[row][col].getPartialSum();
}

float Tile::getPower(int input, float VGG) 
{
    int col;
    if(input == 0)
        col = 0;
    else
        col = floor(log2(input)) + 1;

    // cout << "VGG: " << VGG << endl;
    cout << "input: "<<input << ", power: " ;


    if (VGG == 0.9f)
    {
        cout << powerTable6[0][col] << "E-05" << endl;
        return powerTable6[0][col];
    }
    else if (VGG == 0.8f)
    {
        cout << powerTable6[1][col] << "E-05" << endl;
        return powerTable6[1][col];
    }
    else if (VGG == 0.7f)
    {
        cout << powerTable6[2][col] << "E-05" << endl;
        return powerTable6[2][col];
    }
    else
    {
        cout << "no corresponding power table for VGG = " << VGG  << endl;
        return -1;
    }
}