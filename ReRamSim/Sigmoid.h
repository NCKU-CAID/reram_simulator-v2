#ifndef SIGMOID_H_
#define SIGMOID_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"
#include "Adder.h"
#include "DFF.h"
#include "RowDecoder.h"
#include "Mux.h"
#include "DecoderDriver.h"
#include "VoltageSenseAmp.h"
#include "SenseAmp.h"

class Sigmoid: public FunctionUnit {
public:
	Sigmoid(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~Sigmoid() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void Initialize(bool _SRAM, int _numYbit, int _numEntry, int _numFunction, double _clkFreq);
	void CalculateUnitArea(AreaModify _option);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double numRead);
	void CalculatePower(double numRead);

	/* Properties */
	bool initialized;	/* Initialization flag */
	bool SRAM;
	int numYbit, numEntry;
	int numFunction;         // # of sigmoid functions that can be processed in parallel
	double senseVoltage;     // senseAmp voltage
	int numCell;
	double clkFreq;
	double capSRAMCell, capLoad;
	double widthInvN, widthInvP;
	double hUnit, wUnit, areaUnit;

	RowDecoder muxDecoder;
	Mux mux;
	RowDecoder wlDecoder;
	SenseAmp senseAmp;
	RowDecoder colDecoder;
	DecoderDriver colDecoderDriver;
	VoltageSenseAmp voltageSenseAmp;
};

#endif /* SIGMOID_H_ */
