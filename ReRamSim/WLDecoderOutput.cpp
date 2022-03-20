#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "WLDecoderOutput.h"

using namespace std;

WLDecoderOutput::WLDecoderOutput(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit(){
	initialized = false;
}

void WLDecoderOutput::Initialize(int _numWLRow, bool _multifunctional, bool _neuro) {
	//write our own design
}

void WLDecoderOutput::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void WLDecoderOutput::CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numRead, double numWrite) {
	//write our own design
}

void WLDecoderOutput::CalculatePower(double numRead, double numWrite) {
	//write our own design
}

void WLDecoderOutput::PrintProperty(const char* str) {
	//write our own design
}

void WLDecoderOutput::SaveOutput(const char* str) {
	//write our own design
}
