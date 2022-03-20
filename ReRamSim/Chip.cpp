#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "MaxPooling.h"
#include "Sigmoid.h"
#include "BitShifter.h"
#include "AdderTree.h"
#include "Buffer.h"
#include "HTree.h"
#include "DRAM.h"
#include "ProcessingUnit.h"
#include "Tile.h"
#include "WeightGradientUnit.h"
#include "constant.h"
#include "formula.h"
#include "Param.h"
#include "Chip.h"
#include "Adder.h"

using namespace std;

extern Param *param;
double globalBusWidth = 0;
int numBufferCore = 0;

/*** Circuit Modules ***/
Buffer *globalBuffer;
HTree *GhTree;
AdderTree *Gaccumulation;
Sigmoid *Gsigmoid;
BitShifter *GreLu;
MaxPooling *maxPool;
DRAM *dRAM;
WeightGradientUnit *weightGradientUnit;
Adder *gradientAccum;

vector<int> ChipDesignInitialize(InputParameter& inputParameter, Technology& tech, MemCell& cell, bool pip, const vector<vector<double> > &netStructure,
					double *maxPESizeNM, double *maxTileSizeCM, double *numPENM){
	//write our own design
}

vector<vector<double> > ChipFloorPlan(bool findNumTile, bool findUtilization, bool findSpeedUp, const vector<vector<double> > &netStructure, const vector<int > &markNM,
					double maxPESizeNM, double maxTileSizeCM, double numPENM, const vector<int> &pipelineSpeedUp,
					double *desiredNumTileNM, double *desiredPESizeNM, double *desiredNumTileCM, double *desiredTileSizeCM, double *desiredPESizeCM, int *numTileRow, int *numTileCol) {
	//write our own design
}

void ChipInitialize(InputParameter& inputParameter, Technology& tech, MemCell& cell, const vector<vector<double> > &netStructure, const vector<int > &markNM, const vector<vector<double> > &numTileEachLayer, 
		double numPENM, double desiredNumTileNM, double desiredPESizeNM, double desiredNumTileCM, double desiredTileSizeCM, double desiredPESizeCM, int numTileRow, int numTileCol, int *numArrayWriteParallel) { 
	//write our own design
}

vector<double> ChipCalculateArea(InputParameter& inputParameter, Technology& tech, MemCell& cell, double desiredNumTileNM, double numPENM, double desiredPESizeNM, double desiredNumTileCM, double desiredTileSizeCM,
						double desiredPESizeCM, int numTileRow, double *height, double *width, double *CMTileheight, double *CMTilewidth, double *NMTileheight, double *NMTilewidth) {
	//write our own design
}

double ChipCalculatePerformance(InputParameter& inputParameter, Technology& tech, MemCell& cell, int layerNumber, const string &newweightfile, const string &oldweightfile, const string &inputfile, bool followedByMaxPool,
							const vector<vector<double> > &netStructure, const vector<int> &markNM, const vector<vector<double> > &numTileEachLayer, const vector<vector<double> > &utilizationEachLayer,
							const vector<vector<double> > &speedUpEachLayer, const vector<vector<double> > &tileLocaEachLayer, double numPENM, double desiredPESizeNM, double desiredTileSizeCM,
							double desiredPESizeCM, double CMTileheight, double CMTilewidth, double NMTileheight, double NMTilewidth, int numArrayWriteParallel,
							double *readLatency, double *readDynamicEnergy, double *leakage, double *readLatencyAG, double *readDynamicEnergyAG, double *readLatencyWG, double *readDynamicEnergyWG,
							double *writeLatencyWU, double *writeDynamicEnergyWU, double *bufferLatency, double *bufferDynamicEnergy, double *icLatency, double *icDynamicEnergy, double *coreLatencyADC,
							double *coreLatencyAccum, double *coreLatencyOther, double *coreEnergyADC, double *coreEnergyAccum, double *coreEnergyOther, double *dramLatency, double *dramDynamicEnergy,
							double *readLatencyPeakFW, double *readDynamicEnergyPeakFW, double *readLatencyPeakAG, double *readDynamicEnergyPeakAG, double *readLatencyPeakWG, double *readDynamicEnergyPeakWG,
							double *writeLatencyPeakWU, double *writeDynamicEnergyPeakWU) {
	//write our own design
}

vector<double> TileDesignCM(double tileSize, const vector<int > &markNM, const vector<vector<double> > &netStructure, int numRowPerSynapse, int numColPerSynapse) {
	//write our own design
}

vector<double> TileDesignNM(double peSize, const vector<int > &markNM, const vector<vector<double> > &netStructure, int numRowPerSynapse, int numColPerSynapse, double numPENM){
	//write our own design
}
vector<vector<double> > PEDesign(bool Design, double peSize, double desiredTileSize, double numTileTotal, const vector<int > &markNM, const vector<vector<double> > &netStructure, int numRowPerSynapse, int numColPerSynapse) {
	//write our own design
}

vector<vector<double> > SubArrayDup(double desiredPESizeCM, double desiredPESizeNM, const vector<int > &markNM, const vector<vector<double> > &netStructure, int numRowPerSynapse, int numColPerSynapse) {
	//write our own design
}

vector<vector<double> > OverallEachLayer(bool utilization, bool speedUp, const vector<vector<double> > &peDup, const vector<vector<double> > &subArrayDup, const vector<int> &pipelineSpeedUp, double desiredTileSizeCM,
										double desiredPESizeNM, const vector<int > &markNM, const vector<vector<double> > &netStructure, int numRowPerSynapse, int numColPerSynapse, double numPENM) {
	//write our own design
}

vector<vector<double> > LoadInWeightData(const string &weightfile, int numRowPerSynapse, int numColPerSynapse, double maxConductance, double minConductance) {
	//write our own design
}

vector<vector<double> > CopyArray(const vector<vector<double> > &orginal, int positionRow, int positionCol, int numRow, int numCol) {
	//write our own design
}

vector<vector<double> > ReshapeArray(const vector<vector<double> > &orginal, int positionRow, int positionCol, int numRow, int numCol, int numPE, int weightMatrixRow) {
	//write our own design
}

vector<vector<double> > LoadInInputData(const string &inputfile) {
	//write our own design
}

vector<vector<double> > CopyInput(const vector<vector<double> > &orginal, int positionRow, int numInputVector, int numRow) {
	//write our own design
}

vector<vector<double> > ReshapeInput(const vector<vector<double> > &orginal, int positionRow, int numInputVector, int numRow, int numPE, int weightMatrixRow) {
	//write our own design
}
