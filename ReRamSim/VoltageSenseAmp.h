#ifndef VOLTAGESENSEAMP_H_
#define VOLTAGESENSEAMP_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class VoltageSenseAmp: public FunctionUnit {
public:
	VoltageSenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~VoltageSenseAmp() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numReadCol, double _clkFreq);
	void CalculateArea(double _layoutWidth);
	void CalculateLatency(double capInputLoad, double numRead);
	void CalculatePower(double numRead);
	void CalculateUnitArea();

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numReadCol;
	double widthNmos, widthPmos;
	double widthVoltageSenseAmp;
	double rampInput, rampOutput;
	double voltageSenseDiff;
	double resPrecharge;
	double capNmosGate, capNmosDrain, capPmosGate, capPmosDrain;
	double capS1;
	double areaUnit;
	double clkFreq;
};

#endif /* VOLTAGESENSEAMP_H_ */
