#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "WLNewDecoderDriver.h"

using namespace std;

WLNewDecoderDriver::WLNewDecoderDriver(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit(){
	initialized = false;
	invalid = false;
	//inputParameter = _inputParameter;
	//tech = _tech;
	//cell = _cell;
}

WLNewDecoderDriver::~WLNewDecoderDriver() {
	// TODO Auto-generated destructor stub
}

void WLNewDecoderDriver::Initialize(int _numWLRow) {
	//write our own design
}

void WLNewDecoderDriver::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void WLNewDecoderDriver::CalculateLatency(double _rampInput, double _capLoad, double _resLoad, double numRead, double numWrite) {
	//write our own design
}

void WLNewDecoderDriver::CalculatePower(double numRead, double numWrite) {
	//write our own design
}

void WLNewDecoderDriver::PrintProperty(const char* str) {
	//write our own design
}

void WLNewDecoderDriver::SaveOutput(const char* str) {
	//write our own design
}
