#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

enum LogLevel
{
    DEBUG = 4,
    WARN = 3,
    INFO = 2,
    ERROR = 1,
    TRACE = 0
};

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


class Logger
{
protected:
    int time; //in minutes
    std::string date;
    LogLevel level;

public:
    virtual void log(std::string message, LogLevel level) {};

    Logger(int time, std::string date, LogLevel log_level): 
    time(time), date(date), level(log_level)
    {
    }

    void setLogLevel(LogLevel level_){
        level = level_;
    }

    LogLevel getLogLevel(){
        return level;
    }
};


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

    FileLogger(int time, std::string date, LogLevel log_level, std::string file_path):
    Logger(time, date, log_level), fout(file_path)
    {
    }

    void log(std::string message, LogLevel level)
    {
        fout<<to_char(level)<<" "<<date<<" "<<time<<"\n";
        std::cout<<"cu mesajul: "<<message<<"\n\n";
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
    ConsoleLogger cl1(120, "28.10.2025", LogLevel::DEBUG);
    ConsoleLogger cl2(220, "28.08.2025", LogLevel::ERROR);
    FileLogger fl1(120, "28.10.2025", LogLevel::DEBUG, "./log.txt");

    // LogLevel este cel minim
    LoggerDistributor log_manager(120, "30.10.2025", LogLevel::ERROR);

    cl1.log("test error", LogLevel::ERROR);
    cl1.log("other rror", LogLevel::ERROR);

    cl2.log("debug log", LogLevel::DEBUG);

    fl1.log("test log", LogLevel::WARN);


    Logger *clogger = new ConsoleLogger(120, "28.10.2025", LogLevel::DEBUG);
    Logger *flogger = new FileLogger(120, "28.10.2025", LogLevel::DEBUG, "./log.txt");

    clogger->log("msg", LogLevel::DEBUG);
    flogger->log("msg", LogLevel::DEBUG);

    log_manager.log("da", {clogger, flogger});

    return 0;
}