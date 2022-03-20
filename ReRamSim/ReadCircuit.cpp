#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "ReadCircuit.h"

using namespace std;

ReadCircuit::ReadCircuit(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void ReadCircuit::Initialize(ReadCircuitMode _mode, int _numReadCol, int _maxNumIntBit, SpikingMode _spikingMode, double _clkFreq) {
	//write our own design
}

void ReadCircuit::CalculateUnitArea() {
	//write our own design
}

void ReadCircuit::CalculateArea(double _newWidth) {	// Just add up the area of all the components
	//write our own design
}

void ReadCircuit::CalculateLatency(double numRead) {
	//write our own design
}

void ReadCircuit::CalculatePower(double numof1, double numof2, double numof3, double numof4, double numof5, double numof6, double numof7, double numof8, double numof9, double numof10, double numof20, double numof30, double numof40, double numof50, double numof60, double numof70, double numof80, double numof90, double numof100, double numRead) {
	//write our own design
}

void ReadCircuit::PrintProperty(const char* str) {
	//write our own design
}

void ReadCircuit::SaveOutput(const char* str) {
	//write our own design
}


