#include <cmath>
#include <iostream>
#include "constant.h"
#include "typedef.h"
#include "formula.h"
#include "Adder.h"

using namespace std;

Adder::Adder(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void Adder::Initialize(int _numBit, int _numAdder){
	/*-----write our own design-----*/
}

void Adder::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	/*-----write our own design-----*/
}

void Adder::CalculateLatency(double _rampInput, double _capLoad, double numRead){
	/*-----write our own design-----*/
}

void Adder::CalculatePower(double numRead, int numAdderPerOperation) {
	/*-----write our own design-----*/
}

void Adder::PrintProperty(const char* str) {
	/*-----write our own design-----*/
}

void Adder::SaveOutput(const char* str) {
	/*-----write our own design-----*/
}
