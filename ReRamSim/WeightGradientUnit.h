#ifndef WEIGHTGRADIENTUNIT_H_
#define WEIGHTGRADIENTUNIT_H_

#include <vector>
#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "formula.h"
#include "FunctionUnit.h"
#include "Adder.h"
#include "AdderTree.h"
#include "RowDecoder.h"
#include "Mux.h"
#include "DFF.h"
#include "Precharger.h"
#include "SenseAmp.h"
#include "SRAMWriteDriver.h"
#include "SwitchMatrix.h"
#include "ShiftAdd.h"
#include "MultilevelSenseAmp.h"
#include "MultilevelSAEncoder.h"

using namespace std;

class WeightGradientUnit: public FunctionUnit {
public:
	WeightGradientUnit(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~WeightGradientUnit() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numMemRow, int _numMemCol);
	void CalculateArea();
	void CalculateLatency(int numRead, int numBitDataLoad);
	void CalculatePower(int numRead, int numBitDataLoad);

	/* Properties */	
	bool initialized;	   // Initialization flag
	int numRow;			   // Number of rows
	int numCol;			   // Number of columns
	
	int numMemRow;         // total memory size needed to support calculation
	int numMemCol;         // total memory size needed to support calculation
	
	int numArrayInRow;           
	int numArrayInCol;
	int outPrecision;
	
	double unitWireRes, lengthRow, lengthCol, capRow1, capRow2, capCol, resRow, resCol, resCellAccess, capCellAccess, colDelay, capSRAMCell;
	double heightArray;
	double widthArray;
	double areaArray, areaSubArray;
	double readDynamicEnergyArray, writeDynamicEnergyArray;
	double writeLatencyArray;
	double readLatencyPeak, writeLatencyPeak, readDynamicEnergyPeak, writeDynamicEnergyPeak;
	
	SpikingMode spikingMode;	
	
	
	/* Circuit modules */
	RowDecoder                   wlDecoder;
	SwitchMatrix                 wlSwitchMatrix;
	Mux                          mux;
	RowDecoder                   muxDecoder;
	Precharger                   precharger;
	SenseAmp                     senseAmp;
	SRAMWriteDriver              sramWriteDriver;
	DFF                          dff;
	Adder                        adder;
	MultilevelSenseAmp           multilevelSenseAmp;
	MultilevelSAEncoder          multilevelSAEncoder;
	ShiftAdd                     shiftAdd;
	AdderTree					 accumulation;
	DFF							 bufferInput;
	DFF							 bufferOutput;
};

#endif /* WEIGHTGRADIENTUNIT_H_ */
