#include <iostream>
#include <vector>
#include <algorithm>

enum NumeProba
{
    SPRINT = 0,
    CROS = 1,
    SEMI = 2,
    MARATON = 3
};

std::ostream& operator<<(std::ostream& out, const NumeProba& nume)
{   
    switch(nume)
    {
        case NumeProba::SPRINT:
            out<<"SPRINT";
            break;
        case NumeProba::CROS:
            out<<"CROS";
            break;
        case NumeProba::SEMI:
            out<<"SEMI";
            break;
        case NumeProba::MARATON:
            out<<"MARATON";
            break;
        default:
            out<<"Proba invalida!";
            break;
    } 
    return out;
}

class Proba
{
private:
    NumeProba nume;
    float perf;

public:
    Proba(NumeProba np, float pf): nume(np), perf(pf)
    {}

    Proba()
    {}

    float score() const
    {
        switch(nume)
        {
            case NumeProba::SPRINT:
                return perf < 10 ? 10 : 90/perf;
                break;
            case NumeProba::CROS:
                return perf < 30 ? 10 : 120/perf;
                break;
            case NumeProba::SEMI:
                return perf > 50 ? 10 : perf/5;
                break;
            case NumeProba::MARATON:
                return perf > 50 ? 10 : perf/5;
                break;
            default:
                return -1;
                break;
        } 
    }

    friend std::ostream& operator<<(std::ostream& out, const Proba& p)
    {
        out<<"Proba: "<<p.nume<<"\n";
        
        if(p.nume == NumeProba::SPRINT || p.nume == NumeProba::CROS)
            out<<"Timpul scos: ";
        else
            out<<"Distanta parcursa: ";
        out<<p.perf<<"\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Proba& p)
    {
        std::cout<<"Selectati un tip de proba: SPRINT(0), CROS(1), SEMI(2), MARATON(3): ";
        int tip;
        in >> tip;

        switch(tip)
        {
            case 0:
                p.nume = NumeProba::SPRINT;
                break;
            case 1:
                p.nume = NumeProba::CROS;
                break;
            case 2:
                p.nume = NumeProba::SEMI;
                break;
            case 3:
                p.nume = NumeProba::MARATON;
                break;
        }
        std::cout<<"\n";
        std::cout<<"Perf: ";
        in >> p.perf;
        
        return in;
    } 
};

class Candidat
{
private:
    std::string nume, prenume, data;
    Proba proba;
    
public:
    Candidat(const std::string& nume, const std::string& prenume, const std::string& data, 
    const Proba& proba):
    nume(nume), prenume(prenume), data(data), proba(proba)
    {}

    Candidat()
    {}

    const Proba& get_proba() const
    {
        return proba;
    }

    friend std::ostream& operator<<(std::ostream& out, const Candidat& c)
    {
        out<<"Nume: "<<c.nume<<"\n";
        out<<"Prenume: "<<c.prenume<<"\n";
        out<<"Data nasterii: "<<c.data<<"\n";

        out<<c.proba;
        return out;
        // + (2 3) = 5
        // cout << c <-> <<(cout, c)
    }  

    friend std::istream& operator>>(std::istream& in, Candidat& c)
    {   
        std::cout<<"---------Citire candidat---------\n";
        std::cout<<"Nume: ";
        in >> c.nume;
        std::cout<<"Prenume: ";
        in >> c.prenume;
        std::cout<<"Data: ";
        in >> c.data;
        std::cout<<"---------Citire proba---------\n";
        in>>c.proba;


        return in;
    } 

    bool operator<(const Candidat& c)
    {
        return c.get_proba().score() < this->get_proba().score();
    }
};


class ManageApp
{
private:
    const int secret_code = 123456;
    std::vector<Candidat> candidates;

    void pick_best(int limit)
    {
        std::sort(candidates.begin(), candidates.end(),
        [](const Candidat& c1, const Candidat& c2){return c1.get_proba().score() > c2.get_proba().score();});

        std::cout<<"Candidati alesi: ";
        int idx = 0;
        for(auto &cand:candidates)
        {
            if(idx >= 3)
                break;
            
            std::cout<<cand<<' '<<cand.get_proba().score()<<'\n';
            idx ++;
        }
    }

    void inscriere()
    {
        int n;
        std::cout<<"introduceti nr de candidati: ";
        std::cin>>n;

        while(n--)
        {
            Candidat c1;
            std::cin>>c1;
            candidates.push_back(c1);
        }
    }


    void inchiere_inscriere()
    {
        int code;
        std::cout<<"Enter admin code: ";
        std::cin>>code;
        
        while(code != secret_code)
        {
            std::cout<<"Wrong! Try again!\n";
            std::cout<<"Enter admin code: ";
            std::cin>>code;   
        }

        pick_best(3);
    }

public:
    ManageApp()
    {}

    void run()
    {
        inscriere();
        inchiere_inscriere();
    }
};


int main()
{
    ManageApp app;
    app.run();
    return 0;
}


/*
Pentru alta data
Polimorfism:


class Proba
{
    std::string nume;


    virtual void score() = 0;
}

class Sprint : public Proba
{
    int timp;

    void score() override
    {
        return timp > 10;
    }
}

class Semi : public Proba
{
    int distanta;

    void score() override
    {
        return dist > 50;
    }
}




int main()
{
    Proba* sprint = new Sprint(), semi = new Semi();

    vector<Proba*> v;

    for(auto &proba:v)
        cout<<proba->score();
}

----

*/