#include "tile.h"
#include "cell.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

int separateBits(int value, int CellPrecision);

Tile::Tile(int Size, int cellType, int CellPrecision, float Area): size(Size){

	if(cellType==0&&CellPrecision>1){
		cout<<"ERROR: SRAM can only store one bit"<<endl;
		exit(1);
	}
	
	cellArray = new Cell*[Size];
	for(int i = 0; i < Size; ++i){
		cellArray[i] = new Cell[Size];
	}

	for(int i = 0; i < Size; ++i){
		for(int j = 0; j < Size; ++j){
			cellArray[i][j] = Cell(cellType, CellPrecision, Area);
			cellArray[i][j].setVoltage(0);
			cellArray[i][j].setEnable(0);
			cellArray[i][j].setValue(0);
		}

	}
}

Tile::~Tile(){ 
	for(int i = 0; i < size; ++i){
		delete[] cellArray[i];
	}
}

int Tile::getSize(){ return size; }

void Tile::enableRow(int row, bool enable){
	for (int j = 0; j < size; ++j){
		cellArray[row][j].setEnable(enable);
	}
}

void Tile::setRowVoltage(int row, float VDD){
	for (int j = 0; j < size; ++j){
		cellArray[row][j].setVoltage(VDD);
	}
}

void Tile::writeSingleWeight(int input, int row, int col){ // assuming that WLs are all on
	int CellPrecision = cellArray[row][col].getCellPrecision();
	if (input >= pow(2,CellPrecision))
		cout << "ERROR: The input value for the synapse at row " << row << " and column " << col << "exceed its cell precision" << endl;
	else
		cellArray[row][col].setValue(input);
}

void Tile::programWeights(string inFileName, int kernel_w, int kernel_h, int weight_precision){
	
	int CellPrecision = cellArray[0][0].getCellPrecision();
	int NumCellPerWeight = ceil(weight_precision/CellPrecision);
	int maxNumKernelPerColumn = int(floor(size/(kernel_h*kernel_w)));
	int maxNumWeightPerRow = int(floor(size/NumCellPerWeight));
	int kernelSize = kernel_w*kernel_h;

	ifstream inFile(inFileName, ios::in);
	if(!inFile){
		cerr << "Failed opening file" << endl;
		exit(1);
	}

	cout << "Weight precision = " << weight_precision<< endl;
	cout << "Cell precision = " << CellPrecision << endl;
	cout << "Number of cells per weight = " << NumCellPerWeight << endl;
	cout << "Kernel size = " << kernel_w << "x" << kernel_h<<endl;
	cout << "Maximum number of set of weights (kernels) stored per column = " << maxNumKernelPerColumn << endl;
	cout << "Maximum number of weights stored per row = " << maxNumWeightPerRow << endl;

	if (kernelSize>size){
		cout << "ERROR: Kernel size should be smaller than number of weights that can be stored in a column" << endl;
		exit(1);
	}
	
	int weight;
	int cellValue;
	int kernelCount = 1;
	int weightCount = 0;
	for(int col = 0; col < size; col = col+NumCellPerWeight){
		for(int row = 0; row < size; ++row){
			if(row == kernelSize){
				cout << "Finished programming "<< kernelCount << " kernel(s)"<<endl;	
				kernelCount++;
				if(size - row < kernelSize) // check if the remaining rows can accomodate the next kernel
					break;
			}
			inFile >> weight;
			if(inFile.eof())
				goto DONE;
			
			cout << endl << "[" << row << "][" << col <<"]: Weight " << weightCount << " = " << weight << endl;	
			for(int cell = 0; cell < NumCellPerWeight; ++cell){ //LSB -> MSB
				if(weight == 0)
					break;
				cellValue = separateBits(weight, CellPrecision);
				weight = weight >> CellPrecision;
				cellArray[row][cell+col].setValue(cellValue);
			}
			weightCount++;	
			
		}
	}

	DONE:
	cout << "Done programming all the weights" << endl;
	printWeightFloorPlan();

	

}

int separateBits(int value, int CellPrecision){
	int mask = pow(2, CellPrecision)-1;
	int cellValue = value & mask;
	// cout << "mask = "<< mask << endl;
	cout << "cell value = " << cellValue << endl;
	return cellValue;
}

void Tile::printWeightFloorPlan(){
	if (cellArray[0][0].getCellType() == 0)
		cout << "Cell Type = SRAM" << endl;
	else
		cout << "Cell Type = RRAM" << endl;

	cout << " \t";
	for(int j=0;j<size;++j){
		cout << j << "\t";
	}
	cout << endl;

	for(int i =0; i< size; ++i){
		cout << i << "\t";
		for(int j=0;j<size;++j){
			cout << cellArray[i][j].getValue() << "\t";
		}
		cout << endl;
	}
}


void Tile::computePartialSum(int col){
	
}

float Tile::getPower(float VGG){
	
}