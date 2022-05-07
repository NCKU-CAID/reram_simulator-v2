#include <fstream>
#include <iostream>
#include "cell.h"
#include "tile.h"
using namespace std;

int main(int argc, char const *argv[])
{
    /* test Cell class
    Cell testcell;
    testcell.setVoltage(2.5);
    testcell.setEnable(0);
    cout << "Area = " << testcell.getArea() << "nm^2" << endl;
    if (testcell.getCellType() == 0)
        cout << "Cell Type = 6T SRAM" << endl;
    else
        cout << "Cell Type = RRAM" << endl;
    cout << "BL = " << testcell.getVoltage() << "(V)" << endl;
    cout << "WL = " << testcell.isWLON() << endl;
    cout << "Stored weight = " << testcell.getValue() << endl;
    */

    Tile testtile(16, 0, 1);
    cout << "Tile size = " << testtile.getSize() << "x" << testtile.getSize()
         << endl;

    ofstream outfile("temp_weight", ios::out);
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    outfile << 255 << "\t" << 2 << "\t" << 5 << endl
            << 4 << "\t" << 64 << "\t" << 10 << endl
            << 25 << "\t" << 100 << "\t" << 234 << endl;

    // cout << "Created a temporary testing weight file" << endl;

    ifstream inFile("temp_weight", ios::in);
    if (!inFile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    testtile.programWeights("temp_weight", 3, 3, 8);



    return 0;
}