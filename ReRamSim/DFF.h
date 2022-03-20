#ifndef DFF_H_
#define DFF_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class DFF: public FunctionUnit {
public:
	DFF(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~DFF() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void PrintMagicProperty();
	void Initialize(int _numDff, double _clkFreq);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double numRead);
	void CalculatePower(double numRead, double numDffPerOperation);

	/* Properties */
	bool initialized;	/* Initialization flag */
	double capTgDrain, capTgGateN, capTgGateP, capInvInput, capInvOutput;
	int numDff;			/* Number of columns */
	double widthTgN, widthTgP, widthInvN, widthInvP;
	double rampInput, rampOutput;
	double clkFreq;
};

#endif /* DFF_H_ */
