> Credite: https://github.com/Ionnier/poo-wps/blob/main/lab/L04.md

# Laborator 4 

## Polinom

Clasa ”Polinom” (cu o singura nedeterminată) - reprezentat ca vector al coeficienților

* fiecare coeficient va fi de tip double
* membri privati pentru vectorul propriuzis
* constructori pentru initializare si copiere
* destructor
* metoda publica pentru calculul valorii unui polinom intr-un punct
* suma a doua polinoame, implementata prin supraincarcarea operatorului +
* diferenta a doua polinoame, implementata prin supraincarcarea operatorului -
* produsul a doua polinoame, implementat prin supraincarcarea operatorului *


Referințe:

* [Definrea unei clase](https://github.com/Ionnier/poo/tree/main/labs/L02#crearea-obiectelor)
* [Funcții date membre (metode)](https://github.com/Ionnier/poo/tree/main/labs/L02#lucrul-cu-metode)
* [Supraîncărcarea operatorilor](https://github.com/Ionnier/poo/tree/main/labs/L02#supra%C3%AEnc%C4%83rcarea-operatorilor)
* [Supraîncărcarea opeartorilor de citire și afișare](https://gist.github.com/Ionnier/c67751fb609c8e4eded7396495cfb04d#file-fractie-cpp-L142)
* [Polinom](https://www.cuemath.com/algebra/polynomials-in-one-variable/)

## Spânzurătoarea

Creați un program în C++ care să simuleze un joc de "Spânzurătoarea".

Un joc de spânzurătoarea conține un cuvânt ascuns pe care un jucător trebuie să îl
ghicească literă cu literă. Dacă o literă nu se află în cuvânt, numărul de vieți (șanse de a
alege) disponibile scade. Jocul se termină atunci când jucătorul ghicește cuvântul întreg sau
când acesta rămâne fără vieți.

Sarcini:

* Crearea funcționalității minime (pornirea unui joc de la un cuvânt aleator, afișarea stării
curente (numărul de vieți, literele deja cunoscute din cuvânt), citirea unei litere și
actualizarea stării.
* Adăguarea unor nivele de dificultate (separarea pool-ului de cuvinte in dificultăți,
pornirea de la câteva litere cunoscute, număr de vieți mai mare), ușor, mediu și dificil.
* Posibilitatea de salvare a stării curente a jocului și revenirea mai târziu (se pot suspenda
un număr nelimitat de jocuri)
*  Crearea unui sistem de punctare (per fiecare joc, streak-uri, etc.)
* Crearea unui leaderboard local

**Atenție!**

 Citiți cu atenție întreaga cerință, dar nu încercați să rezolvați toate cerințele din prima. Concentrați-vă doar pe minimul necesar ce vă aduce mai aproape pentru rezolvarea unei cerințe.

 Dezvoltarea software este incrementală, astfel trebuie să fim obișnuiți în adăugarea de logică după finalizare.

### Indicații

1. Analizați jocul de [spânzurătoarea](https://www.coolmathgames.com/0-hangman). Care sunt elementele care ajută în reprezentarea acestuia? Care sunt acțiunile care sunt luate și în ce context?

<details>
<summary></summary>
Jocul presupune ghicirea unui cuvânt necunoscut. 

Astfel există un cuvânt necunoscut (1) ce necesită să fie memorat.

De asemenea mereu există un progres în ghicirea acestui cuvânt care trebuie memorat (2).

Jocul se termină atunci când fie este ghicit, fie se epuizează numărul de câte ori putem ghici. (3).

Acțiunile pe care un utilizator le face sunt:
- alegerea unei litere
- vizualizarea numărului rămas de încercări
- vizualizarea progresului

</details>

2. Cunoscând aceste informații, scrieți declararea clasei (adică doar fișierul header, nu neapărat și implementarea) care să encapsuleze logica aplicației. Păstrați datele ca fiind private și neaccesibile din exterior și doar acțiunile să fie publice.

**Atenție!**

Logica aplicației este diferită de logică introducerii datelor, astfel în clasa pe care o creați, ar trebui să vă concentrați doar pe regulile necesare jocului.

<details>
<summary></summary>

[Link](https://github.com/Ionnier/poo-wps/commit/33414b504a651c28bf3e578c25b66528c063ac9b)

</details>

3. Analizați clasa scrisă și gândițivă cum ați folosi-o. Dacă ea acoperă toate cazurile de care aveți nevoie, atunci implementați-o (adăugând la nevoie alte funcții auxiliare). Testați cât mai orice implementați (în funcția main).

<details>
<summary></summary>

[Link](https://github.com/Ionnier/poo-wps/commit/44ee06f24495a78f485d7e73a36e3376ef19ba90)

</details>

4. Implementați în funcția main introducerea datelor de la tastatură (și afișarea) ca să jucați jocul prin intermediul clasei create anterior. (creați la nevoie alte funcții)

<details>
<summary></summary>

Instanțiem clasa cu un cuvânt oarecare (hardcodat). 

Citim de la tastatură cât timp mai avem vieți până când terminăm jocul.

Creăm funcții adiționale pentru aceste verificări.

[Link](https://github.com/Ionnier/poo-wps/commit/11afe0b40f505bc8658dda666e9a892827d661bd)

</details>

5. Implementarea de bază a jocului ar trebui să fie gata. Continuăm implementarea logicii adiționale din cerință: cuvânt aleator.

Cuvântul aleator nu este ceva ce ține de logica de bază a jocului de spânzurătoarea, de aceea el ar trebui să fie separat. Evident, putem să implementăm acest lucru în mai multe metode:
* un fișier cu cuvinte separate
* un cuvânt din caractere aleatoare

În general preferăm metoda cea mai simplă care respectă specificațiile. Creăm un vector cu mai multe cuvinte din care luăm unul aleator.

Separați cât mai mult logica ca să imbunătățiți reutilizarea de cod (chiar dacă ea nu se întâmplă)

<details>
<summary></summary>
[Link](https://github.com/Ionnier/poo-wps/commit/26e7931d4007eaad560c98ab10592c2ebb553114) 
</details>

6. Implementați logică pentru dificultate.

<details>
<summary></summary>
Cerința menționează:

 - pool de cuvinte diferit per dificultate
 - litere cunoscute
 - numar de vieți mai mare

Momentan avem o clasă de Spânzurătoarea ce acceptă un cuvânt ce trebuie ghicit și un număr de vieți.

Vom considera 3 dificultăți, ușor, mediu, dificil.[detalii auxiliare](#enums) 

Pentru a adăuga dificultatea, ar trebui să creăm un alt constructor care să accepte 
Dacă creăm un alt constructor -> nu putem apela constructorul deja creat, și preferăm să nu duplicăm logica, astfel creăm o funcție separată.

Există două metode de abordare a acestei probleme.
* la nivel de compilare -> creăm 3 funcții `getCuvinteUsoare`, `getCuvinteMedii`, `getCuvinteGrele` ce returneaza cuvintele corespunzatoarea
* la nivel de rulare -> cream un singur vector de cuvinte, si filtram cuvintele in functie de dificultate, dacă putem crea o funcție de calculare a dificultății

Acesta reprezintă un detaliu de implementare, în care alegerea este a voastră. Însă alegerea trebuie făcută gândidu-ne la principiile de dezvoltare software, în care în general ne interesează portabilitatea și ușurința de extindere.

Dacă peste câteva luni vrem să adăugăm cuvinte noi, vom putea să ne amintim cum am ales această partiționare? De asemenea, de fiecare dată când vrem să adăugăm cuvinte noi vrem să calculăm noi manual dificultatea unui cuvânt și după să îl adăugăm?

În general, preferăm ca atunci când vrem să adăugăm, să modificăm cât mai puțin și să funcționeze fără să cauzeze probleme neașteptate.

Abordarea aleasă de mine:
- crearea unui vector cu multe cuvinte
- crearea unei funcții ce returnează dificultatea unui cuvânt pe baza unui algoritm

[Analizați implementarea](https://github.com/Ionnier/poo-wps/commit/35b2e455474438ce4b6846a583b081d149ff550d) pentru obtinerea unui cuvant de o anumita dificultate din perspectiva cat de usor este sa adaugam alta dificultate sau alte cuvinte. (recomandat sa va familiarizati cu conceptul de [static](https://github.com/mcmarius/poo/tree/master/tema-2#func%C8%9Bii-%C8%99i-atribute-statice))

[Implementarea dificultatii](https://github.com/Ionnier/poo-wps/commit/4ac291100c36e83e48ddde2f31d2b7c80f26bb0c)
</details>

7. Implementați salvarea stări și revenirea

<details>
<summary></summary>
Cerința este ambiguă întrucât este la latitudinea alegerii voastre ce înseamnă să salvați starea și să reveniți.

* puteți să interpretați alegerea ca salvarea stării la ieșirea din program (adică sa salvați ceva pe disc)
* să interpretați ca ieșitul din jocul curent și întoarcerea la meniul principal.

Ca întotdeauna, preferăm varianta mai simplă ce respectă specificația, adică a doua cerință.

Întrucât modul în care am scris codul păstrează logica în obiectul Spanzuratoarea, se referă strict să menținem starea mai multor obiecte de tip Spanzuratoarea într-un vector și alegerea unuia dintre ele.

[Solutie](https://github.com/Ionnier/poo-wps/commit/dedda6744fcdc1d904a001b0c7a924d528565a72)

</details>

8. Crearea scorurilor
<details>
<summary></summary>
Momentan am implementat jocul de Spanzuratoarea + dificultatea (care reprezinta doar modul cum instanțiem jocul).

În programul scris până acum există două componente. Jocul (clasa Spanzurătoarea) și funcția main (care ar trebui să fie o clasă separată).

Scorul este ceva ce poate fi gândit din două perspective

* aparține instanției curente a jocului (clasa Spanzuratoarea)
* este extern jocului și aparține componentei care rulează clasa (funcția main)

Evident, alegem varianta cea mai simplă ce îndeplinește specificațiile, adică prima, acest lucru presupunand ca înseamnă ca la nivelul cel mai simplu, un jucător primeste 10 puncte pe răspuns corect și un multiplicator pentru un număr consecutiv de răspunsuri.

[Link](https://github.com/Ionnier/poo-wps/commit/aa7485604c99d9d7438ecaa685a259a150b72757)
</details>


9. Crearea leaderboard-urilor locale

<details>
<summary>
</summary>
Un leaderboard local poate fi suma scorurilor pentru jocurile memorate.

In acest caz iarasi sunt doua optiuni
* fiecare joc va fi detinut de un utilizator
* fiecare utilizator va "detine" mai multe jocuri

In general, preferam sa nu facem prea multa logica in cadrul unei singure clase, de accea posibil sa preferam a doua varianta, chiar daca sunt necesare mai multe modificari.

[Link](https://github.com/Ionnier/poo-wps/commit/2ae730d381f9e5222d38fe7a60ba5c6e3be3d353)

</details>

10. Cleanup

    În general, în timpul dezvoltării alegem varianta cea mai simplă pentru a livra un produs cât mai repede, însă la finalul proiectului avem o altă perspectivă asupra modului cum putem scrie clasele, de aceea există o etapă de refactoring, ca să îmbunătățim mentanibilitatea codului.

## Bibliotecă

1. Familiarizați-vă cu conceptul de funcții și variabile [statice](https://github.com/mcmarius/poo/tree/master/tema-2#func%C8%9Bii-%C8%99i-atribute-statice).

2. Creați clasele necesare pentru a modela datele unei biblioteci. Considerăm că o bibliotecă are ca dată membră doar un vector de cărți identificate prin titlu și autor.

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/778911753f0e5f3c35fcf8afab09049477b8abd8)
</details>

3. Folosind variabile si functii statice creați un contor "automat" pentru numărul de obiecte de tip Carte.

<details>
Adaugati o variabila statica numita contor.
Incrementati contorul in constructorul clasei carte. Decrementați-o în destructor.
Creati un getter pentru acest contor.

[Link](https://github.com/Ionnier/poo-wps/commit/0825369e720141cacdff829275fc29d30f6b80b0) 
</details>

4. Folosind variabile si funcții statice creați pentru fiecare obiect de tip carte un ID unic.

<details>
Adăugați o variabilă statică numită idGenerator.
Incrementați-o și asociați-o în constructorul clasei Carte.

[Link](https://github.com/Ionnier/poo-wps/commit/187b23d99b832033ef2b19fe4216de86f3aca951)
</details>

5. Familiarizați-vă cu conceptul de moștenire, funcții virtuale, upcasting și downcasting.
([longer more explicit](https://github.com/mcmarius/poo/tree/master/tema-2#mo%C8%99teniri), [shorter but less clear](https://github.com/Ionnier/poo/tree/main/labs/L04#mo%C8%99tenirea))

6. Întrucât o bibliotecă nu depozitează doar cărți modificați codul anterior scris pentru a folosi în locul clasei "Carte" o clasa "Object" mai generică. Clasa "Object" ar trebui sa păstreze doar logica de generare a ID-ului și contorul, iar restul să fie într-o clasă derivată carte.

Foloșiți optiunea de "Refactor" din CLion.

<details>
Implementare partiala:
[Link](https://github.com/Ionnier/poo-wps/commit/b92c99947e04dbb4d5b272d28946bfea18e46b69)
</details>

7. Completați codul anterior pentru a stoca pointeri la clasa de baza în loc de obiecte concrete de tipul clasei de bază.

Atunci când știm că vom lucra cu obiecte derivate vom folosi exclusiv **pointeri** și **referințe**. ([tangențial descriere aici](https://github.com/Ionnier/poo/tree/main/labs/L04#probleme-cu-upcasting-early-binding))

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/1e8e50266a181393640e9199c4c5c2ea739c6baf)
</details>

8. Suprascrieți funcția de afișare în Clasa carte pentru a funcționa atunci când o apelăm din pointer la clasa de bază.

Toate funcțiile pe care le vom rescrie în clasa derivată trebuie să fie marcate ca **virtual**.

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/dd2a0cbc07457b1279e0a18e073d539901d7aa44)
</details>

9. Ce se întâmplă dacă nu marcăm funcția ca virtual în clasa de bază?

10. Modificați destructorul clasei obiect și al clasei Carte pentru a afișa un mesaj. Ce observați?

11. Fixați problema de la punctul anterior.

Orice clasa ce va fi derivata **trebuie** să aibă destructor virtual.

12. Modificați clasa `Object` pentru a fi considerată o clasa abstractă. ([see this](https://github.com/Ionnier/poo/tree/main/labs/L04#clase-abstracte))

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/f555b5eed118f4d4d60feacf10a8dbab3ac3cb36)
</details>

13. Adăugați o nouă clasă numită `Revista` ce are ca date memebre numele, anul și luna apariției. Ea trebuie să fie o clasă derivată a clasei 'Obiect'.

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/f555b5eed118f4d4d60feacf10a8dbab3ac3cb36)
</details>

14. Se considera că o carte are valoarea 5 și o revistă are valoare 2. Calculați valoarea totală ce ar avea-o toate obiectele dintr-o bibliotecă la un loc.

<details>
[Link](https://github.com/Ionnier/poo-wps/commit/c789e46d09aa371a2aee122f036594ee46b276f5)
</details>

15. Folosiți [dynamic_cast](https://github.com/Ionnier/poo/blob/main/labs/L04/README.md#smarter-downcast-dynamic-cast) sau [type_info](https://github.com/Ionnier/poo/blob/main/labs/L04/README.md#typeinfo) pentru a număra obiectele de fiecare tip bibliotecă.

<details>
Iterați prin vectorul de obiecte și verificați tipul fiecărui element, incrementând numărul de elemente. 

[Link](https://github.com/Ionnier/poo-wps/commit/c7e226499eba4d9aca2c28932ce5ccab38c100ea)
</details>

16. Ce s-ar întâmpla dacă nu am avea funcții virtuale în contextul dynamic_cast?

## Logger

O clasă *Logger* este o componentă software care se ocupă de înregistrarea (logarea) evenimentelor, mesajelor sau erorilor care apar într-o aplicație sau sistem. Scopul principal al unei astfel de clase este de a furniza o metodă centralizată de a captura informații relevante despre starea aplicației pe măsură ce aceasta rulează, oferind astfel o modalitate eficientă de monitorizare și depanare.

Se dorește implementarea unei ierarhii de clase pentru logarea mesajelor într-o aplicație. Clasa principală va fi o clasă abstractă `Logger`, iar aceasta va fi extinsă de trei clase derivate: `ConsoleLogger`, `FileLogger` și `LoggerDistributor`.

#### Detalii:

1. **Clasa `Logger`**:

   * Este o clasă abstractă, care va defini metodele de bază pentru logarea mesajelor.
   * Mesajele logate vor avea un format standardizat: `W 2024.10.23 14:35 [nume mesaj]`, unde `W` reprezintă nivelul logului.

2. **Nivelele de Severitate**:

   * Vor exista cinci nivele de severitate ale mesajelor:

     * **D** (Debug): Detalii tehnice pentru depanare.
     * **W** (Warn): Avertismente ce semnalează posibile probleme.
     * **I** (Info): Mesaje de informare despre evenimente normale.
     * **E** (Error): Mesaje de eroare care indică o problemă.
     * **T** (Trace): Mesaje de urmărire detaliată, folosite pentru debugging.

3. **Metode**:

   * Clasa `Logger` va include o metodă abstractă `log(message, level)` pentru logarea mesajelor.
   * De asemenea, va exista o metodă `setLogLevel(level)` pentru a seta nivelul minim de severitate pentru mesajele logate.

4. **Clase derivate**:

   * **ConsoleLogger**: Va scrie mesajele de log pe consolă (folosind `cout`).
   * **FileLogger**: Va scrie mesajele într-un fișier.
   * **LoggerDistributor**: Va trimite mesajele de log către mai multe instanțe de `Logger` (de exemplu, atât către un `ConsoleLogger`, cât și către un `FileLogger`).

5. **Funcționalitate**:

   * Clasa `LoggerDistributor` va permite logarea mesajelor simultan în mai multe destinații.
   * Mesajele vor fi afișate doar dacă nivelul de severitate al acestora corespunde sau este mai grav decât nivelul setat pentru logare.

## Imobiliare

Un fond de investiții american dorește să intre pe piața imobiliarelor din București și
are nevoie de o aplicație în C++ pentru a-și administra proprietățile.

Aceștia au un set de reguli pentru fiecare proprietate, fiecare dintre aceasta va avea un ID, 
incrementat automat. Unul dintre cei mai importanți factori reprezintă poziția locuinței, 
astfel acesta poate fi central, periferic sau între cele două. Pentru fiecare dintre acestea, indiferent
de proprietate prețul final de cumpărare va fi majorat cu 100%, 25% sau 50% în funcție de poziție.

Tipurile de proprietăți în care aceștia vor să investeasc sunt garsoniere, apartamente și case.

Pentru fiecare dintre acestea, se cunoaște o regulă internă cu care aceștia le calculează
valoarea unui imobil luând în calcul că prețul pe metru pătrat (m^2) este de 2000$ 

Pentru garsoniere, valoare se calculează după formula: suprafață utilă * preț m^2, 
înmulțit cu 1.25 dacă are o bucătărie separată.

Pentru apartamente, valorea se calculează prețul de bază după formula: suprafață totala * preț m^ la care se adaugă
  - 20% pentru fiecare cameră peste 2.
  - 10% dacă apartamentul este la un etaj inferior (maxim 80% pentru etajul 1 și -20% dacă este la parter sau demisol)
  - 25% dacă apartamentul este într-un bloc de maxim 4 etaje
  - 5% pentru fiecare 10 ani cu care blocul este mai nou față de 1960 (30% pentru blocuri > 2020)

Pentru case, valoarea se calculează prețul de bază după formula: suprafață construită * preț m^2 + teren disponibil * pret m^2 * 0.5 la care se adaugă:
  - 25% pentru fiecare etaj construit
  - 10% pentru fiecare cameră
  - 5% dacă are piscină

Cerințe:
  - adăugarea a unui număr variabil de imobiliare
  - afișarea tuturor imobiliarelor
  - afișarea valorii fiecărui imobiliar
  - afișarea imobiliarelor ordonate descrescător în funcție de valoare
  - afișarea numărului de imobiliare de fiecare tip 

## Side notes

### Enums

Când avem variabile de acest tip (dificultate cu 3 valori), în general suntem tentați să le reprezentăm fie prin string-uri ("usor", "mediu", "dificil"), int-uri (0, 1, 2) sau boolene. 

Atunci când folosim aceste dificultăți însă nu suntem expliciți, de exemplu

```c++
/// NU !!!
Spanzuratoarea getGame(int dificulty) {
    if (dificulty = 0) {
        return easyGame()
    }

    if (dificulty = 1) {
        return mediumGame()
    }
}
/// NU !!!
```

Este un **anti pattern** numit [magic numbers](https://en.wikipedia.org/wiki/Magic_number_(programming)). Folosirea de constante în cod devenind dificil să întelegem ce înseamnă cu adevărat.

Pentru a reprezenta variabile în acest tip, în C se creau constante la un nivel cât mai înalt și folosite.

```c++
const int DIFICULTY_LOW = 0
const int DIFICULTY_MEDIUM = 1
const int DIFICULTY_HARD = 2

Spanzuratoarea getGame(int dificulty) {
    if (dificulty = DIFICULTY_LOW) {
        return easyGame()
    }

    if (dificulty = DIFICULTY_MEDIUM) {
        return mediumGame()
    }
}
```

În limbajele moderne există enum-uri.

```c++
enum Dificulty
{
    LOW,
    MEDIUM,
    HARD,
};
```

Enum-urile sunt defapt alias-uri tot pentru niște constante generate de compilator și oferă mai mult context.

Din C++11 există enum classes, care sunt mai avansate întrucât pot fi instanțiate și nu sunt doar int-uri.