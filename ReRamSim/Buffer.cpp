#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "Buffer.h"
#include "Param.h"

using namespace std;

extern Param *param;


Buffer::Buffer(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), 
                      wlDecoder(_inputParameter, _tech, _cell), 
					  precharger(_inputParameter, _tech, _cell), 
					  sramWriteDriver(_inputParameter, _tech, _cell), 
					  senseAmp(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void Buffer::Initialize(int _numBit, int _interface_width, int _num_interface, double _unitWireRes, double _clkFreq, bool _SRAM){
	// Write our own design
}

void Buffer::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	// Write our own design
}

void Buffer::CalculateLatency(double numAccessBitRead, double numRead, double numAccessBitWrite, double numWrite){
	// Write our own design
}

void Buffer::CalculatePower(double numAccessBitRead, double numRead, double numAccessBitWrite, double numWrite) {
	// Write our own design
}

void Buffer::PrintProperty(const char* str) {
	// Write our own design
}
