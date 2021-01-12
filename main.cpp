#include <iostream>
#include <cstdlib>
#include<windows.h>
#include<fstream>
#include<vector>
#include <sstream>
#include <string>
using namespace std;

struct Adresat {
    int id=0;
    string imie="", nazwisko="", nr_telefonu="", adres="", email="";
};

char wyswietlMenu () {

    char wybor=' ';
    system("cls");

    cout << "KSI¤½KA ADRESOWA" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wy˜wietl wszystkich adresat¢w" << endl;
    cout << "5. Usuä adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "9. Zakoäcz program" << endl;
    cout<<"Tw¢j wyb¢r: ";
    cin>> wybor;
    return wybor;
}

vector <Adresat> rozdzielDaneNaPojedynczeInformacjeOsobowe (vector <Adresat> &adresaci, string linia) {
    Adresat osoba;
    int nrLinii = 1;
    stringstream ss(linia);
    string pojedynczaInformacja = " ";

    while (getline(ss, pojedynczaInformacja, '|')) {
        switch (nrLinii) {
        case 1:
            osoba.id = (atoi(pojedynczaInformacja.c_str()));
            break;
        case 2:
            osoba.imie = pojedynczaInformacja;
            break;
        case 3:
            osoba.nazwisko = pojedynczaInformacja;
            break;
        case 4:
            osoba.nr_telefonu = pojedynczaInformacja;
            break;
        case 5:
            osoba.email = pojedynczaInformacja;
            break;
        case 6:
            osoba.adres = pojedynczaInformacja;
            break;
        }
        nrLinii++;
    }
    adresaci.push_back(osoba);

    return adresaci;
}

void odczytajDane(vector <Adresat> &adresaci) {

    string linia;
    fstream plik;
    adresaci.clear();

    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == false) {
        cout << "Ksiazka adresowa jest pusta."<<endl;
        Sleep(1000);
    } else {
        while(getline(plik,linia)) {
            rozdzielDaneNaPojedynczeInformacjeOsobowe (adresaci,linia);
        }
        cout << "...";
        Sleep(500);
    }
    plik.close();
}

void zapiszDane(vector <Adresat> &adresaci) {
    Adresat osoba;

    if (adresaci.empty() == true) {
        osoba.id=1;
    } else {
        osoba.id=adresaci.back().id+1;
    } ;

    cout<<endl;
    cout<< "Podaj imie: ";
    cin>>osoba.imie;
    cout<< "Podaj nazwisko: ";
    cin>>osoba.nazwisko;
    cout<< "Podaj numer telefonu: ";
    cin>>osoba.nr_telefonu;
    cout<< "Podaj adres: ";
    cin.sync();
    getline(cin, osoba.adres);
    cout<< "Podaj email: ";
    cin>>osoba.email;

    adresaci.push_back(osoba);
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << osoba.id <<"|"<<osoba.imie<<"|"<<osoba.nazwisko <<"|"<< osoba.nr_telefonu << "|" << osoba.adres << "|"<< osoba.email << endl;

        plik.close();

        cout <<endl<< "Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

void wyszukajImie(vector <Adresat> &adresaci) {
    string imie;
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();
    int licznik=0;

    cout<<"Podaj szukane imie ";
    cin>>imie;
    for (itr; itr != itrEnd; ++itr) {
        if(itr->imie == imie) {
            cout<<endl<< itr->imie <<" "<< itr->nazwisko<<endl;
            licznik++;
        }
    }
    if (licznik==0) {
        cout<<endl<<"Imie "<<imie<<" nie zostalo odnalezione w bazie."<<endl;
    }
    Sleep(3000);
}

void wyszukajNazwisko(vector <Adresat> &adresaci) {
    string nazwisko;
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();
    int licznik=0;

    cout<<"Podaj szukane nazwisko: ";
    cin>>nazwisko;
    for (itr; itr != itrEnd; ++itr) {
        if(itr->nazwisko == nazwisko) {
            cout<<endl<<itr->nazwisko<<" "<<itr->imie<<endl;
            licznik++;
        }
    }
    if (licznik==0) {
        cout<<endl<<"nazwisko "<<nazwisko<<" nie zostalo odnalezione w bazie."<<endl;
    }
    Sleep(3000);
}

void wyswietlAdresatow (vector <Adresat> &adresaci) {
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();

    for (itr; itr != itrEnd; ++itr) {
        cout << endl;
        cout << "ID: " << itr -> id << endl;
        cout << itr -> imie << " " << itr -> nazwisko<< endl;
        cout << "Telefon: " << itr -> nr_telefonu << endl;
        cout << "Email: " << itr -> email << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
    }
}

void przepiszPlik(vector <Adresat> &adresaci) {

    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::trunc| ios::out);
    if (plik.good()) {
        for (itr; itr != itrEnd; ++itr) {
            plik << itr -> id <<"|"<<itr -> imie<<"|"<<itr -> nazwisko <<"|"<< itr -> nr_telefonu << "|" << itr -> adres << "|"<< itr -> email << endl;
        }
        plik.close();
        cout << endl<<"Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

void usunAdresata (vector <Adresat> &adresaci) {

    int wybraneID;
    char potwierdzenieUsuniecia;
    int licznik=0;
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();

    cout << "Podaj id adresata, ktorego chcesz usunac:";
    cin >> wybraneID;
    for (itr; itr != itrEnd; ++itr) {
        if (itr->id == wybraneID) {
            cout << "Czy na pewno chcesz usunac tego adresata? Jesli tak, kliknij t"<<endl;
            cin >> potwierdzenieUsuniecia;
            if (potwierdzenieUsuniecia == 't') {
                itr= adresaci.erase (itr);
            }
            cout << "Kontakt zostal usuniety";
            Sleep(800);
            przepiszPlik(adresaci);

        }
    }
    licznik++;
}



void edycja (vector <Adresat> &adresaci) {
    int wybor,id ;
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itrEnd = adresaci.end();

    cout << "Podaj ID osoby ktorej dane chcesz edytowac" << endl;
    cin>>id;

    for (itr; itr != itrEnd; ++itr) {
        if (id == itr -> id) {

            cout << "Oto dane kontaktowe osoby o wybranym ID:" << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Telefon: " << itr -> nr_telefonu << endl;
            cout << "Email: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
            cout <<"Wybierz dane do edycji:"<<endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout<<"Twcj wybcr: ";
            cin>> wybor;

            switch (wybor) {
            case 1:
                cout<< "Podaj nowe imie:";
                cin>>itr -> imie;
                przepiszPlik(adresaci);
                break;
            case 2:
                cout<< "Podaj nowe nazwisko:";
                cin>>itr -> nazwisko;
                przepiszPlik(adresaci);
                break;
            case 3:
                cout<< "Podaj nowy nr telefonu:";
                cin>>itr -> nr_telefonu;
                przepiszPlik(adresaci);
                break;
            case 4:
                cout<< "Podaj nowy email:";
                cin>>itr -> email;
                przepiszPlik(adresaci);
                break;
            case 5:
                cout<< "Podaj nowy adres:";
                cin>>itr -> adres;
                przepiszPlik(adresaci);
                break;
            case 6:
                system("cls");
                break;
            }
            break;

        } else if (itr==itrEnd)
            cout <<"Nie znaleziono osoby o podanym ID ";
        Sleep(2000);
    }
}

int main() {
    char wybor;
    vector <Adresat> adresaci;

    while(1) {
        odczytajDane(adresaci);
        wybor=wyswietlMenu();

        if (wybor == '1') {
            zapiszDane(adresaci);
            Sleep(3000);
        } else if (wybor == '2') {
            wyszukajImie(adresaci);
        } else if (wybor == '3') {
            wyszukajNazwisko(adresaci);
        } else if (wybor == '4') {
            wyswietlAdresatow(adresaci);
            Sleep(7000);
        } else if (wybor == '5') {
            usunAdresata(adresaci);
            Sleep(3000);
        } else if (wybor == '6') {
            edycja (adresaci);
        } else if (wybor == '9') {
            exit(0) ;
        }

    }
}
