#include <math.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "cell.h"
#include "tile.h"

using namespace std;

 // ./main --tile_width 8 --tile_height 10 --kernel_width 2 --kernel_height 2 --kernel_channel 4 --kernel_number 2 --weight_precision 8 --signed_weight 2 --input_width 4 --input_height 4 --input_precision 8 --stride 1 --file ./test/filename.txt


void convolution( Tile &tile,
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
                  int signed_weight,
                  int relu_on,
                  float ADC_voltage,
                  string resultFileName)
{
    int kernelSize = kernel_w*kernel_h*kernel_c;
    int NumOutKernel_w = (input_w-kernel_w)/stride+1;
    int NumOutKernel_h = (input_h-kernel_h)/stride+1;
    int outSize = NumOutKernel_h*NumOutKernel_w;
    // NumOutKernel_w*NumOutKernel_h files

    ifstream infile(FileNamesFile);
    if (!infile) {
        cerr << "Failed opening file: " << FileNamesFile << endl;
        exit(1);
    }
    string inputFile, weightFile;

    int input_count = 0;
    int filter_count = 0;
    int filter_num = 0;
    string action = "new"; //accumulate, append
    // cout << "output size: " << outSize << endl;
    while(infile >> inputFile >> weightFile)
    {
        ++input_count;

        // cout << "input_count: " << input_count << endl;
        // cout << "filter_count: " << filter_count << endl;
        // cout << "filter_num: " << filter_num << endl;
        // cout << "action: "<< action << endl;

        // if (weightFile == to_string(0))
        //     cout << "input: "<< inputFile << "\t" << "weight: unchanged" << endl;
        // else
        //     cout << "input: "<< inputFile << "\t" << "weight: " << weightFile << endl;
        if(weightFile != to_string(0))
        {
            cout << "---------------------Start Programming Weights-----------------------" << endl;
            tile.programWeights(weightFile, kernel_w, kernel_h,kernel_c, weight_precision);
            cout << "---------------------Programming Weights Finish----------------------" << endl;
        }
        string outputFileName = to_string(input_count)+".txt";
        // cout << outputFileName << endl << endl;

        string mat_result="";
       
        matrixMultiplication(inputFile, input_precision, tile, kernel_w,kernel_h, kernel_c, weight_precision, signed_weight, mat_result, ADC_voltage, relu_on);

        string outFileName = to_string(input_count) + ".txt";
        string outName = "./output/" + outFileName;
        if (!experimental::filesystem::is_directory("output") ||
            !experimental::filesystem::exists(
                "output")) {  // Check if src folder exists
            experimental::filesystem::create_directory(
                "output");  // create src folder
        }
        if(action == "new"){
            ofstream outfile(outName, ios::out);
            if (!outfile) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            // cout << weightFile << endl;
            // outfile << weightFile << '\t';

            // cout << "matrix result: " << mat_result << endl;
            outfile <<mat_result << '\t';
        }
        else if (action == "append"){
            ofstream outfile(outName, ios::app);
            if (!outfile) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            // outfile << weightFile << '\t';
            // cout << weightFile << endl;

            outfile << mat_result << '\t';
            // cout << "matrix result: " << mat_result << endl;
            
        }
        else{
            fstream file(outName, ios::in | ios::out );
            if (!file) {
                cerr << "Failed opening file: " << outName << endl;
                exit(1);
            }
            string tempstring;
            int tempcount = 0;
            string writestring;

            while(file>>tempstring){
                    ++tempcount;
                    istringstream iss(mat_result);
                    iss >> writestring; 
                    // cout << tempcount << ": old value " << tempstring << " + accumulated value " << writestring;
                    writestring = to_string(stoi(tempstring)+stoi(writestring));
                    // cout << " = " << writestring << endl;
                    if(tempcount == filter_num){
                        
                        int diff = abs(int(tempstring.length())-int(writestring.length()));
                        if(tempstring.length()>=writestring.length())
                        {
                            file.seekg(-tempstring.length(), ios_base::cur);    
                            file<<writestring;
                            for (int i = 0; i<diff;++i)
                                file.put(' ');
                            file.seekg(tempstring.length(), ios_base::cur);  
                        }
                        else
                        {

                            int ptrpos_cur = file.tellg();
                            // cout << "ptr: " << ptrpos_cur << endl;
                            string linestring;
                            getline(file,linestring);
                            // ccout << "line: " << linestring << endl;
                            int ptrpos = ptrpos_cur-tempstring.length();
                            file.seekg(ptrpos, ios_base::beg); 
                            file<<writestring<<'\t'<<linestring<<'\t';
                            file.seekg(ptrpos+writestring.length(), ios_base::beg);  
                        }
                        
                       
                        break;
                    }
            }



        }

       

        if (input_count>=outSize)
        {   
            ++filter_count;
            action = "append";
            if (filter_count < kernel_num){
                input_count = 0;
            }
        }
        if (filter_count >= kernel_num)
        {
            action = "accumulate";
            if (input_count >= outSize){
                ++filter_num; //for correctly accumulate psum
                input_count = 0;
            }
            if(filter_num>kernel_num){
                filter_num = 0;

            }
            
        }

        
        
    }

    string outPut = "";
    for (int i = 1; i<=outSize; ++i)
    {
        string result;
        ifstream outputfile("./output/"+to_string(i)+".txt");
        if (!outputfile) {
            cerr << "Failed opening file: " << to_string(i)+".txt" << endl;
            exit(1);
        }
        getline(outputfile, result);
        outPut.append(result);

    }

    ofstream resultFile("./output/"+resultFileName+".txt");
    resultFile<<outPut;

 
}