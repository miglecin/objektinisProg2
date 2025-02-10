#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::setw;
using std::endl;
using std::string;
using std::fstream;
using std::fixed;
using std::setprecision;


using namespace std;


struct studentas {
    string Vard;
    string Pav;
    float* nd;
    int nd_kiekis;
    int egz;
    double Gal;
};