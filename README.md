
# objektinisProg2
# Programų spartos palyginimas

Šiame dokumente pateikiamas programų, naudojančių `struct` ir `class` tipo studentus, spartos palyginimas.

## Testavimo metodika

* Konteineris: `std::vector`
* Failų dydžiai: 100000 ir 1000000 studentų
* Dalijimo strategija: Greičiausia (neoptimizuota)

## Rezultatai

### Struktūros (`struct`) rezultatai

| Studentų skaičius | Failo nuskaitymas (s) | Studentų rūšiavimas (s) | Skirstymas į grupes (s) |
|---|---|---|---|
| 100000 | 0.20392 | 0.0007994 | 0.01625 |
| 1000000 | 1.86321 | 0.00835099 | 0.19125 |

### Klasės (`class`) rezultatai

| Studentų skaičius | Failo nuskaitymas (s) | Studentų rūšiavimas (s) | Skirstymas į grupes (s) |
|---|---|---|---|
| 100000 | 0.196728 | 0.000793 | 0.013829 |
| 1000000 | 1.824976 | 0.009382 | 0.214729 |

## Išvados

* Abiejų implementacijų veikimo laikas yra panašus.
* Nėra didelio skirtumo tarp `struct` ir `class` naudojimo spartos.
* Nedideli skirtumai gali atsirasti dėl įvairių faktorių.

# objektinisProg
bfee5a45c0feec4d2f885eedda9dd39cab515343
