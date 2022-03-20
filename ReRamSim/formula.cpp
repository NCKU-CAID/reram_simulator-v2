#include <cmath>
#include <cstdlib>
#include <iostream>
#include "constant.h"
#include "formula.h"

using namespace std;

/* Beyond 22 nm technology, the value capIdealGate is the sum of capIdealGate and capOverlap and capFringe */
double CalculateGateCap(double width, Technology tech) {
	//write our own design
}

double CalculateGateArea(	// Calculate layout area and width of logic gate given fixed layout height
    int gateType, int numInput,
    double widthNMOS, double widthPMOS,
    double heightTransistorRegion, Technology tech,
    double *height, double *width) {
	//write our own design
}

void CalculateGateCapacitance(
    int gateType, int numInput,
    double widthNMOS, double widthPMOS,
    double heightTransistorRegion, Technology tech,
    double *capInput, double *capOutput) {
	//write our own design
}

double CalculateDrainCap(
    double width, int type,
    double heightTransistorRegion, Technology tech) {
	//write our own design
}

double CalculateGateLeakage(
    int gateType, int numInput,
    double widthNMOS, double widthPMOS,
    double temperature, Technology tech) {
	//write our own design
}

double CalculateOnResistance(double width, int type, double temperature, Technology tech) {
	//write our own design
}

double CalculateTransconductance(double width, int type, Technology tech) {
	//write our own design
}

double horowitz(double tr, double beta, double rampInput, double *rampOutput) {
	//write our own design
}

double CalculatePassGateArea(	// Calculate layout area, height and width of pass gate given the number of folding on the pass gate width
    // This function is for pass gate where the cell height can change. For normal standard cells, use CalculateGateArea() where the cell height is fixed
    double widthNMOS, double widthPMOS, Technology tech, int numFold, double *height, double *width) {
	//write our own design
}

double NonlinearResistance(double R, double NL, double Vw, double Vr, double V) {	// Nonlinearity is the current ratio between Vw and V, and R means the resistance at Vr
	//write our own design
}
