#ifndef SRAMNEWSA_H_
#define SRAMNEWSA_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class SramNewSA: public FunctionUnit {
public:
	SramNewSA(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~SramNewSA() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void Initialize(int _numCol, int _levelOutput);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double numRead);
	void CalculatePower(double numRead);

	/* Properties */
	bool initialized;		/* Initialization flag */
	int numCol;				/* Number of columns */
	int levelOutput;	

};

#endif /* SRAMNEWSA_H_ */
