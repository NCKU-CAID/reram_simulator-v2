#include <fstream>
#include <iostream>
#include "cell.h"
#include "conv.cpp"
#include "layer_conv.cpp"
#include "tile.h"
#include <boost/program_options.hpp>
using namespace std;
namespace BPO = boost::program_options;
#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

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
	int tileWidth,tileHeight,cellType,cellPrecision,kernelWidth,kernelHeight,kernelChannel, kernelNum, weightPrecision, inputPrecision, weightSign;
	int inputWidth, inputHeight;
	int stride, relu_on;
	string weightFileName,inputFileName, outputFileName;
	string ADC_V;
	string FileName;
	float ADCVoltage;
	
	try {
		BPO::options_description bOptions("Allowed Options");
		bOptions.add_options()("help,h","Produce help message")
							  ("tile_width,tw",BPO::value<int>(&tileWidth)->default_value(64)->value_name("power of 2"),"The width of a tile, default is 「64」")
							  ("tile_height,th",BPO::value<int>(&tileHeight)->default_value(64)->value_name("power of 2"),"The height of a tile, default is 「64」")
							  ("cell_type,ctype",BPO::value<int>(&cellType)->default_value(1)->value_name("0 or 1"),"Type of the cell, 0:SRAM, 1:RRAM, default is 「RRAM」")
							  ("cell_precision,cp",BPO::value<int>(&cellPrecision)->default_value(1)->value_name("1~8"), "Precision of a cell, default is 「1」")
							  // ("weight_file,wtfile",BPO::value<string>(&weightFileName)->required(), "Weight file after training")
	  					  	  ("kernel_width,kw",BPO::value<int>(&kernelWidth)->default_value(3)->value_name("1~5"),"The width of a kernel, default is 「3」")
							  ("kernel_height,kh",BPO::value<int>(&kernelHeight)->default_value(3)->value_name("1~5"),"The height of a kernel, must as same as kernel width, default is 「3」")
							  ("kernel_channel,kc",BPO::value<int>(&kernelChannel)->default_value(7)->value_name("1~7"),"The channel number of a kernel, default is 「7」")
							  ("kernel_number,kn",BPO::value<int>(&kernelNum)->default_value(2)->value_name("integer"),"The number of kernels, default is 「2」")
							  ("weight_precision,wp",BPO::value<int>(&weightPrecision)->default_value(8)->value_name("1~8"),"The precision of a weight, default is 「8」")
							  ("signed_weight,sw",BPO::value<int>(&weightSign)->default_value(2)->value_name("0, 1, or 2"),"The sign of weights, 0: unsigned, 1: signed (1's complement), 2: signed (2's complement), default is 「2」")
							  // ("input_file,infile",BPO::value<string>(&inputFileName)->required(),"Input file")
							  ("input_width,iw",BPO::value<int>(&inputWidth)->default_value(32)->value_name("integer"),"The width of an input featuremap, default is 「32」")
							  ("input_height,ih",BPO::value<int>(&inputHeight)->default_value(32)->value_name("integer"),"The height of an input featuremap, default is 「32」")
							  ("input_precision,inp",BPO::value<int>(&inputPrecision)->default_value(8)->value_name("1~8"),"The precision of a input feature, default is 「8」")
							  ("stride,s",BPO::value<int>(&stride)->default_value(1)->value_name("integer"),"The stride of the sliding window in convolution, default is 「1」")
							  // ("output_file,ofile",BPO::value<string>(&outputFileName)->required(),"Output file name")
							  ("files_list,file",BPO::value<string>(&FileName)->required(),"File that includes the list of input file and weight file")
							  ("ReLU",BPO::value<int>(&relu_on)->default_value(1),"1 to activate ReLU function, 0 to deactivate ReLU function")
							  ("ADC_voltage,vADC",BPO::value<string>(&ADC_V)->default_value("0.9")->value_name("0.7, 0.8 or 0.9"),"The voltage for ADC, default is 「0.9」");

								
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
	
	ADCVoltage = stof(ADC_V);

	cout << "--------------The arguments you setup in this simulation--------------" << endl;

	cout << "Tile Width is: " << tileWidth << endl;
	cout << "Tile height is: " << tileHeight << endl;
	if(cellType){
		cout << "Cell type is 「ReRAM」" <<endl;
	}
	else {
		cout << "Cell type is 「SRAM」" << endl;
	}
	cout << "Tile Cell precision is: " << cellPrecision << " bit(s)" << endl;
	cout << "The width of input featuremap is: " << inputWidth << endl;
	cout << "The height of input featuremap is: " << inputHeight << endl;
	cout << "The kernel width is: " << kernelWidth << endl;
	cout << "The kernel height is: " << kernelHeight << endl;
	cout << "The channel number of a kernel/input is: " << kernelChannel << endl;
	cout << "The number of total kernels is: " << kernelNum << endl;
	cout << "The precision of a weight is: " << weightPrecision << " bit(s)" << endl;
	if(weightSign)
		cout << "Weights are signed values with " << weightSign << "'s complement" << endl;
	else
		cout << "Weights are unsigned values" << endl;
	cout << "The precision of a input feature is: " << inputPrecision << " bit(s)" << endl;
	cout << "The ADC voltage is: " << ADCVoltage << "V" << endl;

	cout << "---------------------------------------------------------------------" << endl;
	
	// cout << "-----------------Input File and Output File Name---------------------" << endl;

	// cout << "The weight file name is: " << weightFileName << endl;
	// cout << "The input file name is: " << inputFileName << endl;
	// cout << "The output file name is: " << outputFileName << endl;

	// cout << "---------------------------------------------------------------------" << endl;

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
	

	// cout << "---------------------Start Programming Weights-----------------------" << endl;
    Tile tile(tileWidth, tileHeight, cellType, cellPrecision);
    // tile.programWeights(weightFileName, kernelWidth, kernelHeight,kernelChannel, weightPrecision);
	// cout << "---------------------Programming Weights Finish----------------------" << endl;
            
	Tile &tileref = tile;
	float ADC_power = 0;
    // matrixMultiplication(inpuFileName, inputPrecision, tileref, kernelWidth,kernelHeight, kernelChannel, weightPrecision, weightSign, mat_result, ADCVoltage, ADC_power,relu_on, kernelNum);
    convolution(tileref, FileName, inputWidth, inputHeight, inputPrecision, kernelWidth,kernelHeight, kernelChannel, kernelNum, weightPrecision, stride, weightSign, relu_on, ADCVoltage, ADC_power, "ExampleLayer");
    cout << "_____________________________________END LAYER CONVOLUTION__________________________________________"<< endl;
    cout << "ADC total power = " << ADC_power << "E-05 (W)"<< endl;
    

    return 0;
}
