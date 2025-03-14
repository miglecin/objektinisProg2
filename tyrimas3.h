#ifndef TYRIMAS3_H
#define TYRIMAS3_H

#include "studentas.h"
#include "sufailais.h"
#include "rikiavimas.h"
#include "LaikoMatavimas.h"


//sabloninė funkcija konteineriu testavimui
template <typename Container>
void testuotiKonteineri(const string& failoPavadinimas, const string& rezultataiAplankas);
void issaugotiRezultatus(const string& failoPavadinimas, const string& turinys);


#endif 
