#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cstdlib>  // srand(), rand()
#include <ctime> 
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>

using std::cout;
using std::cin;
using std::vector;
using std::setw;
using std::endl;
using std::string;
using std::fstream;
using std::fixed;
using std::setprecision;
using std::cerr;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::stringstream;
using std::numeric_limits;
using std::streamsize;
using namespace std::chrono;
using std::ostringstream;
using std::istringstream;
using std::move;
extern std::stringstream buffer;

//using namespace std;

struct studentas {
    string Vard;
    string Pav;
    vector<float> nd;
    int egz;
    double Gal;
};

double pasirinktasGal(vector<float>&nd, int egz, char kaip);
void randomPaz(vector<float>& nd, int& egz, int kiek_nd);
void generuotiVardPav(string& vardas, string& pavarde);


#endif
