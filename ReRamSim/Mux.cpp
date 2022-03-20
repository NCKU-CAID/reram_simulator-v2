#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "Mux.h"

using namespace std;

Mux::Mux(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void Mux::Initialize(int _numInput, int _numSelection, double _resTg, bool _FPGA){
	//write our own design
}

void Mux::CalculateArea(double _newHeight, double _newWidth, AreaModify _option){
	//write our own design
}

void Mux::CalculateLatency(double _rampInput, double _capLoad, double numRead) {  // rampInput is from SL/BL, not fron EN signal
	//write our own design
}

void Mux::CalculatePower(double numRead) {
	//write our own design
}

void Mux::PrintProperty(const char* str) {
	//write our own design
}

void Mux::SaveOutput(const char* str) {
	//write our own design
}
