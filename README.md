
# Studentų duomenų apdorojimo greičio testai

Šis projektas testuoja studentų duomenų apdorojimo spartą naudojant tris skirtingus konteinerius:  
- `std::vector`
- `std::list`
- `std::deque`

Testuojami trys pagrindiniai veiksmai:
1. **Failo nuskaitymas** – kiek laiko užtrunka įkelti duomenis į konteinerį.
2. **Rūšiavimas** – kiek laiko užtrunka surūšiuoti studentus.
3. **Skirstymas į grupes** – kiek laiko užtrunka atskirti studentus į dvi grupes.

   
## **Testavimo sistemos parametrai**
- **Operacinė sistema**: macOS Monterey 12.0.1
- **Įrenginys**: MacBook Pro (16-inch, 2019)
- **Procesorius (CPU)**: Intel Core i7, 6 branduoliai, 2.6 GHz
- **Operatyvioji atmintis (RAM)**: 16 GB DDR4 2667 MHz
- **Kietasis diskas (HDD/SSD)**: Macintosh HD (greičiausiai SSD)
- **Vaizdo plokštė (GPU)**: Intel UHD Graphics 630 (1536 MB)
- **Kompiliatorius**: `g++ (GCC) / clang++`
- **Kompiliavimo nustatymai**: `-std=c++17 -O2`

## Testavimo eiga
Testai buvo atliekami su failais, kuriuose buvo skirtingas įrašų kiekis:
- 1 000 įrašų (`STUDENTAI_1000.txt`)
- 10 000 įrašų (`STUDENTAI_10000.txt`)
- 100 000 įrašų (`STUDENTAI_100000.txt`)
- 1 000 000 įrašų (`STUDENTAI_1000000.txt`)
- 10 000 000 įrašų (`STUDENTAI_10000000.txt`)

Su kiekvienu failu tyrimas buvo pakartotas 5 kartus, rezultatai surašyti į lentelę ir apskaičiuotas vidurkis.

Testavimo metu matuota kiekvienos operacijos trukmė.

## REZULTATAI:

<img width="682" alt="Screenshot 2025-03-14 at 17 04 24" src="https://github.com/user-attachments/assets/37c7f9f4-1552-49c8-8f85-ff878345b34e" />

## Pastebėjimai:

Failo nuskaitymas:
Visi konteineriai panašiai skaito failą, tačiau DEQUE šiek tiek lėtesnis didesniems duomenų kiekiams.

Studentų rūšiavimas:
VECTOR yra žymiai greitesnis rūšiuojant studentus.
LIST ir DEQUE rūšiuoja lėčiau, ypač didėjant duomenų kiekiui.

Studentų skirstymas į grupes:
VECTOR ir LIST yra žymiai efektyvesni skirstant studentus į grupes.
DEQUE skirstymas į grupes yra labai lėtas, ypač didesniems duomenų kiekiams, ir yra mažiausiai efektyvus konteineris šiai operacijai.

## Išvados:

VECTOR konteineris yra efektyviausias visose trijose operacijose, ypač rūšiavimo ir skirstymo į grupes atžvilgiu.

LIST konteineris yra geras pasirinkimas, jei reikia dažnai įterpti arba ištrinti elementus, bet rūšiavimas ir skirstymas į grupes yra lėtesni nei su VECTOR.

DEQUE konteineris yra mažiausiai efektyvus šiam konkrečiam atveju, ypač skirstymo į grupes operacijai.



