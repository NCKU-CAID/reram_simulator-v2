#include <iostream>
#include <fstream>
#include "FunctionUnit.h"

using namespace std;

FunctionUnit::FunctionUnit() {
	height = width = 0;
	area = 0;
	emptyArea = 0;
	usedArea = 0;
	totalArea = 0;	// may use it if the circuit units are scattered
	readLatency = writeLatency = 0;
	readDynamicEnergy = writeDynamicEnergy = 0;
	leakage = 0;

	newWidth = newHeight = 0;
	readPower = writePower = 0;
}

void FunctionUnit::PrintProperty(const char* str) {
	//write our own design
}

void FunctionUnit::SaveOutput(const char* str) {
	//write our own design
}

void FunctionUnit::MagicLayout() {
	//write our own design
}

void FunctionUnit::OverrideLayout() {
	//write our own design
}
