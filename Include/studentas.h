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
#include <filesystem>
#include <chrono>
#include <random>
#include <list>
#include <deque>

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
using std::list;
using std::deque;
using std::string;

//using namespace std;

template <typename T=vector<float>>  //jei T nepateikta, bus vector<float
struct studentas {
    using nd_type=T;  //konteineris automatiskai priskiriamas is T

    string Vard;
    string Pav;
    nd_type nd;  //cia gali buti vector<float>, list<float> arba deque<float>
    int egz;
    double Gal;
};


//sabloniniu funkc deklaravimas
template <typename Container>
void nuskaitymasFile(Container& grupe, const string& filename);

template <typename Container>
void rusiuotiStud(Container& grupe);

template <typename Container>
void skirstytiStudentus(const Container& grupe, Container& vargsiai, Container& kietiakai);

template <typename Container>
double pasirinktasGal(Container& nd, int egz, char kaip);

template <typename Container>
void randomPaz(Container& nd, int& egz, int kiek_nd);

void generuotiVardPav(string& vardas, string& pavarde);


#endif
