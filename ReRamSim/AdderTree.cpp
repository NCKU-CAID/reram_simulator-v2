#include <cmath>
#include <iostream>
#include "constant.h"
#include "formula.h"
#include "AdderTree.h"

using namespace std;

AdderTree::AdderTree(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell): inputParameter(_inputParameter), tech(_tech), cell(_cell), adder(_inputParameter, _tech, _cell), FunctionUnit() {
	initialized = false;
}

void AdderTree::Initialize(int _numSubcoreRow, int _numAdderBit, int _numAdderTree) {
	/*--Write our own design--*/
}

void AdderTree::CalculateArea(double _newHeight, double _newWidth, AreaModify _option) {
	/*--Write our own design--*/
}

void AdderTree::CalculateLatency(double numRead, int numUnitAdd, double _capLoad) {
	/*--Write our own design--*/
}

void AdderTree::CalculatePower(double numRead, int numUnitAdd) {
	/*--Write our own design--*/
}

void AdderTree::PrintProperty(const char* str) {
	/*--Write our own design--*/
}
