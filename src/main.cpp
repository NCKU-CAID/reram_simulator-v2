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
kernel channel,
weight precision,

input file name,
input precision

output file name

*/

// e.g., ./main 16 64 1 4 ./test/weight64.txt 3 3 7 8 ./test/data64.txt 8
// result64.txt



int main(int argc, char const *argv[])
{
    int tileWidth = atoi(argv[1]);
    int tileHeight = atoi(argv[2]);
    int cellType = atoi(argv[3]);
    int cellPrecision = atoi(argv[4]);
    string weightFileName = argv[5];
    int kernelWidth = atoi(argv[6]);
    int kernelHeight = atoi(argv[7]);
    int kernelChannel = atoi(argv[8]);
    int weightPrecision = atoi(argv[9]);
    string inputFileName = argv[10];
    int inputPrecision = atoi(argv[11]);
    string outputFileName = argv[12];


    Tile tile(tileWidth, tileHeight, cellType, cellPrecision);

    tile.programWeights(weightFileName, kernelWidth, kernelHeight,
                        kernelChannel, weightPrecision);

    Tile &tileref = tile;

    matrixMultiplication(inputFileName, inputPrecision, tileref, kernelWidth,
                         kernelHeight, kernelChannel, weightPrecision,
                         outputFileName);

    return 0;
}