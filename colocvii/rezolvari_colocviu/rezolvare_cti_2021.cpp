#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Jucarie{
protected:
    string m_denumire;
    float m_dimensiune;
    string m_tip;

    virtual void print(ostream& os) const{
        os << this->m_denumire << " " << this->m_dimensiune << " " << this->m_tip << " ";
    }

    virtual void read(istream& os){
        cout << "Denumire: ";
        os >> this->m_denumire;
        cout << "Dimensiune: ";
        os >> this->m_dimensiune;
        cout << "Tip: ";
        os >> this->m_tip;

    }

public:
    Jucarie() = default;
    Jucarie(const string& p_denumire, float p_dimensiune,const string& p_tip):
        m_denumire(p_denumire), m_dimensiune(p_dimensiune), m_tip(p_tip) {}

    friend ostream& operator<<(ostream& os, const Jucarie& jucarie){
        jucarie.print(os);
        return os;
    }

    friend istream& operator>>(istream& os, Jucarie& jucarie){
        jucarie.read(os);
        return os;
    }
};

class JucarieClasica : public Jucarie{
private:
    string m_material;
    string m_culoare;

    void print(ostream& os) const{
        Jucarie::print(os);
        os << m_material << " " << m_culoare << " ";
    }

    void read(istream& os){
        Jucarie::read(os);
        cout << "Material: ";
        os >> this->m_material;
        cout << "Culoare: ";
        os >> this->m_culoare;
    }

public:
    JucarieClasica() = default;
    JucarieClasica(const string& p_denumire, float p_dimensiune, const string& p_tip, const string& p_material, const string& p_culoare) :
        Jucarie(p_denumire, p_dimensiune, p_tip), m_material(p_material), m_culoare(p_culoare) {}
};

class JucarieEducativa : virtual public Jucarie{
protected:
    string m_abilitate;

    void print(ostream& os)const{
        Jucarie::print(os);
        os << m_abilitate << " ";
    }

    void read(istream& os){
        Jucarie::read(os);
        cout << "Abilitate: ";
        os >> this->m_abilitate;
    }
public:
    JucarieEducativa() = default;
    JucarieEducativa(const string& p_denumire, float p_dimensiune, const string& p_tip, const string& p_abilitate) :
        Jucarie(p_denumire, p_dimensiune, p_tip), m_abilitate(p_abilitate) {}
};

class JucarieElectronica : virtual public Jucarie{
protected:
    int m_nrBateri;

    void print(ostream& os)const{
        Jucarie::print(os);
        os << m_nrBateri << " ";
    }

    void read(istream& os){
        Jucarie::read(os);
        cout << "Nr Baterii: ";
        os >> this->m_nrBateri;
    }
public:
    JucarieElectronica() = default;
    JucarieElectronica(const string& p_denumire, float p_dimensiune,const string& p_tip,int p_nrBateri):
        Jucarie(p_denumire,p_dimensiune,p_tip), m_nrBateri(p_nrBateri) {}
};

class JucarieModerna : public JucarieEducativa, public JucarieElectronica {
private:
    string m_brand;
    string m_model;

    void print(ostream& os) const{
        JucarieEducativa::print(os);
        os<<m_nrBateri<<" "
          <<m_brand<<" "
          <<m_model<<" ";
    }
    void read(istream& os){
        Jucarie::read(os);
        cout << "Brand: ";
        os >> this->m_brand;
        cout << "Model: ";
        os >> this->m_model;
    }

public:
    JucarieModerna() {
        this->m_abilitate = "generala";
        this->m_nrBateri = 1;
    }
    JucarieModerna(const string& p_denumire, float p_dimensiune,const string& p_tip,const string& p_brand,const string& p_model):
    JucarieEducativa(p_denumire, p_dimensiune, p_tip, "generala"), m_brand(p_brand), m_model(p_model) {
        this->m_nrBateri=1;
    }
};
class Copil{
    protected:
    static int global_id;
    int m_copil_id;
    string m_nume;
    string m_prenume;
    string m_adresa;
    int m_varsta;
    int m_nrFapteBune;
    vector<Jucarie> m_jucarii;
    virtual void print(ostream& os) const {
        os<<this->m_copil_id<<" "<<this->m_nume<<" "<<this->m_prenume<<" "<<this->m_adresa<<" "<<this->m_varsta<<" "<<this->m_nrFapteBune<<"\n";

        for(const auto jucarie:this->m_jucarii){
            os<<jucarie<<"\n";
        }
    }
    virtual void read(istream& os) {
        cout<<"Nume: ";
        os>>this->m_nume;
        cout<<"Prenume: ";
        os>>this->m_prenume;
        cout<<"Adresa: ";
        os>>this->m_adresa;
        cout<<"varsta: ";
        os>>this->m_varsta;
        cout<<"Nr Fapte Bune: ";
        os>>this->m_nrFapteBune;
/*
        if(this->m_nrFapteBune < 10)
            cout<<"Fapte bune insuficiente.",
            this->m_nrFapteBune = 10;
*/
        cout << this->m_nrFapteBune << " jucarii:\n";
        for(int i=0; i<this->m_nrFapteBune; i++){
            Jucarie j;
            os >> j;
            this->addJucarie(j);
        }
    }
public:
    Copil(){
        m_copil_id = global_id++;
    };
    Copil(const string& p_nume,const string& p_prenume, const string& p_adresa,int p_varsta,int p_nrFapteBune):
        m_copil_id(global_id++),
        m_nume(p_nume),
        m_prenume(p_prenume),
        m_adresa(p_adresa),
        m_varsta(p_varsta),
        m_nrFapteBune(p_nrFapteBune){
    }

    const int& getVarsta() const { return m_varsta; }
    const int& getNrFapteBune() const { return m_nrFapteBune; }

    const string& getNume() const
    {
        return m_nume;
    }

    friend ostream& operator<<(ostream& os,const Copil& copil){
        copil.print(os);
        return os;
    }
    friend istream& operator>>(istream& os,Copil& copil){
        copil.read(os);
        return os;
    }

    void addJucarie(const Jucarie& p_jucarie){
        m_jucarii.push_back(p_jucarie);
    }
};

class CopilCuminte : public Copil {
    int m_nrDulciuri;
public:
    CopilCuminte() = default;
    CopilCuminte(const string& p_nume,const string& p_prenume, const string& p_adresa,int p_varsta,int p_nrFapteBune, int p_nrDulciuri) :
        Copil(p_nume, p_prenume, p_adresa, p_varsta, p_nrFapteBune), m_nrDulciuri(p_nrDulciuri) {}
    void print(ostream& os) {
        Copil::print(os);
        os << m_nrDulciuri;
    }
    void read(istream& os) {
        Copil::read(os);
        cout << "Numar dulciuri: ";
        os >> m_nrDulciuri;
    }
};

class CopilNeastamparat : public Copil {
    int m_nrCarbuni;
public:
    CopilNeastamparat() = default;
    CopilNeastamparat(const string& p_nume,const string& p_prenume, const string& p_adresa,int p_varsta,int p_nrFapteBune, int p_nrCarbuni) :
        Copil(p_nume, p_prenume, p_adresa, p_varsta, p_nrFapteBune), m_nrCarbuni(p_nrCarbuni) {}
    void print(ostream& os) {
        Copil::print(os);
        cout << "Numar carbuni: ";
        os << m_nrCarbuni;
    }
    void read(istream& os) {
        Copil::read(os);
        os >> m_nrCarbuni;
    }
};

int Copil::global_id=0;

bool comp (const Copil &a, const Copil &b) {
    return a.getVarsta() < b.getVarsta();
}

void sortVarsta(vector<Copil> &V) {
    sort(V.begin(), V.end(), &comp);
}

bool comp1 (const Copil &a, const Copil &b) {
    return a.getNrFapteBune() > b.getNrFapteBune();
}

void sortNrFapteBune(vector<Copil> &V) {
    // sort(V.begin(), V.end(), &comp1);
    sort(V.begin(), V.end(), [](const Copil &a, const Copil &b) -> bool {
    return a.getNrFapteBune() > b.getNrFapteBune();});
}

void cautareCopil(vector<Copil> V, string nume_de_cautat)
{
    for(auto &copil:V)
    {

        if(copil.getNume().find(nume_de_cautat) != string::npos)
            cout<<copil<<'\n';

        //if(copil.getNume() == nume_de_cautat)
          //  cout<<copil<<'\n';
    }
}

int main()
{
    //Jucarie j("Barbie",20.0f,"Papusa");
    //cout << j << endl;
    Copil c;
    //cin>>c;
    //cout << c;
    JucarieModerna j;
    CopilCuminte fo;
    CopilNeastamparat co;
    cin >> co;
    cout << co;
    //cin >> fo;
    /*
    cin>>j;
    cout<<j;
    cout << "\n";
    vector<Copil> V;
    V.push_back(Copil("popescu", "p1", "a1", 12, 1));
    V.push_back(Copil("ana", "p1", "a2", 5, 110));
    V.push_back(Copil("anaMaria", "p1", "a3", 22, 10));

    /// cautareCopil(V, "ana");

    sortVarsta(V);
    for (const auto& copil: V) {
        cout << copil << endl;
    }
    cout << '\n' << '\n';
    sortNrFapteBune(V);
    for (const auto& copil: V) {
        cout << copil << endl;
    }

    */
    return 0;
}
