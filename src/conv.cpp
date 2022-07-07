#include <math.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "cell.h"
#include "tile.h"
#include "result.h"

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
                          int signed_weight,
                          // string outFileName,
                          string &mat_result,
                          float ADC_voltage,
                          int relu_on)
{
    ifstream inFile(inFileName, ios::in);
    if (!inFile) {
        cerr << "Failed opening file: " << inFileName << endl;
        exit(1);
    }


    int kernelSize = kernel_w * kernel_h * kernel_c;
    if (kernelSize>tile.getTileHeight())
        kernelSize = tile.getTileHeight(); //the incomplete channels (the rest of the first 64 weights) will be sequentially done

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
    

    // string outName = "./output/" + outFileName;
    // if (!experimental::filesystem::is_directory("output") ||
    //     !experimental::filesystem::exists(
    //         "output")) {  // Check if src folder exists
    //     experimental::filesystem::create_directory(
    //         "output");  // create src folder
    // }
    // ofstream outfile(outName, ios::out);
    // if (!outfile) {
    //     cerr << "Failed opening file: " << outName << endl;
    //     exit(1);
    // }

    // RRAM matrix multiplication
    cout << endl << "Start matrix multiplication" << endl;

    Result *result = new Result();
    result->setPower(0);
    float tempOut = 0;

    for (int inputSet = 0; inputSet < maxNumKernelPerColumn; ++inputSet) {
        int *inputData = new int[kernelSize];
        for (int i = 0; i < kernelSize; ++i) {
           
            if (inFile.eof()) {
                // cout << "End of File" << endl;
                inputData[i]=0;
                // cout << inputData[i] << '\t';
                
            }
            else{
                inFile >> inputData[i];
                // cout << inputData[i] << '\t';
            }
        }
        cout << endl;
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


        //--------------------------- calculate # of negative values --------------------

        //for recording number of <0 in a weight column (NumCellPerWeight columns)
        int *negative_count = new int[maxNumWeightPerRow];
        initialize(negative_count, maxNumWeightPerRow);

        if(signed_weight)
        {
            for (int MSBcell = NumCellPerWeight - 1; MSBcell < tile.getTileWidth();
                            MSBcell=MSBcell+NumCellPerWeight)  // for the <first> bit of weight
            {
                int k = (MSBcell+1)/NumCellPerWeight-1;
                for(int i = 0; i<kernelSize; ++i)
                {
                    int msb_mask = 1 << (CellPrecision - 1);
                    int cellvalue = tile.getCellValue(i + inputSet*kernelSize, MSBcell);
                    int msb = cellvalue&msb_mask;
                    if(msb)
                    {
                        negative_count[k] += 1;                        
                    }
                    // cout << "cell value: "<< cellvalue << ", MSB: "<<msb<<endl;

                }
                // cout << "negative value of "<< k << "'s weight column: " << negative_count[k] << endl;
            }
        }
        //--------------------------- calculate # of negative values --------------------


        for (int i_prec = input_precision - 1; i_prec >= 0;
             --i_prec)  // for the <first> bit of input
        {
            initialize(Accumulator, maxNumWeightPerRow);
            cout << "--------- input bit " << i_prec << " ------------" << endl;

            for (int k = 0; k < maxNumWeightPerRow;
                 ++k)  // for the <first> set of kernel in the kth (weight
                       // precision) columns
            {
                Shift_Adder[k] = Shift_Adder[k] << 1;
                cout << "Shift partial sum for input bit " << k << ": "
                << Shift_Adder[k] << endl;

                cout << "----- Kernel " << k << "-----" << endl;
                for (int cell = NumCellPerWeight - 1; cell >= 0;
                     --cell)  // for the <first> bit of weight
                {
                    // cout << "< cell " << cell << " >" << endl;
                    Accumulator[k] = Accumulator[k] << CellPrecision;
                    // cout << "Shift partial sum " << k << ": " <<
                    // Accumulator[k]
                    //      << endl;
                    tempOut = 0;

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

                        float partialSUm = tile.getCellPartialSum(i + inputSet * kernelSize,
                                                   cell + k * NumCellPerWeight); 
                        Accumulator[k] += partialSUm;
                        tempOut += partialSUm;
                                                    
                        // cout << " - partial sum " << k << ": " <<
                        // Accumulator[k]
                        //      << endl
                        //      << endl;
                       

                    }
                    result->storePower(tile.getPower(tempOut, ADC_voltage));
                }                
                Shift_Adder[k] += Accumulator[k];
                cout << "S&H " << k << ": " << Shift_Adder[k] << endl;


            }
           
            tile.printFloorPlan("InputFloorPlan", 2);
        }


        int outresult = 0;

        for (int k = 0; k < maxNumWeightPerRow; ++k) {
            switch(signed_weight)
            {
                case 0: 
                    // outfile << Shift_Adder[k] << "\t";
                    mat_result.append(to_string(Shift_Adder[k])+"\t");
                    break;
                case 1:
                    outresult = Shift_Adder[k] - negative_count[k]*(pow(2, weight_precision)-1); 
                    if (outresult < 0)
                        // outfile << 0 << "\t";
                        mat_result.append(to_string(0)+"\t");
                    else
                        // outfile << outresult << "\t";
                        mat_result.append(to_string(outresult)+"\t");

                    break;
                default: 
                    // cout << "# of negative values in " << k << "'s weight: " << negative_count[k] << endl;
                    // cout << Shift_Adder[k] << endl;
                    // cout << Shift_Adder[k] - negative_count[k]*((pow(2, weight_precision)-1) + 1) << endl;
                    outresult = Shift_Adder[k] - negative_count[k]*((pow(2, weight_precision)-1) + 1); 
                    if (relu_on && outresult < 0)
                        // outfile << 0 << "\t";
                        mat_result.append(to_string(0)+"\t");


                    else
                        // outfile << outresult << "\t";
                        mat_result.append(to_string(outresult)+"\t");

                    break;
            }
            
        }
        // outfile << endl;
       // mat_result.append("\n");

    }

    delete[] Accumulator;
    delete[] Shift_Adder;


DONE:
    cout << "ADC power: " << result->getPower() << "E-05 (W)" << endl;
    cout << "Done doing matrix multiplication of the input feature map" << endl;
}

int separateInputBits(int value, int bit, int input_prec)
{
    if (value > pow(2, input_prec)) {
        cout << endl;
        cout << "input value = " << value
             << ", 2^precision = " << pow(2, input_prec) << endl
             << "ERROR: Input value exceeds the input precision / Wrong number "
                "of input data"
             << endl;
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
