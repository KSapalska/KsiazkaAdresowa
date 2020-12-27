#include <iostream>
#include<windows.h>
#include <fstream>

using namespace std;

struct Przyjaciel
{
    int id;
    string imie, nazwisko, nr_telefonu, adres, email;
};


int odczytajDane(Przyjaciel przyjaciele[],int &iloscWprowadzonychPrzyjaciol)
{
    int nr_linii=1;
    string linia;

    fstream plik;

    plik.open("przyjaciele.txt", ios::in);
    if (plik.good()==false)
    {
        cout<<"Ksiazka adresowa jest pusta.";
        Sleep(1000);
    }

    while(getline(plik,linia))
    {
        switch(nr_linii)
        {
        case 1:
            przyjaciele[iloscWprowadzonychPrzyjaciol].id =atoi(linia.c_str());
            break;
        case 2:
            przyjaciele[iloscWprowadzonychPrzyjaciol].imie=linia;
            break;
        case 3:
            przyjaciele[iloscWprowadzonychPrzyjaciol].nazwisko=linia;
            break;
        case 4:
            przyjaciele[iloscWprowadzonychPrzyjaciol].nr_telefonu=linia;
            break;
        case 5:
            przyjaciele[iloscWprowadzonychPrzyjaciol].adres=linia;
            break;
        case 6:
            przyjaciele[iloscWprowadzonychPrzyjaciol].email=linia;
            break;
        }
        if (nr_linii==6)
        {
            nr_linii=0;
            iloscWprowadzonychPrzyjaciol++;
        }
        nr_linii++;
    }

    plik.close();
    return iloscWprowadzonychPrzyjaciol;
}


int zapiszDane(Przyjaciel przyjaciele[],int &iloscWprowadzonychPrzyjaciol)
{

    przyjaciele[iloscWprowadzonychPrzyjaciol].id=iloscWprowadzonychPrzyjaciol;
    cout<<endl;
    cout<< "Podaj imie: ";
    cin>>przyjaciele[iloscWprowadzonychPrzyjaciol].imie;
    cout<< "Podaj nazwisko: ";
    cin>>przyjaciele[iloscWprowadzonychPrzyjaciol].nazwisko;
    cout<< "Podaj numer telefonu: ";
    cin>>przyjaciele[iloscWprowadzonychPrzyjaciol].nr_telefonu;
    cout<< "Podaj adres: ";
    cin.sync();
    getline(cin, przyjaciele[iloscWprowadzonychPrzyjaciol].adres);
    cout<< "Podaj email: ";
    cin>>przyjaciele[iloscWprowadzonychPrzyjaciol].email;

    fstream plik;
    plik.open("przyjaciele.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].id << endl;
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].imie << endl;
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].nazwisko << endl;
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].nr_telefonu << endl;
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].adres << endl;
        plik << przyjaciele[iloscWprowadzonychPrzyjaciol].email << endl;

        plik.close();

        cout << "Dane zostaly zapisane." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    return ++iloscWprowadzonychPrzyjaciol;
}

void wyswietlListe(Przyjaciel przyjaciele[],int &iloscWprowadzonychPrzyjaciol)
{
    for(int i=0; i<iloscWprowadzonychPrzyjaciol; i++)
        cout<<przyjaciele[i].id+1<<" "<<przyjaciele[i].imie<<" "<<przyjaciele[i].nazwisko<<endl;
}

void wyszukajImie(Przyjaciel przyjaciele[],int &iloscWprowadzonychPrzyjaciol)
{
    string imie;
    int licznik=0;
    cin>>imie;
    for (int i=0; i<iloscWprowadzonychPrzyjaciol; i++)
    {
        if(przyjaciele[i].imie==imie)
        {
            cout<<endl<<przyjaciele[i].imie<<" "<<przyjaciele[i].nazwisko;
            licznik++;
        }
    }
    if (licznik==0)
    {
        cout<<endl<<"Imie "<<imie<<" nie zostalo odnalezione w bazie.";
    }
    Sleep(3000);
}

void wyszukajNazwisko(Przyjaciel przyjaciele[],int &iloscWprowadzonychPrzyjaciol)
{
    string nazwisko;
    int licznik=0;
    cin>>nazwisko;
    for (int i=0; i<iloscWprowadzonychPrzyjaciol; i++)
    {
        if(przyjaciele[i].nazwisko==nazwisko)
        {
            cout<<endl<<przyjaciele[i].nazwisko<<" "<<przyjaciele[i].imie;
            licznik++;
        }
    }
    if (licznik==0)
    {
        cout<<endl<<"Nazwisko "<<nazwisko<<" nie zostalo odnalezione w bazie.";
    }
    Sleep(3000);
}
int main()
{


    Przyjaciel przyjaciele[1000];
    int iloscWprowadzonychPrzyjaciol =0;

    odczytajDane(przyjaciele,iloscWprowadzonychPrzyjaciol);
    cout<<"iloscWprowadzonychPrzyjaciol; "<<iloscWprowadzonychPrzyjaciol<<endl;
    char wybor;


    while(1)
    {
        system("cls");
        cout<<"----------------------------"<<endl;
        cout<<"         MENU GLOWNE"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1. Wprowadz dane Twojego przyjaciela"<<endl;
        cout<<"2. Wyszukaj po imieniu"<<endl;
        cout<<"3. Wyszukaj po nazwisku"<<endl;
        cout<<"3. Wyswietl liste przyjaciol"<<endl;
        cout<<"9. Zakoncz program"<<endl;

        cout<<endl<<"Wybieram: ";
        cin>> wybor;

        if (wybor=='1')
        {
            iloscWprowadzonychPrzyjaciol=zapiszDane(przyjaciele,iloscWprowadzonychPrzyjaciol) ;
            Sleep(3000);
        }
        else if (wybor=='2')
            {
                cout<<"Szukam przyjaciela o imieniu: ";
                wyszukajImie(przyjaciele,iloscWprowadzonychPrzyjaciol);
            }
            else if (wybor=='3')
            {
                cout<<"Szukam przyjaciela o nazwisku: ";
                wyszukajNazwisko(przyjaciele,iloscWprowadzonychPrzyjaciol);
            }


        else if (wybor=='4')
        {
            system("cls");
            cout<<"--------------------------------------"<<endl;
            cout<<"         LISTA TWOICH PRZYJACIOL"<<endl;
            cout<<"--------------------------------------"<<endl;
            if(iloscWprowadzonychPrzyjaciol==0)
            {
                cout<<"Baza danych jest pusta...";
            }
            else
                wyswietlListe(przyjaciele,iloscWprowadzonychPrzyjaciol);
            Sleep(3000); ;
        }
        else if (wybor=='9')
        {
            exit(0) ;
        }
    }
    return 0;
}
