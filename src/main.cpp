#include <fstream>
#include <iostream>
#include "cell.h"
#include "conv.cpp"
#include "tile.h"
#include <boost/program_options.hpp>
using namespace std;
namespace BPO = boost::program_options;

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
	int tileWidth,tileHeight,cellType,cellPrecision,kernelWidth,kernelHeight,kernelChannel,weightPrecision,inputPrecision;
	string weightFileName,inputFileName, outputFileName;
	
	try {
		BPO::options_description bOptions("Allowed Options");
		bOptions.add_options()("help,h","Produce help message")
							  ("tile_width,tw",BPO::value<int>(&tileWidth)->default_value(16)->value_name("power of 2"),"The width of a tile, default is 「16」")
							  ("tile_height,th",BPO::value<int>(&tileHeight)->default_value(64)->value_name("power of 2"),"The height of a tile, default is 「64」")
							  ("cell_type,ctype",BPO::value<int>(&cellType)->default_value(1)->value_name("0 or 1"),"Type of the cell, 0:SRAM, 1:RRAM, default is 「RRAM」")
							  ("cell_precision,cp",BPO::value<int>(&cellPrecision)->default_value(4)->value_name("1~8"), "Precision of a cell, default is 「4」")
							  ("weight_file,wtfile",BPO::value<string>(&weightFileName)->required(), "Weight file after training")
	  					  	  ("kernel_width,kw",BPO::value<int>(&kernelWidth)->default_value(3)->value_name("1~5"),"The width of a kernel, default is 「3」")
							  ("kernel_height,kh",BPO::value<int>(&kernelHeight)->default_value(3)->value_name("1~5"),"The height of a kernel, must as same as kernel width, default is 「3」")
							  ("kernel_channel,kc",BPO::value<int>(&kernelChannel)->default_value(7)->value_name("1~7"),"The channel number of a kernel, default is 「7」")
							  ("weight_precision,wp",BPO::value<int>(&weightPrecision)->default_value(8)->value_name("1~8"),"The precision of a weight, default is 「8」")
							  ("input_file,infile",BPO::value<string>(&inputFileName)->required(),"Input file")
							  ("input_precision,inp",BPO::value<int>(&inputPrecision)->default_value(8)->value_name("1~8"),"The precision of a input feature, default is 「8」")
							  ("output_file,ofile",BPO::value<string>(&outputFileName)->required(),"Output file name");
	
		BPO::variables_map mVMap;
		BPO::store(BPO::parse_command_line(argc,argv,bOptions),mVMap);
	
		if(mVMap.count("help")){
			cout << bOptions << endl;
			return 0;
		}

		BPO::notify(mVMap);
	} 
	catch(BPO::error& e){
		cout << "Error: " << e.what() <<endl;
		return 1;
	}
	catch (exception& e){
		cout << "Error: " << e.what() << endl;
		return 1;
	}

	cout << "--------------The arguments you setup in this simulation--------------" << endl;

	cout << "Tile Width is: " << tileWidth << endl;
	cout << "Tile height is: " << tileHeight << endl;
	if(cellType){
		cout << "Cell type is 「ReRAM」" <<endl;
	}
	else {
		cout << "Cell type is 「SRAM」" << endl;
	}
	cout << "Tile Cell precision is: " << cellPrecision << " bits" << endl;
	cout << "The kernel width is: " << kernelWidth << endl;
	cout << "The kernel height is: " << kernelHeight << endl;
	cout << "The channel number of a kernel is: " << kernelChannel << endl;
	cout << "The precision of a weight is: " << weightPrecision << " bits" << endl;
	cout << "The precision of a input feature is: " << inputPrecision << " bits" << endl;

	cout << "---------------------------------------------------------------------" << endl;
	
	cout << "-----------------Input File and Output File Name---------------------" << endl;

	cout << "The weight file name is: " << weightFileName << endl;
	cout << "The input file name is: " << inputFileName << endl;
	cout << "The output file name is: " << outputFileName << endl;

	cout << "---------------------------------------------------------------------" << endl;

	// int tileWidth = atoi(argv[1]);
	// int tileHeight = atoi(argv[2]);
    // int cellType = atoi(argv[3]);
	// int cellPrecision = atoi(argv[4]);
	// string weightFileName = argv[5];
    // int kernelWidth = atoi(argv[6]);
	// int kernelHeight = atoi(argv[7]);
    // int kernelChannel = atoi(argv[8]);
	// int weightPrecision = atoi(argv[9]);
    // string inputFileName = argv[10];
	// int inputPrecision = atoi(argv[11]);
    // string outputFileName = argv[12];
	

	cout << "---------------------Start Programming Weights-----------------------" << endl;
    Tile tile(tileWidth, tileHeight, cellType, cellPrecision);
    tile.programWeights(weightFileName, kernelWidth, kernelHeight,kernelChannel, weightPrecision);
	cout << "---------------------Programming Weights Finish----------------------" << endl;
	Tile &tileref = tile;
    matrixMultiplication(inputFileName, inputPrecision, tileref, kernelWidth,kernelHeight, kernelChannel, weightPrecision,outputFileName);
    return 0;
}
