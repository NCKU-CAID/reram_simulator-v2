#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class Comparator: public FunctionUnit {
public:
	Comparator(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~Comparator() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void Initialize(int _numBit, int _numComparator);
	void CalculateUnitArea(AreaModify _option);
	void CalculateArea(double widthArray);
	void CalculateLatency(double _rampInput, double _capLoad, double numRead);
	void CalculatePower(double numRead, int numComparatorPerOperation);

	/* Properties */
	bool initialized;	/* Initialization flag */
	double capLoad;
	double capInvInput, capInvOutput, capNand2Input, capNand2Output, capNand3Input, capNand3Output;
	int numBit;
	int numComparator;
	double widthInvN, widthInvP, widthNand2N, widthNand2P, widthNand3N, widthNand3P;
	double rampInput, rampOutput;
    double areaUnit;
};

#endif /* COMPARATOR_H_ */
