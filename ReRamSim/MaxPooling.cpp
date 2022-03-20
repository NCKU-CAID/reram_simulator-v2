#include <iostream>
#include "constant.h"
#include "formula.h"
#include "MaxPooling.h"


using namespace std;

MaxPooling::MaxPooling(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), comparator(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void MaxPooling::Initialize(int _numBit, int _window, int _numMaxPooling) {    // able to assign multiple MPU to operate in parallel
	//write our own design
}

void MaxPooling::CalculateUnitArea(AreaModify _option) {
	//write our own design
}

void MaxPooling::CalculateArea(double widthArray){
	//write our own design
}

void MaxPooling::CalculateLatency(double _rampInput, double _capLoad, double numRead){
	//write our own design
}

void MaxPooling::CalculatePower(double numRead) {
	//write our own design
}

void MaxPooling::PrintProperty(const char* str) {
	//write our own design
}
