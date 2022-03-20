#ifndef MAXPOOLING_H_
#define MAXPOOLING_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"
#include "Comparator.h"

class MaxPooling: public FunctionUnit {
public:
	MaxPooling(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~MaxPooling() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numBit, int _window, int _numMaxPooling);
	void CalculateUnitArea(AreaModify _option);
	void CalculateArea(double widthArray);
	void CalculateLatency(double _rampInput, double _capLoad, double numRead);
	void CalculatePower(double numRead);

	/* Properties */
	bool initialized;	/* Initialization flag */
	double capLoad;
	double capInvInput, capInvOutput, capNandInput, capNandOutput, capNorInput, capNorOutput, capNor2Input, capNor2Output;
	int numBit, window, numMaxPooling, numStage;
	int numComparator;
	double widthInvN, widthInvP, widthNandN, widthNandP, widthNorN, widthNorP, widthNorN2, widthNorP2;
	double rampInput;
    double areaUnit;
	
	Comparator comparator;
};

#endif /* MAXPOOLING_H_ */
