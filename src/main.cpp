#include <fstream>
#include <iostream>
#include "cell.h"
#include "conv.cpp"
#include "tile.h"
using namespace std;

/* INPUT FORMAT

tile width,
tile height,
cell type (0:SRAM, 1:RRAM),
cell precision,
weight file name,
kernel width,
kernel height,
weight precision,

input file name,
input precision

output file name

*/

// e.g., ./main 4 16 1 4 temp_weight 3 3 8 temp_input 2 temp_output
// e.g., ./main 4 18 1 4 temp_weight 3 3 8 temp_input 3 temp_output



int main(int argc, char const *argv[])
{
    int tileWidth = atoi(argv[1]);
    int tileHeight = atoi(argv[2]);
    int cellType = atoi(argv[3]);
    int cellPrecision = atoi(argv[4]);
    string weightFileName = argv[5];
    int kernelWidth = atoi(argv[6]);
    int kernelHeight = atoi(argv[7]);
    int weightPrecision = atoi(argv[8]);
    string inputFileName = argv[9];
    int inputPrecision = atoi(argv[10]);
    string outputFileName = argv[11];


    Tile tile(tileWidth, tileHeight, cellType, cellPrecision);

    ofstream outfile("temp_weight", ios::out);  // 4-bit weight
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    
    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    outfile.close();

    tile.programWeights(weightFileName, kernelWidth, kernelHeight,
                        weightPrecision);



    // input file
    ofstream outfile_i("temp_input", ios::out);  // 2-bit input
    if (!outfile_i) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    outfile_i << 1 << "\t" << 2 << "\t" << 3 << "\t" << 1 << "\t" << 2 << "\t"
              << 3 << "\t" << 1 << "\t" << 2 << "\t" << 3 << endl;

    outfile_i << 2 << "\t" << 4 << "\t" << 6 << "\t" << 2 << "\t" << 4 << "\t"
              << 6 << "\t" << 2 << "\t" << 4 << "\t" << 6 << endl;
    outfile_i.close();

    convolution(inputFileName, inputPrecision, tile, kernelWidth, kernelHeight,
                weightPrecision, outputFileName);

    return 0;
}