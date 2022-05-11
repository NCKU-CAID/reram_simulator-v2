#include <math.h>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void compute(string Input, string Weight)
{
    ifstream infile_i(Input, ios::in);
    if (!infile_i) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    std::vector<int> v_i;
    int indata;
    while (1) {
        infile_i >> indata;
        if (infile_i.eof())
            break;
        // cout << indata << endl;
        v_i.push_back(indata);
    }

    infile_i.close();

    ifstream infile_w(Weight, ios::in);
    if (!infile_w) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }
    std::vector<int> v_w;
    int wdata;
    while (1) {
        infile_w >> wdata;
        v_w.push_back(wdata);
        if (infile_w.eof())
            break;
    }
    infile_w.close();

    if (!experimental::filesystem::is_directory("computedResult") ||
        !experimental::filesystem::exists(
            "computedResult")) {  // Check if src folder exists
        experimental::filesystem::create_directory(
            "computedResult");  // create src folder
    }
    ofstream outfile("./computedResult/computedOutput", ios::out);
    if (!outfile) {
        cerr << "Failed opening file" << endl;
        exit(1);
    }

    for (int i = 0; i < v_i.size(); ++i) {
        cout << v_i.at(i) << "\t";
    }
    cout << endl;

    for (int i = 0; i < v_w.size(); ++i) {
        cout << v_w.at(i) << "\t";
    }
    cout << endl;

    int numKernel = ceil(v_w.size() / v_i.size());
    cout << "numKernel = " << numKernel << endl;
    for (int j = 0; j < numKernel; ++j) {
        int result = 0;
        for (int i = 0; i < v_i.size(); ++i) {
            // cout << v_i.at(i) << "*" << v_w.at(j*v_i.size()+i);
            result += v_i.at(i) * v_w.at(j * v_i.size() + i);
            // cout << " = " << result << endl;
        }
        outfile << result << "\t";
    }
    outfile << endl;
}

int main(int argc, char const *argv[])
{
    compute(argv[1], argv[2]);
    return 0;
}