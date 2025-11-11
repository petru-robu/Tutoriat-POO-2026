#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <set>
using namespace std;

class drum{
protected:
    static uint32_t ID;
    string denumire;
    float lungime;
    uint32_t nr_tronsoane;
    drum(){
         ID++;
    }
    drum(float lungime,uint32_t nr_tronsoane):
                                lungime(lungime),
                                    nr_tronsoane(nr_tronsoane)
    {
         ID++;
    }

    virtual float getCost()=0;
    virtual void print(ostream& os) const{
        os<<denumire<<":"<< "lungime:"<<lungime<<" nr tronsoane:"<<nr_tronsoane<<'\n';
    }
    virtual void read(istream& is){
        cout<<"lungime:";
        is>>lungime;
        cout<<"nr tronsoane:";
        is>>nr_tronsoane;
        if(nr_tronsoane<1){
            throw invalid_argument("numarul de tronsoane trebuie sa fie minim 1");
        }
    }
    friend istream& operator>>(istream& is,drum& dr){
        dr.read(is);
        return is;
    }
    friend ostream& operator<<(ostream& os,const drum& dr){
        dr.print(os);
        return os;
    }
    virtual ~drum(){}
public:
     float getLungime(){
        return lungime;
    }
    std::string getDenumire(){
        return denumire;
    }

    int32_t getNrTronsoane(){
        return nr_tronsoane;
    }
};
uint32_t drum::ID=0;

class drum_national:public drum{
    uint32_t nr_judete;
public:
    drum_national(float lungime, uint32_t nr_tronsoane,uint32_t nr_judete):
        drum(lungime,nr_tronsoane),
        nr_judete(nr_judete)
    {
        denumire="DN"+to_string(ID);
    }
    drum_national(){
        denumire="DN"+to_string(ID);

    }
    float getCost(){
        return 3000*lungime/nr_tronsoane;
    }
    virtual void print(ostream& os) const {
        drum::print(os);
        os<<"nr jutete:"<<nr_judete;
    }
    virtual void read(istream& is){
        drum::read(is);
        cout<<"nr judete:";
        is>>nr_judete;
    }

};

class drum_european:public drum{
protected:
    uint32_t nr_tari;
public:
    drum_european(float lungime, uint32_t nr_tronsoane,uint32_t nr_tari):
        drum(lungime,nr_tronsoane),
        nr_tari(nr_tari)
    {
        denumire="E"+to_string(ID);
    }
    drum_european(){
        denumire="E"+to_string(ID);

    }
     float getCost(){
        return 3000*lungime/nr_tronsoane+500*nr_tari;
    }
    virtual void print(ostream& os) const {
        drum::print(os);
        os<<"nr tari:"<<nr_tari;
    }
    virtual void read(istream& is){
        drum::read(is);
        cout<<"nr tari:";
        is>>nr_tari;
    }
};
class autostrada:public drum_european{
    uint32_t nr_benzi;
public:
    autostrada(float lungime, uint32_t nr_tronsoane,uint32_t nr_benzi,uint32_t nr_tari=1):
        drum_european(lungime,nr_tronsoane,nr_tari),
        nr_benzi(nr_benzi)
    {
        denumire="A"+to_string(ID);
    }
    autostrada(){
        denumire="A"+to_string(ID);
    }

      virtual void print(ostream& os) const {
        drum::print(os);
        if(nr_tari!=1)
            os<<" nr tari:"<<nr_tari;
        os<<" nr benzi:"<<nr_benzi;
    }
    float getCost(){
        if(nr_tari>1)
            return 2500*nr_benzi*lungime/nr_tronsoane+nr_tari*500;
        return 2500*nr_benzi*lungime/nr_tronsoane;
    }
    virtual void read(istream& is){
        drum::read(is);
        cout<<"nr benzi:";
        is>>nr_benzi;
        cout<<"nr tari:";
        is>>nr_tari;

        if(nr_benzi<2){
            throw invalid_argument("numarul de benzi trebuie sa fie minim 2");
        }
    }
};

class contract{
    static int global_id;
    static set<pair<string,int>> drumuri_asociate;
    int id;
    string nume;
    string CIF;
    shared_ptr<drum> dr;
    int nr_transon;
public:

    contract(){
        id=global_id++;

    }

   contract(const string& nume,const string& CIF){
        id=global_id++;
        this->nume=nume;
        this->CIF=CIF;
    }

    friend istream& operator>>(istream& is,contract& c){
        cout<<"nume:";
        is>>c.nume;
        cout<<"CIF:";
        is>>c.CIF;
        return is;
    }
    friend ostream& operator<<(ostream& os,const contract& c){
        os<<"nume:"<<c.nume<<"CIF:"<<c.CIF<<"transon";
        if(c.dr!=nullptr){
            os<<c.nr_transon<<"Drum:"<<*c.dr;
        }
        return os;
    }
    ~contract(){
         if(this->dr!=nullptr){
                drumuri_asociate.erase(pair(this->dr->getDenumire(),this->nr_transon));
        }
    }
public:
      void asociazaDrumSiTranson(shared_ptr<drum>& dr,int nr_transon){
        if(nr_transon>dr->getNrTronsoane()){
            throw invalid_argument("numarul transonului mai mare ca numarul total de transoane ale drumului");
        }
        if(drumuri_asociate.count(pair(dr->getDenumire(),nr_transon))==0){
            if(this->dr!=nullptr){
                drumuri_asociate.erase(pair(this->dr->getDenumire(),this->nr_transon));

            }
            this->dr=dr;
            this->nr_transon=nr_transon;
            drumuri_asociate.insert(pair(dr->getDenumire(),nr_transon));
        }else{
            throw invalid_argument("drumul si transonul acesta au deja un contract asignat");
      }
    }
    string getCIF(){
        return CIF;
    }
};
set<pair<string,int>> contract::drumuri_asociate;
int contract::global_id=0;
float calculeazaLungimeDrumuri(const std::vector<shared_ptr<drum>>& drumuri)
{
    float ans=0;
    for(auto& drum:drumuri){
        ans+=drum->getLungime();
    }
    return ans;
}
float calculeazaLungimeAutostrazi(const std::vector<shared_ptr<drum>>& drumuri)
{
    float ans=0;
    for(auto& drum:drumuri){
        if(dynamic_pointer_cast<autostrada>(drum))
            ans+=drum->getLungime();
    }
    return ans;
}
int main()
{

    try{
        std::vector<shared_ptr<drum>> drumuri;
        std::vector<shared_ptr<contract>> contracte;
        drumuri.push_back(make_shared<drum_european>(20,5,3));
        drumuri.push_back(make_shared<drum_national>(40,4,6));
        drumuri.push_back(make_shared<autostrada>(120,4,2));
        cout<<calculeazaLungimeAutostrazi(drumuri);
        contracte.push_back(make_shared<contract>("A1","B5"));
        contracte.push_back(make_shared<contract>("A2","B4"));
        contracte.push_back(make_shared<contract>("A3","B3"));
        contracte.push_back(make_shared<contract>("A4","B2"));
        contracte.push_back(make_shared<contract>("A5","B1"));
        contracte[0]->asociazaDrumSiTranson(drumuri[0],2);
        contracte[1]->asociazaDrumSiTranson(drumuri[0],1);
        contracte[2]->asociazaDrumSiTranson(drumuri[0],0);

        for(int i=0;i<contracte.size();i++){
            if(contracte[i]->getCIF()=="B3"){
                contracte.erase(contracte.begin()+i);
                i--;
            }
        }
        for(auto contract:contracte){
            cout<<*contract<<"\n";
        }
    }catch(invalid_argument& e){
        cout<<e.what();
    }
    return 0;
}
