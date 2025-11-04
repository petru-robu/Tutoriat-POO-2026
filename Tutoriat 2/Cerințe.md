> Credite: https://github.com/Ionnier/poo-wps/blob/main/lab/L04.md

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