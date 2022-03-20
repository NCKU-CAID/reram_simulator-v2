#ifndef DRAM_H_
#define DRAM_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class DRAM: public FunctionUnit {
public:
	DRAM(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~DRAM() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void Initialize(int DRAMtype);
	void CalculateLatency(double numRead);
	void CalculatePower(double numRead);

	/* Properties */
	bool initialized;	/* Initialization flag */
	double bandwidth, energyperbit;
};

#endif /* BUS_H_ */
