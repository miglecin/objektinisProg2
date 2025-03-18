# Studentų duomenų apdorojimo greičio testai

Šis projektas testuoja studentų duomenų apdorojimo spartą naudojant tris skirtingus konteinerius:  
- `vector`
- `list`
- `deque`

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


## 1 STRATEGIJOS TYRIMAS

## REZULTATAI:
<img width="662" alt="Screenshot 2025-03-16 at 19 34 05" src="https://github.com/user-attachments/assets/0406f181-726e-44d7-bfe1-3a1d977784fc" />

## Pastebėjimai

### Failo nuskaitymas:
- Visi konteineriai panašiai skaito failą, tačiau `DEQUE` yra pastebimai lėčiausias didėjant duomenų kiekiui.

### Studentų rūšiavimas:
- `VECTOR` yra greičiausias rūšiuojant studentus.  
- `LIST` ir `DEQUE` rūšiuoja lėčiau, ypač didėjant duomenų kiekiui.

### Studentų skirstymas į grupes:
- `VECTOR` ir `LIST` yra daug efektyvesni skirstant studentus į grupes.  
- `DEQUE` skirstymas į grupes yra labai lėtas, ypač didesniems duomenų kiekiams.

---

## Išvados

- **`VECTOR`** yra efektyviausias konteineris visose trijose operacijose, ypač rūšiuojant ir skirstant į grupes.  
- **`LIST`** yra geras pasirinkimas, jei reikia dažnai įterpti arba ištrinti elementus, bet rūšiavimas ir skirstymas į grupes yra lėtesni nei su `VECTOR`.  
- **`DEQUE`** yra mažiausiai efektyvus pasirinkimas, ypač skirstant studentus į grupes, kur jo veikimo laikas yra ženkliai didesnis nei kitų dviejų konteinerių.

---

## Atminties naudojimo efektyvumas

Kadangi pirmoje strategijoje studentai yra dviejuose konteineriuose (bendrame ir vienoje iš grupių), atminties naudojimas yra neefektyvus.  
- Kiekvienas studentas egzistuoja du kartus, todėl naudojama dvigubai daugiau atminties nei būtų optimizuotame variante.  
- Tai ypač pastebima didėjant studentų skaičiui – kuo daugiau įrašų, tuo daugiau nereikalingos atminties sunaudojama.

### Atminties naudojimas realioje sistemoje

Žemiau pateiktoje ekrano nuotraukoje iš „Activity Monitor“ matyti, kad programos `v1` veikimo metu sunaudojama net **63,23 GB RAM**, kai fizinės operatyviosios atminties (RAM) kiekis yra tik **16 GB**.  
- Dėl šios priežasties sistema pradeda naudoti **swap atmintį** (4,84 GB), kas gali stipriai sumažinti našumą, nes keitimasis su SSD yra lėtesnis nei tiesioginis duomenų saugojimas RAM.
- Dėl perteklinio atminties naudojimo programos gali sulėtėti, o esant labai dideliems duomenų kiekiams – net sustoti veikti.
- Optimizuojant šį procesą būtų galima sumažinti atminties naudojimą bent **dvigubai**, pašalinant nereikalingas duomenų kopijas.

<img width="852" alt="Screenshot 2025-03-16 at 18 58 53" src="https://github.com/user-attachments/assets/7cf403ea-994a-44d3-ba24-db4ceba50323" />


## 2 STRATEGIJOS TYRIMAS

## Apžvalga
Ši tyrimo strategija nagrinėja studentų duomenų skirstymo į dvi grupes (vargšiukai ir kietiakai) efektyvumą naudojant bendrą studentų konteinerį (t.y., `vector`, `list`, arba `deque`). Kai studentas yra "vargšiukas" (t.y., jo galutiniai balai mažesni nei 5.0), jis perkeliamas į naująjį "vargšiukų" konteinerį ir ištryniamas iš bendro konteinerio. Po šio proceso bendrame konteineryje lieka tik kietiakai.

## REZULTATAI:
<img width="652" alt="Screenshot 2025-03-18 at 12 35 29" src="https://github.com/user-attachments/assets/712e2b87-af47-47ee-8583-341639d5dccb" />

## Pastebėjimai

- **Failo nuskaitymas**: Visų konteinerių failo nuskaitymo laikas yra panašus, tačiau DEQUE šiek tiek lėtesnis didesniems duomenų kiekiams.

**Atminties naudojimas**:
   - Naudojant šią strategiją, atminties naudojimas tampa efektyvesnis, nes studentai yra perkelti tik į vieną naują konteinerį (vargšiukai) ir ištrinami iš bendro studentų konteinerio. Tai sumažina bendrą atminties naudojimą.

 **Efektyvumas**:
   - Strategija efektyvesnė atminties atžvilgiu, tačiau dažni trynimai (ypač su tam tikrais konteineriais) gali turėti neigiamą poveikį veikimo greičiui.

---

### Pastebėjimai apie našumą su VECTOR

Naudojant **VECTOR** su dideliais duomenų kiekiais (pvz., su 1,000,000 studentų), "skirstymo į grupes" operacija gali tapti labai lėta dėl šių priežasčių:

- **Atminties perrašymai ir peralokacijos**: Nuolatiniai elementų įterpimai ir trinimai gali sukelti didelius atminties perrašymus, nes `VECTOR` turi perskirstyti visą atmintį, kai pasiekia ribas.
  
- **Elementų perkėlimas ir trynimas**: Kiekvienas elementų keitimas gali užtrukti ilgiau, nes `VECTOR` turi išlaikyti nuoseklumą visoje sekos struktūroje.

- **Lėtumas su dideliais duomenimis**: Su milijonais elementų operacijos tampa lėtesnės dėl trynimo ir perkėlimo procesų.

---

## Išvados

1. **VECTOR**: Efektyviausias konteineris rūšiavimui, tačiau su dideliais duomenų kiekiais (pvz., 1,000,000 studentų) gali tapti lėtas dėl atminties perrašymo ir perkėlimo operacijų. Nors jis greitas mažais duomenimis, didelių duomenų atveju gali pasireikšti atminties valdymo problemos.

2. **LIST**: Panašiai kaip ir **VECTOR**, tačiau **LIST** konteineris geriau susidoroja su elementų įterpimu ir šalinimu. Tačiau rūšiavimas ir grupių skirstymas su **LIST** yra lėtesni nei su **VECTOR**.

3. **DEQUE**: Nors **DEQUE** yra greitesnis už **LIST** su mažesniais duomenimis, su didesniais duomenimis jis taip pat susiduria su našumo problemomis, nes reikalauja daugiau atminties ir gali tapti lėtesnis dėl dažnų elementų perkėlimų.

4. **Atminties efektyvumas**: 2-oji strategija, naudojant papildomą konteinerį "vargšiukams", yra efektyvesnė atminties atžvilgiu, nes nebereikia dvigubai laikyti tų pačių duomenų. Tačiau nuolatiniai elementų trynimai ir perkėlimai gali tapti lėtesni, ypač su **VECTOR** konteineriu.


## 3 STRATEGIJOS TYRIMAS: 
### Greitas studentų skirstymas naudojant optimizuotus algoritmus su **VECTOR** konteineriu

Trečioje strategijoje naudojame **VECTOR** konteinerį ir pasitelkiame optimizuotus algoritmus, kad paspartintume studentų skirstymo į grupes operaciją. Pagrindinis tikslas buvo pasiekti spartų studentų skirstymą, pritaikant tokius algoritmus kaip **std::partition**, **std::copy**, ir kitus, kurie leidžia greitai suskirstyti studentus į dvi grupes.

### Implementacijos apžvalga:
- **Failo nuskaitymas**: Studentai įkeliami į **VECTOR** konteinerį.
- **Studentų rūšiavimas**: Studentai yra rūšiuojami pagal nustatytus parametrus.
- **Studentų skirstymas į grupes**: Pritaikytas algoritmas **std::partition** su **std::copy**, siekiant efektyviai perkelti studentus į dvi grupes: vargšus ir kietiakus. Naudojama tik viena operacija, kuri atlieka greitą skirstymą.

### Palyginimas su kitomis strategijomis:
- **Našumo palyginimas**: Po optimizacijos operacija **skirstymas į grupes** su **VECTOR** konteineriu buvo žymiai greitesnė nei su kitais konteineriais, ypač dirbant su didesniais duomenų kiekiais.

### REZULTATAI:
<img width="649" alt="Screenshot 2025-03-18 at 20 33 25" src="https://github.com/user-attachments/assets/a1ce3201-585a-479e-ba31-f822a242c752" />

### Pastebėjimai:
- **Greitėjimas**: Panaudojus optimizuotus algoritmus, kaip **std::partition** ir **std::copy**, studentų skirstymo į grupes operacija tapo žymiai greitesnė.
- **Didelis našumas su dideliais duomenimis**: Su didesniais duomenų kiekiais, pavyzdžiui, su 10 milijonų studentų, optimizuotas skirstymas išlieka efektyvus, nors vis tiek pastebimas laiko augimas, susijęs su dideliais duomenų kiekiais.
  
### Išvados:
3-ioji strategija, naudojanti optimizuotus algoritmus su **VECTOR** konteineriu, yra labai efektyvi ir greita, ypač esant dideliems studentų kiekiams. Ši strategija suteikia žymiai greitesnį skirstymą į grupes palyginti su kitais konteineriais ir tradiciniais metodais.


