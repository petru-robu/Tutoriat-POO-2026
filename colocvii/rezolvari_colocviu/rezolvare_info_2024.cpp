#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class obiect
{
protected:
    static int id_ct;
    const int id = id_ct;

public:
    virtual void Afisare(ostream& os) const
    {
        os << 1;
    }
    obiect()
    {
        ++id_ct;
    }
    friend ostream & operator <<(ostream & os,const obiect& a)
    {
        a.Afisare(os);
        return os;
    }
    virtual float cost_upgrade() = 0;
    virtual void upgrade() = 0 ;
};
int obiect::id_ct=0;

class zid_aparare : public obiect
{
    int inaltime, lungime;
    float grosime;
public:
    zid_aparare()
    {
        inaltime = 2;
        lungime = 1;
        grosime = 0.5;
    }
    void Afisare(ostream& os) const override
    {
        os << inaltime << " " << grosime << " " << lungime <<"\n";

    }
    float cost_upgrade() override
    {
        return 100.0 * inaltime * lungime * grosime ;
    }
    void upgrade() override
    {
        inaltime += 1;
        lungime += 1;
        grosime += 1;
    }
};
class turn_defensiv : public obiect
{
    int putere;
public:
    turn_defensiv()
    {
        putere = 1000;
    }
    virtual void Afisare(ostream& os)  const override
    {
        os << putere <<"\n";
    }
    float cost_upgrade()
    {
        return 500.0 * putere ;
    }
    void upgrade() override
    {
        putere += 500;
    }
};
class robot : public obiect
{
protected:
    int viata,damage,nivel;
public:
    robot()
    {
        nivel = 1;
        damage = viata = 100;
    }
    virtual void Afisare(ostream& os) const override
    {
        os << viata << " " << damage << " " << nivel <<"\n";
    }
    float cost_upgrade()
    {
        return 0;
    }
    void upgrade() override
    {

    }
};
class robot_terestru : public robot
{
    bool are_scut;
    int numar_gloante;
public:
    robot_terestru()
    {
        are_scut = 0 ;
        numar_gloante = 500;
    }
    virtual void Afisare(ostream& os) const override
    {
        robot::Afisare(os);
        os << " " << numar_gloante << " " << are_scut <<" ";
    }
    float cost_upgrade()
    {
        return 10*numar_gloante;
    }
    void upgrade() override
    {
        numar_gloante += 100;
        nivel++;
        damage+=50;
        if( nivel == 5 )
        {
            are_scut = 1;
            viata += 50;
        }
    }
};
class robot_aerian : public robot
{
    int autonomie;
public:
    robot_aerian()
    {
        autonomie = 10;
    }
    virtual void Afisare(ostream& os) const override
    {
        robot::Afisare(os);
        os << " " << autonomie <<"\n";
    }
    float cost_upgrade()
    {
        return 50 * autonomie;
    }
    void upgrade() override
    {
        autonomie ++;
        nivel ++;
        damage += 25;
    }
};

void add_zid(std::vector< obiect *>&inventar,float&bani)
{
    if( bani >= 300 )
    {
        bani -= 300;
        inventar.push_back( new zid_aparare() );
    }
}
void add_turn(std::vector< obiect *>&inventar,float&bani)
{
    if( bani >= 500 )
    {
        bani -= 500;
        inventar.push_back( new turn_defensiv() );
    }
}
void add_robot_terestru(std::vector< obiect *>&inventar,float&bani)
{
    if( bani >= 50 )
    {
        bani -= 50;
        inventar.push_back( new robot_terestru() );
    }
}
void add_robot_aerian(std::vector< obiect *>&inventar,float&bani)
{
    if( bani >= 100 )
    {
        bani -= 100;
        inventar.push_back( new robot_aerian() );
    }
}

void Afisare( std::vector<obiect*>&a )
{
    for( auto&x : a )
        std::cout << ( *x ) << "\n" ;
}



void Afisare_cost( std::vector<obiect*> a )
{
    sort( a.begin(),a.end(),[](obiect* x,obiect* y)
    {
        return x->cost_upgrade() > y->cost_upgrade();
    } );
    for( auto&x:a )
    {
        std::cout << (*x) << " ";
//        x->Afisare(cout);
    }
    std::cout << "\n";
}

void Afisare_robot(std::vector<obiect*> a)
{
    for(auto &x: a)
        if( dynamic_cast<robot*>(x) )
            std::cout << (*x )<<"\n";
}
void Sell(std::vector<obiect*>&inventar,float&bani,int index )
{
    try{
        inventar.erase( inventar.begin()+index );
        bani += 500;
    }
    catch( ... )
    {
        std::cout << "NU";
    }
}

int main()
{
    float bani = 50000;
    std::vector< obiect *> inventar;
    add_zid( inventar,bani );
    add_zid( inventar,bani );
    add_zid( inventar,bani );
    add_robot_aerian( inventar,bani );
    Afisare(inventar);
    std::cout << "----------\n";
    Afisare_cost(inventar);
    std::cout << "----------\n";
    Afisare_robot(inventar);
    std::cout << bani <<"\n";
    Sell(inventar,bani,1);
    std::cout << bani << "\n";
    Sell(inventar,bani,10);
    Afisare(inventar);
    return 0;
}
