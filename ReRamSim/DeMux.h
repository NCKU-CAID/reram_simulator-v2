#ifndef DEMUX_H_
#define DEMUX_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class DeMux: public FunctionUnit {
public:
	DeMux(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~DeMux() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void Initialize(int _numCol, int numRow);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double numRead);
	void CalculatePower(double numRead);
	//Mux & operator=(const Mux &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numInput;
	double widthInvN, widthInvP, widthTgN, widthTgP;
	double capInvInput, capInvOutput, capTgDrain, capTgGateN, capTgGateP;
	double resTg;
	//double avgNumVoltageIntegrate;
	double rampInput, rampOutput;
};

#endif /* DEMUX_H_ */
