#ifndef SRAMWRITEDRIVER_H_
#define SRAMWRITEDRIVER_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class SRAMWriteDriver: public FunctionUnit {
public:
	SRAMWriteDriver(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~SRAMWriteDriver() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numCol, double _activityColWrite, int _numWriteCellPerOperationNeuro);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numWrite);
	void CalculatePower(double numWrite);

	/* Properties */
	bool initialized;	/* Initialization flag */
	double capLoad, resLoad;
	double capInvInput, capInvOutput;
	int numCol;			/* Number of columns */
	double widthInvN, widthInvP;
	double rampInput, rampOutput;
	double activityColWrite;
	int numWriteCellPerOperationNeuro;
};

#endif /* SRAMWRITEDRIVER_H_ */
