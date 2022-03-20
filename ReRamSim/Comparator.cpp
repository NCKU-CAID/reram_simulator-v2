#include <iostream>
#include "constant.h"
#include "formula.h"
#include "Comparator.h"

using namespace std;

Comparator::Comparator(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), FunctionUnit() {
	initialized = false;
}

void Comparator::Initialize(int _numBit, int _numComparator) {
	//write our own design
}

void Comparator::CalculateUnitArea(AreaModify _option) {
	//write our own design
}

void Comparator::CalculateArea(double widthArray){
	//write our own design
}

void Comparator::CalculateLatency(double _rampInput, double _capLoad, double numRead){
	//write our own design
}

void Comparator::CalculatePower(double numRead, int numComparatorPerOperation) {
	//write our own design
}

void Comparator::PrintProperty(const char* str) {
	//write our own design
}

void Comparator::SaveOutput(const char* str) {
	//write our own design
}

