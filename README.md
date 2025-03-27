
# objektinisProg2
# Programų spartos palyginimas `struct` vs. `class`

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

----------------------------------------------------------------

# Programos spartos analizė su O1, O2, O3 flag'ais

Šiame dokumente pateikiama programos spartos analizė, lyginant "Struktūros" ir "Klasės" variantus su skirtingais optimizavimo flagais.

## Testavimo metodika

1.  Programa buvo paleista su skirtingais studentų skaičiais: 1000, 10000, 100000, 1000000 ir 10000000.
2.  Programa buvo kompiliuota su optimizavimo flagais: O1, O2, O3.
3.  Buvo matuojamos šios operacijos:
    * Failo nuskaitymas
    * Studentų rūšiavimas
    * Studentų skaidymas į grupes
4.  Testai buvo pakartoti kelis kartus ir apskaičiuoti vidurkiai.

## Rezultatai

| Tipas      | Optimizavimo flagas | Failo dydis    | Failo nuskaitymas (s) | Studentų rūšiavimas (s) | Skirstymas į grupes (s) |
| :--------- | :------------------ | :------------- | :------------------- | :---------------------- | :----------------------- |
| Struktūra  | O1                  | 100000         | 0.3506804            | 1.022409                 | 0.0343105                |
| Struktūra  | O1                  | 1000000        | 3.199772             | 10.15857                 | 0.3709248                |
| Struktūra  | O2                  | 100000         | 0.2065624            | 0.8267488                | 0.0143346                |
| Struktūra  | O2                  | 1000000        | 1.837956             | 8.00394                 | 0.2062462                |
| Struktūra  | O3                  | 100000         | 0.2042266            | 0.7903494                | 0.0147426                |
| Struktūra  | O3                  | 1000000        | 1.81989              | 8.5064                 | 0.2086486                |
| Klasė      | O1                  | 100000         | 0.337025             | 1.518416                 | 0.0369319                |
| Klasė      | O1                  | 1000000        | 3.049766             | 15.45106                 | 0.4165822                |
| Klasė      | O2                  | 100000         | 0.217939             | 0.811108                 | 0.01640278               |
| Klasė      | O2                  | 1000000        | 2.086458             | 9.742368                 | 0.2256188                |
| Klasė      | O3                  | 100000         | 0.198677             | 1.077024                 | 0.01438404               |
| Klasė      | O3                  | 1000000        | 1.84187              | 8.099636                 | 0.202793                 |

## Analizė

* **Optimizavimo flagų įtaka:**
    * Matome, kad optimizavimo flagai turi didelę įtaką programos veikimo laikui. Su didesniu optimizavimo flagu (O3) programos veikimo laikas sumažėja.
    * Optimizavimo flagai ypač veikia failo nuskaitymo ir skaidymo į grupes operacijas.
* **Failo nuskaitymas:**
    * Failo nuskaitymo laikas didėja tiesiškai didėjant studentų skaičiui.
    * Optimizavimo flagai akivaizdžiai turi įtakos failo nuskaitymo laikui.
* **Studentų rūšiavimas:**
    * Rūšiavimo laikas yra labai mažas abiem variantams.
    * Optimizavimo flagai turi minimalią įtaką rūšiavimo laikui.
* **Studentų skaidymas į grupes:**
    * Skaidymo laikas didėja didėjant studentų skaičiui.
    * Optimizavimo flagai turi didelę įtaką skaidymo laikui.
* **Struktūra vs. Klasė:**
    * Abiejų variantų veikimo laikas yra panašus, tačiau yra nedidelių skirtumų, priklausomai nuo optimizavimo flagų.
    * Klasės variantas su O2 ir O3 optimizavimo flagais rodo šiek tiek didesnį nuskaitymo laiką didesniame faile.

## Išvados

* Optimizavimo flagai (O1, O2, O3) reikšmingai pagerina programos veikimo laiką, ypač didesniems duomenų rinkiniams.
* Failo nuskaitymo ir studentų skaidymo į grupes operacijos labiausiai pasinaudoja optimizavimo flagais.
* Studentų rūšiavimo operacija yra palyginti greita ir mažai priklauso nuo optimizavimo flagų.
* Rekomenduojama naudoti didesnius optimizavimo flagus (O2 ar O3) didesniems duomenų rinkiniams, kad programa veiktų greičiau.

# objektinisProg
bfee5a45c0feec4d2f885eedda9dd39cab515343
