#ifndef ROWDECODER_H_
#define ROWDECODER_H_

#include "typedef.h"
#include "InputParameter.h"
#include "Technology.h"
#include "MemCell.h"
#include "FunctionUnit.h"

class RowDecoder: public FunctionUnit {
public:
	RowDecoder(const InputParameter& _inputParameter, const Technology& _tech, const MemCell& _cell);
	virtual ~RowDecoder() {}
	const InputParameter& inputParameter;
	const Technology& tech;
	const MemCell& cell;

	/* Functions */
	void PrintProperty(const char* str);
	void SaveOutput(const char* str);
	void Initialize(DecoderMode _mode, int _numAddrRow, bool _MUX, bool _parallel);
	void CalculateArea(double _newHeight, double _newWidth, AreaModify _option);
	void CalculateLatency(double _rampInput, double _capLoad1, double _capLoad2, double numRead, double numWrite);
	void CalculatePower(double numRead, double numWrite);

	/* Properties */
	bool initialized;	/* Initialization flag */
	int numAddrRow;		/* Number of rows */
	double capLoad1;	// REGULAR: general capLoad, MUX: the NMOS Tg gates
	double capLoad2;	// MUX: the PMOS Tg gates
	int numColNor, numNorPerCol, numColNand, numNandPerCol, numColInv, numInvPerCol;
	int numRowNor, numNorPerRow, numRowNand, numNandPerRow, numRowInv, numInvPerRow;

	double widthInvN, widthInvP, widthNandN, widthNandP, widthNorN, widthNorP, widthDriverInvN, widthDriverInvP;
	int numInv, numNand, numNor, numMetalConnection;
	double capInvInput, capInvOutput, capNandInput, capNandOutput, capNorInput, capNorOutput, capDriverInvInput, capDriverInvOutput;
	double rampInput, rampOutput;
	DecoderMode mode;	// ROW or COLUMN mode
	bool MUX;	// MUX mode
	bool parallel;    // for mux decoder of parallel reading mode
};

#endif /* ROWDECODER_H_ */
