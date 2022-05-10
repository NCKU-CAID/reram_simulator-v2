#include <math.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "cell.h"
#include "tile.h"

using namespace std;

int separateInputBits(int value, int CellPrecision, int input_prec);
void initialize(int *array, int size);

void matrixMultiplication(string inFileName,
                          int input_precision,
                          Tile &tile,
                          int kernel_w,
                          int kernel_h,
                          int kernel_c,
                          int weight_precision,
                          string outFileName)
{
    ifstream inFile(inFileName, ios::in);
    if (!inFile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    int kernelSize = kernel_w * kernel_h * kernel_c;
    int CellPrecision = tile.getCellPrecision(0, 0);
    int NumCellPerWeight = ceil(weight_precision / CellPrecision);
    int maxNumKernelPerColumn = int(floor(tile.getTileHeight() / kernelSize));
    int maxNumWeightPerRow = int(floor(tile.getTileWidth() / NumCellPerWeight));

    // cout << "Weight precision = " << weight_precision << endl;
    // cout << "Cell precision = " << CellPrecision << endl;
    // cout << "Number of cells per weight = " << NumCellPerWeight << endl;
    // cout << "Kernel size = " << kernel_w << "x" << kernel_h << endl;
    // cout << "Maximum number of set of weights (kernels) stored per column = "
    //      << maxNumKernelPerColumn << endl;
    // cout << "Maximum number of weights stored per row = " <<
    // maxNumWeightPerRow
    //      << endl;

    int *Accumulator = new int[maxNumWeightPerRow];
    int *Shift_Adder = new int[maxNumWeightPerRow];


    string outName = "./output/" + outFileName;
    if (!experimental::filesystem::is_directory("output") ||
        !experimental::filesystem::exists(
            "output")) {  // Check if src folder exists
        experimental::filesystem::create_directory(
            "output");  // create src folder
    }
    ofstream outfile(outName, ios::out);
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    // RRAM matrix multiplication
    cout << endl << "Start matrix multiplication" << endl;
    for (int inputSet = 0; inputSet < maxNumKernelPerColumn; ++inputSet) {
        int *inputData = new int[kernelSize];
        for (int i = 0; i < kernelSize; ++i) {
            inFile >> inputData[i];
            if (inFile.eof()) {
                cout << "End of File" << endl;
                break;
            }
        }
        initialize(Accumulator, maxNumWeightPerRow);
        initialize(Shift_Adder, maxNumWeightPerRow);

        for (int i = 0; i < tile.getTileHeight(); ++i) {
            tile.setRowVoltage(i, 0);
        }



        cout << " ______________ INPUT SET " << inputSet << " _____________"
             << endl;

        // cout << "enableRow: " << inputSet*kernelSize << " to " <<
        // (inputSet+1)*kernelSize-1 << endl;
        tile.enableRow(inputSet * kernelSize, (inputSet + 1) * kernelSize - 1,
                       1);  // enable rows for a matrix multiplication
        tile.printFloorPlan("WLFloorPlan", 1);

        for (int i_prec = input_precision - 1; i_prec >= 0;
             --i_prec)  // for the <first> bit of input
        {
            initialize(Accumulator, maxNumWeightPerRow);


            for (int k = 0; k < maxNumWeightPerRow;
                 ++k)  // for the <first> set of kernel in the kth (weight
                       // precision) columns
            {
                Shift_Adder[k] = Shift_Adder[k] << 1;
                // cout << "Shift partial sum for input bit " << k << ": "
                // << Shift_Adder[k] << endl;

                cout << "----- Kernel " << k << "-----" << endl;
                for (int cell = NumCellPerWeight - 1; cell >= 0;
                     --cell)  // for the <first> bit of weight
                {
                    // cout << "< cell " << cell << " >" << endl;
                    Accumulator[k] = Accumulator[k] << CellPrecision;
                    // cout << "Shift partial sum " << k << ": " <<
                    // Accumulator[k]
                    //      << endl;

                    for (int i = 0; i < kernelSize;
                         ++i)  // for the <first> input for the <first> kernel
                               // element
                    {
                        // cout << " - Input " << inputData[i];
                        int inputBit = separateInputBits(inputData[i], i_prec,
                                                         input_precision);
                        // cout << "\t bit " << i_prec << " = " << inputBit
                        // << endl;
                        tile.setRowVoltage(i + inputSet * kernelSize, inputBit);

                        // cout << " - Weight: "
                        //      << tile.getCellValue(i + inputSet * kernelSize,
                        //                           cell + k *
                        //                           NumCellPerWeight)
                        //      << endl;

                        Accumulator[k] +=
                            tile.getCellPartialSum(i + inputSet * kernelSize,
                                                   cell + k * NumCellPerWeight);
                        // cout << " - partial sum " << k << ": " <<
                        // Accumulator[k]
                        //      << endl
                        //      << endl;
                    }
                }
                Shift_Adder[k] += Accumulator[k];
                cout << "S&H " << k << ": " << Shift_Adder[k] << endl;
            }
            cout << "--------- input bit " << i_prec << " ------------" << endl;
            tile.printFloorPlan("InputFloorPlan", 2);
        }



        for (int k = 0; k < maxNumWeightPerRow; ++k) {
            outfile << Shift_Adder[k] << "\t";
        }
        outfile << endl;
    }

    delete[] Accumulator;
    delete[] Shift_Adder;

DONE:
    cout << "Done doing matrix multiplication of the input feature map" << endl;
}

int separateInputBits(int value, int bit, int input_prec)
{
    if (value > pow(2, input_prec)) {
        cout << endl
             // cout << "input value = " << value << ", 2^precision = " <<
             // pow(2,input_prec) << endl
             << "ERROR: Input value exceeds the input precision" << endl;
        exit(1);
    }

    int mask = 1;
    return (value >> bit) & mask;
}

void initialize(int *array, int size)
{
    for (int i = 0; i < size; ++i) {
        array[i] = 0;
    }
}
