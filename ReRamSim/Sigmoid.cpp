#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "Sigmoid.h"

using namespace std;

Sigmoid::Sigmoid(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), mux(_inputParameter, _tech, _cell), muxDecoder(_inputParameter, _tech, _cell), wlDecoder(_inputParameter, _tech, _cell), colDecoder(_inputParameter, _tech, _cell), senseAmp(_inputParameter, _tech, _cell), colDecoderDriver(_inputParameter, _tech, _cell), voltageSenseAmp(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void Sigmoid::Initialize(bool _SRAM, int _numYbit, int _numEntry, int _numFunction, double _clkFreq) {
	//write our own design
}

void Sigmoid::CalculateUnitArea(AreaModify _option) {      // firstly calculate single sigmoid unit area
	//write our own design
}

void Sigmoid::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {     // assign multiple sigmoid unit to operate in parallel
	//write our own design
}

void Sigmoid::CalculateLatency(double numRead) {
	//write our own design
}

void Sigmoid::CalculatePower(double numRead) {
	//write our own design
}

void Sigmoid::PrintProperty(const char* str) {
	//write our own design
}

void Sigmoid::SaveOutput(const char* str) {
	//write our own design
}
