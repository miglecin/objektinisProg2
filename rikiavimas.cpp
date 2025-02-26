#include "rikiavimas.h"

bool pagalVarda(const studentas& a, const studentas& b) { return a.Vard < b.Vard; }
bool pagalPavarde(const studentas& a, const studentas& b) { return a.Pav < b.Pav; }
bool pagalGal(const studentas& a, const studentas& b) { return a.Gal > b.Gal; }

void rusiuotiStud(vector<studentas>& grupe, char rusiavimoPas)
{
    if(rusiavimoPas=='v')
    {
        sort(grupe.begin(), grupe.end(), pagalVarda);
    }
    else if (rusiavimoPas=='p')
    {
        sort(grupe.begin(), grupe.end(), pagalPavarde);
    }
    else if (rusiavimoPas=='g')
    {
        sort(grupe.begin(), grupe.end(), pagalGal);
    }
}
