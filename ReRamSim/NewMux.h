#ifndef NEWMUX_H_
#define NEWMUX_H_

#include "FunctionUnit.h"
#include "constant.h"
#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"

class NewMux: public FunctionUnit {
public:
	NewMux(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numOutput);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double _capLoad, double numRead, double numWrite);
	void CalculatePower(double numRead, double numWrite, double numWritePulse, int mode_1T1R, double activityRowRead, double activityColWrite) ;

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numInput;
	double capLoad;
	double widthTgN, widthTgP;
	double TgHeight, TgWidth;
	double capTgDrain, capTgGateN, capTgGateP;
	double resTg;
	double rampInput, rampOutput;
	int numRowTgPair;

};

#endif /* NEWMUX_H_ */
