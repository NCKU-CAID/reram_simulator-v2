#ifndef BITSHIFTER_H_
#define BITSHIFTER_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"
#include "DFF.h"

class BitShifter: public FunctionUnit {
public:
	BitShifter(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~BitShifter() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numUnit, int _numBit, double _clkFreq);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double numRead);
	void CalculatePower(double numRead);
	void CalculateUnitArea();

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numUnit;
	int numDff;
	int numBit;
	double clkFreq;

	DFF dff;
};

#endif /* BITSHIFTER_H_ */
