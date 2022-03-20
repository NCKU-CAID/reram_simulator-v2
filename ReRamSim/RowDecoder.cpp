#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "RowDecoder.h"

using namespace std;

RowDecoder::RowDecoder(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit(){
	initialized = false;
}

void RowDecoder::Initialize(DecoderMode _mode, int _numAddrRow, bool _MUX, bool _parallel) {
	//write our own design	
}

void RowDecoder::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	//write our own design
}

void RowDecoder::CalculateLatency(double _rampInput, double _capLoad1, double _capLoad2, double numRead, double numWrite) {
	//write our own design
}

void RowDecoder::CalculatePower(double numRead, double numWrite) {
	//write our own design
}

void RowDecoder::PrintProperty(const char* str) {
	//write our own design
}

void RowDecoder::SaveOutput(const char* str) {
	//write our own design
}
