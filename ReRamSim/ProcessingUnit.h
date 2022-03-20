#ifndef PROCESSINGUNIT_H_
#define PROCESSINGUNIT_H_
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "SubArray.h"
 
/*** Functions ***/
void ProcessingUnitInitialize(SubArray *& subArray, InputParameter& inputParameter, Technology& tech, MemCell& cell, int _numSubArrayRowNM, int _numSubArrayColNM, int _numSubArrayRowCM, int _numSubArrayColCM);
vector<double> ProcessingUnitCalculateArea(SubArray *subArray, int numSubArrayRow, int numSubArrayCol, bool NMpe, double *height, double *width, double *bufferArea);
double ProcessingUnitCalculatePerformance(SubArray *subArray, Technology& tech, MemCell& cell, bool NMpe, 
										const vector<vector<double> > &newMemory, const vector<vector<double> > &oldMemory, const vector<vector<double> > &inputVector, 
										int arrayDupRow, int arrayDupCol, int numSubArrayRow, int numSubArrayCol, int weightMatrixRow, int weightMatrixCol, 
										int numInVector, double *readLatency, double *readDynamicEnergy, double *leakage, 
										double *readLatencyAG, double *readDynamicEnergyAG, double *writeLatencyWU, double *writeDynamicEnergyWU,
										double *bufferLatency, double *bufferDynamicEnergy, double *icLatency, double *icDynamicEnergy,
										double *coreLatencyADC, double *coreLatencyAccum, double *coreLatencyOther, double *coreEnergyADC, 
										double *coreEnergyAccum, double *coreEnergyOther, double *readLatencyPeakFW, double *readDynamicEnergyPeakFW,
										double *readLatencyPeakAG, double *readDynamicEnergyPeakAG, double *readLatencyPeakWU, double *readDynamicEnergyPeakWU);

vector<vector<double> > CopySubArray(const vector<vector<double> > &orginal, int positionRow, int positionCol, int numRow, int numCol);
vector<vector<double> > CopySubInput(const vector<vector<double> > &orginal, int positionRow, int numInputVector, int numRow);
vector<double> GetInputVector(const vector<vector<double> > &input, int numInput, double *activityRowRead);
vector<double> GetColumnResistance(const vector<double> &input, const vector<vector<double> > &weight, MemCell& cell, bool parallelRead, double resCellAccess);
vector<double> GetRowResistance(const vector<double> &input, const vector<vector<double> > &weight, MemCell& cell, bool parallelRead, double resCellAccess);
double GetWriteUpdateEstimation(SubArray *subArray, Technology& tech, MemCell& cell, const vector<vector<double> > &newMemory, const vector<vector<double> > &oldMemory, double *activityColWrite, double *activityRowWrite,
								int *numWritePulseAVG, int *totalNumWritePulse, double *writeDynamicEnergyArray);

#endif /* PROCESSINGUNIT_H_ */
