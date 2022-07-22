#include <math.h>
#include <cstdlib>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "tile.h"

using namespace std;

// ./main --tile_width 8 --tile_height 10 --kernel_width 2 --kernel_height 2
// --kernel_channel 4 --kernel_number 2 --weight_precision 8 --signed_weight 2
// --input_width 4 --input_height 4 --input_precision 8 --stride 1 --file
// ./test/filename.txt


void convolution(Tile &tile,
                 string FileNamesFile,
                 int input_w,
                 int input_h,
                 int input_precision,
                 int kernel_w,
                 int kernel_h,
                 int kernel_c,
                 int kernel_num,
                 int weight_precision,
                 int stride,
                 int padding,
                 int signed_weight,
                 int relu_on,
                 float ADC_voltage,
                 float &ADC_total_power,
                 string resultFileName)
{
    int kernelSize = kernel_w * kernel_h * kernel_c;
    int NumOutKernel_w;
    int NumOutKernel_h;
    if (padding) {
        NumOutKernel_w = (input_w - kernel_w + 2) / stride + 1;
        NumOutKernel_h = (input_h - kernel_h + 2) / stride + 1;
    } else {
        NumOutKernel_w = (input_w - kernel_w) / stride + 1;
        NumOutKernel_h = (input_h - kernel_h) / stride + 1;
    }
    int outSize = NumOutKernel_h * NumOutKernel_w;

    int CellPrecision = tile.getCellPrecision(0, 0);
    int NumCellPerWeight = ceil(weight_precision / CellPrecision);
    int maxNumWeightPerRow = int(floor(tile.getTileWidth() / NumCellPerWeight));
    // NumOutKernel_w*NumOutKernel_h files

    ifstream infile(FileNamesFile);
    if (!infile) {
        cerr << "Failed opening file: " << FileNamesFile << endl;
        exit(1);
    }

    ADC_total_power = 0;
    float ADC_temp_power = 0;

    string inputFile, weightFile;

    int input_count = 0;
    int filter_count = 0;
    int filter_num = 0;
    string action = "new";  // accumulate, append
    // cout << "output size: " << outSize << endl;
    while (infile >> inputFile >> weightFile) {
        ++input_count;

        // cout << "input_count: " << input_count << endl;
        // cout << "filter_count: " << filter_count << endl;
        // cout << "filter_num: " << filter_num << endl;
        // cout << "action: "<< action << endl;
        cout << "______________________________________________________________"
                "_________________"
             << endl;
        if (weightFile == to_string(0))
            cout << endl
                 << "input: " << inputFile << "\t"
                 << "weight: unchanged" << endl;
        else
            cout << endl
                 << "input: " << inputFile << "\t"
                 << "weight: " << weightFile << endl;
        if (weightFile != to_string(0)) {
            cout << "---------------------Start Programming "
                    "Weights-----------------------"
                 << endl;
            tile.programWeights(weightFile, kernel_w, kernel_h, kernel_c,
                                weight_precision);
            cout << "---------------------Programming Weights "
                    "Finish----------------------"
                 << endl;
        }
        string outputFileName = to_string(input_count) + ".txt";
        // cout << outputFileName << endl << endl;

        string mat_result = "";

        matrixMultiplication(inputFile, input_precision, tile, kernel_w,
                             kernel_h, kernel_c, weight_precision,
                             signed_weight, mat_result, ADC_voltage,
                             ADC_temp_power, kernel_num);
        // cout << "ADC_temp_power = " << ADC_temp_power << endl;
        ADC_total_power += ADC_temp_power;
        // cout << "ADC_total_power = " << ADC_total_power << endl;

        string outFileName = to_string(input_count) + ".txt";
        string outName = "./output/" + outFileName;
        if (!experimental::filesystem::is_directory("output") ||
            !experimental::filesystem::exists(
                "output")) {  // Check if src folder exists
            experimental::filesystem::create_directory(
                "output");  // create src folder
        }
        if (action == "new") {
            ofstream outfile(outName, ios::out);
            if (!outfile) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            // cout << weightFile << endl;
            // outfile << weightFile << '\t';

            cout << "matrix result: " << mat_result << endl;
            outfile << mat_result << '\t';
        } else if (action == "append") {
            ofstream outfile(outName, ios::app);
            if (!outfile) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            // outfile << weightFile << '\t';
            // cout << weightFile << endl;

            outfile << '\t' << mat_result;
            cout << "matrix result: " << mat_result << endl;

        } else {
            fstream file(outName, ios::in | ios::out);
            if (!file) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            string filestring, tempstring;
            int tempcount = 0;
            string writestring, accumstring;
            string templine;


            getline(file, templine);
            file.seekg(0, ios_base::beg);
            cout << "matrix result: " << mat_result << endl;
            istringstream iss(mat_result);
            istringstream isf(templine);


            tempcount = 0;
            while (tempcount < kernel_num) {
                ++tempcount;

                isf >> filestring;
                iss >> accumstring;
                // cout << "tempcount: " << tempcount << ", filter_num: " <<
                // filter_num << ", maxNumWeightPerRow+filter_num: "<<
                // maxNumWeightPerRow+filter_num << endl;
                file >> tempstring;
                if (tempcount >= filter_num &&
                    tempcount < maxNumWeightPerRow + filter_num) {
                    cout << tempcount << ": old value " << filestring
                         << " + accumulated value " << accumstring;
                    writestring =
                        to_string(stoi(filestring) + stoi(accumstring));
                    cout << " = " << writestring << endl;

                    // cout << "tempstring: "<< tempstring << endl;
                    if (file.eof()) {
                        file.seekg(0, ios_base::end);
                    }
                    // cout << "ptr0: " << file.tellg() << endl;
                    // cout << "filestring.length: " << filestring.length() << "
                    // writestring.length: " << writestring.length() << endl;

                    int diff = abs(int(filestring.length()) -
                                   int(writestring.length()));
                    if (filestring.length() >= writestring.length()) {
                        file.seekg(-filestring.length(), ios_base::cur);
                        // cout << "ptr1: " << file.tellg() << endl;

                        file << writestring;
                        // cout << "ptr1_2: " << file.tellg() << endl;

                        for (int i = 0; i < diff; ++i)
                            file.put(' ');
                        // file.seekg(filestring.length(), ios_base::cur);

                    } else {
                        int ptrpos_cur = file.tellg();
                        string linestring;
                        getline(file, linestring);
                        // ccout << "line: " << linestring << endl;
                        int ptrpos = ptrpos_cur - filestring.length();
                        file.seekg(ptrpos, ios_base::beg);
                        // cout << "ptr2: " << file.tellg() << endl;


                        file << writestring << '\t' << linestring;
                        file.seekg(ptrpos + writestring.length(),
                                   ios_base::beg);
                    }


                    // break;
                }
            }
        }



        if (input_count >= outSize) {
            action = "append";
            if (maxNumWeightPerRow >= kernel_num) {
                filter_count = kernel_num;
            } else {
                filter_count = filter_count + maxNumWeightPerRow;
            }
            if (filter_count < kernel_num) {
                input_count = 0;
            }
        }
        if (filter_count >= kernel_num) {
            action = "accumulate";
            if (input_count >= outSize) {
                ++filter_num;  // for correctly accumulate psum
                input_count = 0;
            }
            if (filter_num > kernel_num) {
                filter_num = 1;
            }
        }
    }

    string outPut = "";
    for (int i = 1; i <= outSize; ++i) {
        string result;
        ifstream outputfile("./output/" + to_string(i) + ".txt");
        if (!outputfile) {
            cerr << "Failed opening file: " << to_string(i) + ".txt" << endl;
            exit(1);
        }
        getline(outputfile, result);
        // cout << result << endl;
        istringstream out(result);
        int intresult;
        while (!out.eof()) {
            out >> intresult;
            if (relu_on & intresult < 0) {
                intresult = 0;
            }

            // cout << intresult << '\t' << endl;
            outPut.append(to_string(intresult) + '\t');
        }
        cout << endl;


        // outPut.append(result);
    }

    ofstream resultFile("./output/" + resultFileName + ".txt");
    resultFile << outPut;
}