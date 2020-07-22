#include <iostream>
#include <string.h>
using namespace std;

class Ingredient;
class Pizza;



class Calcul
{

    public : virtual float pret() = 0;
    virtual void afisare() = 0;
};



class Ingredient{
    char* nume;
    int cantitate;
    float pret;

public:

    void set_nume(char x[20]){

        nume = new char[strlen(x)];
        strcpy(nume,x);
        //nume[strlen(x)] = '\0';
        }
    void set_cantitate(int x){cantitate = x;}
    void set_pret(float x){pret = x;}

    char* get_nume(){return nume;}
    int get_cantitate(){return cantitate;}
    float get_pret(){return pret;}


    friend istream &operator>>(istream &A, Ingredient &x);
    friend ostream &operator<<(ostream &A, const Ingredient &x);
    Ingredient &operator=(const Ingredient&);


    Ingredient(char x[20], int y, float z);
    Ingredient();

    ~Ingredient(){nume = NULL; cantitate = 0; pret = 0;}


};

Ingredient :: Ingredient(char x[20], int y, float z)
{

    nume = new char[strlen(x)];
    strcpy(nume,x);

    cantitate = y;

    pret = z;


}

Ingredient :: Ingredient()
{
    nume = "";
    cantitate = 0;
    pret = 0;
}

Ingredient &Ingredient :: operator=(const Ingredient& a)
{
    nume = a.nume;
    cantitate = a.cantitate;
    pret = a.pret;

    return *this;
}
istream &operator>>(istream &A, Ingredient &x)
{
    char nu[20];
    int y;
    float z;
    cout << "Dati numele ingredientului: ";
    A >> nu;
    x.set_nume(nu);
    cout << "\n";

    cout << "Dati cantitatea ingredientului: ";
    A >> y;
    x.set_cantitate(y);
    cout << "\n";

    cout << "Dati pretul ingredientului: ";
    A >> z;
    x.set_pret(z);
    cout << "\n";

    return A;
}
ostream &operator<<(ostream &A, const Ingredient &x)
{
    A << "Nume ingredient: " << x.nume << "\n";
    A << "Cantitate: " << x.cantitate << "\n";
    A << "Pret: " << x.pret << "\n";

    return A;

}

class Pizza : public Calcul, public Ingredient
{
    int nr;
    char nume[20];
    Ingredient* ing;
    float pretz;
    const float manopera;

public:

    float get_pretz(){return pretz;}
    //void set_pretz(x){pretz = x;}



    Pizza(int x, Ingredient* v, float man, char n[20]):manopera(man){nr = x; ing = v; pretz = manopera + pret(); strcpy(nume,n);};
    Pizza():manopera(0){nr = 0; ing = NULL; pretz = manopera + pret();}
    Pizza(float man):manopera(man){nr = 0; ing = NULL; pretz = manopera + pret();}

    float pret(){

        float suma;
        suma = manopera;
        for(int i = 0; i < nr; i++)
            suma += ing[i].get_cantitate() * ing[i].get_pret();


        return suma;
    }
    void afisare()
    {
        cout << nr<<"\n";
        cout << nume<<"\n";
        for(int i = 0; i < nr; i++)
            cout << ing[i];
        cout << pretz<<"\n";
        cout << manopera<<"\n";
    }

    friend istream &operator>>(istream &A, Pizza &a);
    friend ostream &operator<<(ostream &A, const Pizza &x);
    Pizza &operator=(const Pizza&);
    ~Pizza(){nr = 0; strcpy(nume,"\0"); delete ing; pretz = 0;}

};

Pizza &Pizza :: operator=(const Pizza& a)
{
    nr = a.nr;
    strcpy(nume, a.nume);
    ing = a.ing;
    pretz = a.pretz;
    //manopera = a.manopera;
}


istream &operator>>(istream &A, Pizza &a)
{
    cout << "Numele pizzei: ";
    A >> a.nume;
    cout << "\n";
    //NRpizze++;
    cout << "Nr de ingrediente: ";
    A >> a.nr;
    a.ing = new Ingredient[a.nr];
    cout << "Ingredientele: \n";
    for(int i = 0; i < a.nr; i++)
        A >> a.ing[i];
    a.pretz = a.pret();
    return A;
}
ostream &operator<<(ostream &A, const Pizza &x)
{
    A << "Numele pizzei: "<< x.nume <<"\n";
    A << "Nr. de ingrediente: "<< x.nr <<"\n";
    A << "Ingredientele: ";
    for(int i = 0; i < x.nr; i++)
        A << x.ing[i];
    A << "\n";

    return A;
}
class Comanda : public Pizza, public Calcul
{

    bool OnLine;
    float distanta;
    Pizza *pizza;
    int nrP;
    float pretF;

public:

    Comanda();
    Comanda(bool , float , Pizza* , int );
    void afisare(){
    cout << "Afisare aici";

    }


    float pret(){

        for(int i = 0; i < nrP; i++)
            pretF += pizza[i].pret();

        if(OnLine == true)
            {
                float adaos = pretF / 20;
                pretF = pretF + adaos *(distanta / 10);
            }

        return pretF;
    }
    friend istream &operator>>(istream &A, Comanda &c);

};

istream &operator>>(istream &A, Comanda &c)
{
    int x;
    float d;
    cout << "Comanda este online? (1/0)\n";
    A >> x;
    if(x)
        c.OnLine = true;
        else
        c.OnLine = false;
    cout << "\n";
    cout << "Distanta in km: ";
    A >> c.distanta;
    cout << "\n";
    cout << "Nr. de pizze: ";
    A >> c.nrP;
    cout << "\n";
    cout << "Pizzele: \n";
    c.pizza = new Pizza[c.nrP];
    for(int i = 0; i < c.nrP; i++)
        A >> c.pizza[i];
    return A;

}


Comanda :: Comanda()
{
    OnLine = false;
    distanta = 0;
    pizza = NULL;
    nrP = 0;
}

Comanda :: Comanda(bool x, float dist, Pizza* p, int n)
{
    OnLine = x;
    distanta = dist;
    pizza = p;
    nrP = n;
    pretF = pret();
}

class Carne : public Pizza
{
public:
    Carne();
};
Carne :: Carne() : Pizza()
{

}
class Vegetariana : public Pizza
{
    //float pretTotal;
public:
    Vegetariana();

};
Vegetariana :: Vegetariana(): Pizza()
{

}
template <class T> class Meniu : public Pizza
{
    T tip;
    Pizza **pitza;
    int numar;

public:

    Meniu(){numar = 0; pitza = NULL;}
    Meniu(int x, Pizza* adr, T y){numar = x; *pitza = adr; tip = y;}

friend istream &operator>>(istream &A, Meniu &a)
{
    cout << "Dati nr de pointeri catre pizza: ";
    A >> a.numar;
    A >> a.numar;
    cout << "\n";
    int num, opt;
    float man;
    char n[20];
    Ingredient *v;
    a.pitza = new Pizza*[a.numar];
    cout << "Dati pizzele: \n";
    for(int i = 0; i < a.numar; i++)
        {   cout << "Dati numele pizzei: ";
            A >> n;
            cout << "\n";
            cout << "Este Vegetariana sau cu carne? (1/0)";
            A >> opt;
           /* if(opt)
            Vegetariana a.tip;
            else
            Carne a.tip;*/
            cout << "\n";
            cout << "Dati nr de ingrediente: ";
            A >> num;
            cout << "\n";
            v = new Ingredient[num];
            for(int j = 0; j < num; j++)
                A >> v[i];
            cout << "\nDati manopera: ";
            A >> man;
            cout << "\n";
            a.pitza[i] = new Pizza(num, v, man, n);

        }

    return A;

}

    friend const Meniu operator+=(Meniu&, const Meniu&);

    static int index;
    ~Meniu(){delete pitza; numar = 0;}
};

template <class T> int Meniu <T>:: index = 0;

/*template <class T> const Meniu <T> :: operator+=(Meniu &a, const Meniu &b)
{
    a.index = a.index + b.index;
}

istream &operator>>(istream &A, Meniu &a)
{
    cout << "Dati nr de pointeri catre pizza: ";
    A >> a.numar;
    cout << "\n";
    int num;
    float man;
    Ingredient *v;
    a.pitza = new Pizza*[a.numar];
    cout << "Dati pizzele: \n";
    for(int i = 0; i < a.numar; i++)
        {
            cout << "Dati nr de ingrediente: ";
            A >> num;
            cout << "\n";
            v = new Ingredient[num];
            for(int j = 0; j < x; j++)
                A >> v[i];
            cout << "\nDati manopera: ";
            A >> man;
            cout << "\n";
            a.pitza[i] = new Pizza(x, v, man);
        }

    return A;

}


*/

template < > class Meniu <Vegetariana>
{
    Vegetariana tip;
    Pizza **pitza;
    int numar;
    float ValoareIncasata;

public:

    Meniu(){numar = 0; pitza = NULL; ValoareIncasata = 0;}
//    Meniu(int x, Pizza* adr, T y){numar = x; *pitza = adr; tip = y; ValoareIncasata = 0;}

friend istream &operator>>(istream &A, Meniu &a)
{

    cout << "Dati nr de pointeri catre pizza: ";
    A >> a.numar;
    cout << "\n";
    int num, opt;
    float man;
    char n[20];
    Ingredient *v;
    a.pitza = new Pizza*[a.numar];
    cout << "Dati pizzele: \n";
    for(int i = 0; i < a.numar; i++)
        {   cout << "Dati numele pizzei: ";
            A >> n;
            cout << "\n";
            cout << "Este Vegetariana sau cu carne? (1/0)";
            A >> opt;
           /* if(opt)
            Vegetariana a.tip;
            else
            Carne a.tip;*/
            cout << "\n";
            cout << "Dati nr de ingrediente: ";
            A >> num;
            cout << "\n";
            v = new Ingredient[num];
            for(int j = 0; j < num; j++)
                A >> v[i];
            cout << "\nDati manopera: ";
            A >> man;
            cout << "\n";
            a.pitza[i] = new Pizza(num, v, man, n);
            a.ValoareIncasata += a.pitza[i]->get_pretz();

        }

    return A;

}
~Meniu(){delete pitza; numar = 0;}
};
template < > class Meniu <Carne>
{
    Vegetariana tip;
    Pizza **pitza;
    int numar;
    float ValoareIncasata;

public:

    Meniu(){numar = 0; pitza = NULL; ValoareIncasata = 0;}
//    Meniu(int x, Pizza* adr, T y){numar = x; *pitza = adr; tip = y; ValoareIncasata = 0;}

friend istream &operator>>(istream &A, Meniu &a)
{

    cout << "Dati nr de pointeri catre pizza: ";
    A >> a.numar;
    try{
        int k = a.numar;
    if(k < 0)
        throw k;
    }
    catch(int)
    {
        cout << "\n Nu e ok numar negativ\n";

    }
    cout << "\n";
    int num, opt;
    float man;
    char n[20];
    Ingredient *v;
    a.pitza = new Pizza*[a.numar];
    cout << "Dati pizzele: \n";
    for(int i = 0; i < a.numar; i++)
        {   cout << "Dati numele pizzei: ";
            A >> n;
            cout << "\n";
            cout << "Este Vegetariana sau cu carne? (1/0)";
            A >> opt;

            try{
            int k = opt;
            if(k < 0)
                throw k;
            }
            catch(int)
            {
                cout << "\n Nu e ok numar negativ\n";
                break;
            }
           /* if(opt)
            Vegetariana a.tip;
            else
            Carne a.tip;*/
            cout << "\n";
            cout << "Dati nr de ingrediente: ";
            A >> num;
            try{
            int k = num;
            if(k < 0)
                throw k;
            }
            catch(int)
            {
                cout << "\n Nu e ok numar negativ\n";
                break;
            }
            cout << "\n";
            v = new Ingredient[num];
            for(int j = 0; j < num; j++)
                A >> v[i];
            cout << "\nDati manopera: ";
            A >> man;
            try{
            int k = man;
            if(k < 0)
                throw k;
            }
            catch(int)
            {
                cout << "\n Nu e ok numar negativ\n";
                break;
            }
            cout << "\n";
            a.pitza[i] = new Pizza(num, v, man, n);
            a.ValoareIncasata += a.pitza[i]->get_pretz();

        }

    return A;

}
~Meniu(){delete pitza; numar = 0;}
};

int main()
{
    char* z = "2" + 2 - 2;
    cout<<z;
    Pizza y;
    Comanda x;
    cin >> x;
    cout << x.pret();

    return 0;
}
