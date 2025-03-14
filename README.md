# objektinisProg
APRAŠYMAS:

Ši programa generuoja studentų duomenų failus ir atlieka jų apdorojimą: studentų rūšiavimą į dvi grupes pagal jų galutinį balą. Testavimai buvo atlikti su skirtingo dydžio failais, siekiant įvertinti programos našumą.




PIRMAS TYRIMAS: 
FAIILŲ KŪRIMO SPARTA

Buvo išmatuotas laikas, per kurį sugeneruojami studentų sąrašų failai su atitinkamais dydžiais.

<img width="573" alt="Screenshot 2025-03-05 at 17 18 42" src="https://github.com/user-attachments/assets/fa7615cf-3011-495f-a5b5-dc759f8cafbd" />

VIDUTINIAI laikai visiems failų dydžiams:

<img width="434" alt="Screenshot 2025-03-05 at 17 02 11" src="https://github.com/user-attachments/assets/bae8d498-fe87-4c77-8a45-d5a7eaf5505f" />



ANTRAS TYRIMAS:
DUOMENŲ APDOROJIMO SPARTA

Buvo išmatuotas duomenų nuskaitymo iš failo, studentų rūšiavimo bei rezultatų išvedimo į naujus failus laikas.

<img width="935" alt="Screenshot 2025-03-05 at 17 25 05" src="https://github.com/user-attachments/assets/feca95ed-a9ca-4737-a67b-0a35ea69c44d" />

<img width="935" alt="Screenshot 2025-03-05 at 17 25 38" src="https://github.com/user-attachments/assets/3274a0bf-edc3-4d02-a275-83c47a4682bc" />

VIDUTINIAI laikai:

<img width="482" alt="Screenshot 2025-03-05 at 17 30 27" src="https://github.com/user-attachments/assets/a9586448-74db-4789-80dc-0be06c6abb23" />
<img width="482" alt="Screenshot 2025-03-05 at 17 30 38" src="https://github.com/user-attachments/assets/68357030-2534-4ba9-9340-26e1837b5aa5" />
<img width="482" alt="Screenshot 2025-03-05 at 17 30 46" src="https://github.com/user-attachments/assets/1ce5bb2f-1ce5-471c-a228-067a195694ad" />
<img width="482" alt="Screenshot 2025-03-05 at 17 30 53" src="https://github.com/user-attachments/assets/cc2a93fc-b07e-4ed4-8d04-82ee0f7f96b9" />
<img width="482" alt="Screenshot 2025-03-05 at 17 31 07" src="https://github.com/user-attachments/assets/3d2230c7-aaf2-43a6-be22-1be2f55a4509" />


TYRIMAS 3:

<img width="682" alt="Screenshot 2025-03-14 at 17 04 24" src="https://github.com/user-attachments/assets/37c7f9f4-1552-49c8-8f85-ff878345b34e" />

Pastebėjimai:

Failo nuskaitymas:
Visi konteineriai panašiai skaito failą, tačiau DEQUE šiek tiek lėtesnis didesniems duomenų kiekiams.

Studentų rūšiavimas:
VECTOR yra žymiai greitesnis rūšiuojant studentus.
LIST ir DEQUE rūšiuoja lėčiau, ypač didėjant duomenų kiekiui.

Studentų skirstymas į grupes:
VECTOR ir LIST yra žymiai efektyvesni skirstant studentus į grupes.
DEQUE skirstymas į grupes yra labai lėtas, ypač didesniems duomenų kiekiams, ir yra mažiausiai efektyvus konteineris šiai operacijai.

Išvados:

VECTOR konteineris yra efektyviausias visose trijose operacijose, ypač rūšiavimo ir skirstymo į grupes atžvilgiu.

LIST konteineris yra geras pasirinkimas, jei reikia dažnai įterpti arba ištrinti elementus, bet rūšiavimas ir skirstymas į grupes yra lėtesni nei su VECTOR.

DEQUE konteineris yra mažiausiai efektyvus šiam konkrečiam atveju, ypač skirstymo į grupes operacijai.



