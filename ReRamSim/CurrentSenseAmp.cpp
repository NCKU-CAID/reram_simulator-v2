#include <cmath>
#include <iostream>
#include <vector>
#include "constant.h"
#include "formula.h"
#include "Param.h"
#include "CurrentSenseAmp.h"

using namespace std;
extern Param *param;

CurrentSenseAmp::CurrentSenseAmp(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	// TODO Auto-generated constructor stub
	initialized = false;
	invalid = false;
}

CurrentSenseAmp::~CurrentSenseAmp() {
	// TODO Auto-generated destructor stub
}

void CurrentSenseAmp::Initialize(int _numCol, bool _parallel, bool _rowbyrow, double _clkFreq, int _numReadCellPerOperationNeuro) {
	//write our own design
}

void CurrentSenseAmp::CalculateUnitArea() {
	//write our own design
}

void CurrentSenseAmp::CalculateArea(double widthArray) {	// adjust CurrentSenseAmp area by fixing S/A width
	//write our own design
}

void CurrentSenseAmp::CalculateLatency(const vector<double> &columnResistance, double numColMuxed, double numRead) {
	//write our own design
}

void CurrentSenseAmp::CalculatePower(const vector<double> &columnResistance, double numRead) {
	//write our own design
}

double CurrentSenseAmp::GetColumnLatency(double columnRes) {
	//write our own design
}

double CurrentSenseAmp::GetColumnPower(double columnRes) {
	//write our own design
}

void CurrentSenseAmp::PrintProperty(const char* str) {
	//write our own design
}
