#ifndef TILE_H_
#define TILE_H_
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"

using namespace std;

/*** Functions ***/
void TileInitialize(InputParameter& inputParameter, Technology& tech, MemCell& cell, double _numPENM, double _peSizeNM, double _numPECM, double _peSizeCM);
vector<double> TileCalculateArea(double numPE, double peSize, bool NMTile, double *height, double *width);
void TileCalculatePerformance(const vector<vector<double> > &newMemory, const vector<vector<double> > &oldMemory, const vector<vector<double> > &inputVector, 
			int novelMap, double numPE, double peSize, 
			int speedUpRow, int speedUpCol, int weightMatrixRow, int weightMatrixCol, int numInVector, 
			Technology& tech, MemCell& cell, double *readLatency, double *readDynamicEnergy, double *leakage,
			double *readLatencyAG, double *readDynamicEnergyAG, double *writeLatencyWU, double *writeDynamicEnergyWU,
			double *bufferLatency, double *bufferDynamicEnergy, double *icLatency, double *icDynamicEnergy,
			double *coreLatencyADC, double *coreLatencyAccum, double *coreLatencyOther, double *coreEnergyADC, 
			double *coreEnergyAccum, double *coreEnergyOther, double *readLatencyPeakFW, double *readDynamicEnergyPeakFW,
			double *readLatencyPeakAG, double *readDynamicEnergyPeakAG, double *writeLatencyPeakWU, double *writeDynamicEnergyPeakWU);
		
vector<vector<double> > CopyPEArray(const vector<vector<double> > &orginal, int positionRow, int positionCol, int numRow, int numCol);
vector<vector<double> > CopyPEInput(const vector<vector<double> > &orginal, int positionRow, int numInputVector, int numRow);
	

#endif /* TILE_H_ */
