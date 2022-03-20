#ifndef SENSEAMP_H_
#define SENSEAMP_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class SenseAmp: public FunctionUnit {
public:
	SenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~SenseAmp() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numCol, bool _currentSense, double _senseVoltage /* Unit: V */, double _pitchSenseAmp, double _clkFreq, int _numReadCellPerOperationNeuro);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double numRead);
	void CalculatePower(double numRead);

	/* Properties */
	bool initialized;		/* Initialization flag */
	int numCol;				/* Number of columns */
	bool currentSense;		/* Whether the sensing scheme is current-based */
	double senseVoltage;	/* Minimum sensible voltage */
	double capLoad;			/* Load capacitance of sense amplifier */
	double pitchSenseAmp;	/* The maximum width allowed for one sense amplifier layout */

	double clkFreq;
	int numReadCellPerOperationNeuro;
};

#endif /* SENSEAMP_H_ */
