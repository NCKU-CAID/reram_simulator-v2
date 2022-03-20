#ifndef BUFFER_H_
#define BUFFER_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"
#include "RowDecoder.h"
#include "Precharger.h"
#include "SenseAmp.h"
#include "SRAMWriteDriver.h"

using namespace std;

class Buffer: public FunctionUnit {
public:
	Buffer(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~Buffer() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void PrintMagicProperty();
	void Initialize(int _numBit, int _interface_width, int _num_interface, double _unitWireRes, double _clkFreq, bool _SRAM);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double numAccessBit, double numRead, double numAccessBitWrite, double numWrite);
	void CalculatePower(double numAccessBit, double numRead, double numAccessBitWrite, double numWrite);

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numBit, interface_width, num_interface;
	double unitWireRes, clkFreq, lengthRow, lengthCol, memoryArea, hDff, wDff, colDelay;
	bool DDR, givenClkFreq, SRAM;

	double capTgDrain, capTgGateN, capTgGateP, capInvInput, capInvOutput;
	double widthInvN, widthInvP, widthTgN, widthTgP, hDffInv, wDffInv;
	double rampInput, rampOutput;
	double readWholeLatency, writeWholeLatency, avgBitReadLatency, avgBitWriteLatency;
	double dffDynamicEnergy, readWholeDynamicEnergy, writeWholeDynamicEnergy, avgBitReadDynamicEnergy, avgBitWriteDynamicEnergy;
	
	/* Circuit Modules */
	RowDecoder  wlDecoder;
	Precharger precharger;
	SRAMWriteDriver sramWriteDriver;
	SenseAmp senseAmp;
};

#endif /* BUFFER_H_ */
