#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

// Enum - Tip de date special care grupează constante numerice
enum LogLevel
{
    DEBUG = 4,
    WARN = 3,
    INFO = 2,
    ERROR = 1,
    TRACE = 0
};

// Funcție care convertește Enum -> Char
// Este necesară și implementarea inversă a acesteia
// Se poate folosi și un dicționar sub forma
// std::unordered_map<LogLevel, char> conv;
std::string to_char(LogLevel log_level)
{
    if(log_level == LogLevel::DEBUG)
        return "D";
    else if(log_level == LogLevel::WARN)
        return "W";
    else if(log_level == LogLevel::INFO)
        return "I";
    else if(log_level == LogLevel::ERROR)
        return "E";
    else if(log_level == LogLevel::TRACE)
        return "T";
    
    return "";
}

// Clasă de bază - Logger
class Logger
{
protected:
    int time; // în minute
    std::string date;
    LogLevel level;

public:
    // Definirea unei funcții virtuale (nu e pură)
    virtual void log(std::string message, LogLevel level) {};

    // Definirea constructorului, cu listă de inițializare
    Logger(int time, std::string date, LogLevel log_level): 
        time(time), date(date), level(log_level)
        {
        }

    // Setter pentru modificarea din nivel public a 
    // unui atribut privat
    void setLogLevel(LogLevel level_){
        level = level_;
    }

    // Getter pentru accesarea din nivel public a
    // unui atribut privat
    LogLevel getLogLevel(){
        return level;
    }
};


// Console Logger 
class ConsoleLogger : public Logger
{
public:
    ConsoleLogger(int time, std::string date, LogLevel log_level):
    Logger(time, date, log_level)
    {
    }

    void log(std::string message, LogLevel level)
    {
        std::cout<<to_char(level)<<" "<<date<<" "<<time<<"\n";
        std::cout<<"cu mesajul: "<<message<<"\n\n";
    }
};

class FileLogger : public Logger
{
private:
    std::ofstream fout;

public:

    // Constructor cu listă de inițializare
    // În lista de inițializare se inițializează
    // obiectul părinte Logger
    FileLogger(int time, std::string date, LogLevel log_level, std::string file_path):
    Logger(time, date, log_level), fout(file_path)
    {
    }

    void log(std::string message, LogLevel level)
    {
        fout << to_char(level) << " " <<date << " " << time << "\n";
        std::cout << "cu mesajul: "<< message << std::endl << std::endl;
    }
};


class LoggerDistributor : public Logger
{

public:
    LoggerDistributor(int time, std::string date, LogLevel log_level) : Logger(time, date, log_level) {}
 
    void log(std::string message, std::vector<Logger*> current_logger){
        for (const auto &logger : current_logger){
            if (logger->getLogLevel() >= level){
                logger->log(message, LogLevel::INFO);
            }
        }
    }

    virtual ~LoggerDistributor() = default;
};


int main()
{
    // Inițializăm două obiecte ConsoleLogger, care are constructorul
    // ConsoleLogger(int time, std::string date, LogLevel log_level)
    ConsoleLogger cl1(120, "28.10.2025", LogLevel::DEBUG);
    ConsoleLogger cl2{220, "28.08.2025", LogLevel::ERROR};

    // Inițializăm un obiect FileLogge, care are constructorul
    // FileLogger(int time, std::string date, LogLevel log_level, std::string file_path)
    FileLogger fl1{120, "28.10.2025", LogLevel::DEBUG, "./log.txt"};

    // Observație: Putem folosi nume_obiect() sau nume_obiect{}

    // Apelarea funcției virtuale .log, care are efecte 
    // diferite în funcție de obiectul care o apelează
    cl1.log("test error", LogLevel::ERROR);
    cl1.log("other rror", LogLevel::ERROR);

    cl2.log("debug log", LogLevel::DEBUG);

    fl1.log("test log", LogLevel::WARN);


    // Definirea unor pointeri la obiecte
    // Vom avea nevoie de pointeri pentru RTTI / Dynamic Cast
    Logger *clogger = new ConsoleLogger(120, "28.10.2025", LogLevel::DEBUG);
    Logger *flogger = new FileLogger(120, "28.10.2025", LogLevel::DEBUG, "./log.txt");

    // Apelarea unei funcții dintr-un pointer care conține un 
    // obiect nu se mai face prin . ci prin ->
    clogger->log("msg", LogLevel::DEBUG);
    flogger->log("msg", LogLevel::DEBUG);

    // LogLevel este cel minim
    LoggerDistributor log_manager(120, "30.10.2025", LogLevel::ERROR);
    log_manager.log("da", {clogger, flogger});

    return 0;
}