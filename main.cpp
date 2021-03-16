#include <iostream>
#include <iostream>
#include <cstdlib>
#include<windows.h>
#include<fstream>
#include<vector>
#include <sstream>
#include <string>

using namespace std;

struct Uzytkownik {
    int idUzytkownika=0;
    string nazwa, haslo;
};

struct Adresat {
    int idAdresata=0;
    int idUzytkownika=0;
    string imie="", nazwisko="", nr_telefonu="", adres="", email="";
};

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}


char wyswietlMenu () {

    char wybor=' ';
    system("cls");

    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresat¢w" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;
    cout<<"Tw¢j wyb¢r: ";
    wybor= wczytajZnak();
    return wybor;
}

vector <Adresat> rozdzielDaneNaPojedynczeInformacjeOsobowe (vector <Adresat> &adresaci, string linia,int &idZalogowanegoUzytkownika) {   //updated
    Adresat osoba;
    int nrLinii = 1;
    stringstream ss(linia);
    string pojedynczaInformacja = " ";

    while (getline(ss, pojedynczaInformacja, '|')) {
        switch (nrLinii) {
        case 1:
            osoba.idAdresata = (atoi(pojedynczaInformacja.c_str()));
            break;
        case 2:
            osoba.idUzytkownika = (atoi(pojedynczaInformacja.c_str()));
            break;
        case 3:
            osoba.imie = pojedynczaInformacja;
            break;
        case 4:
            osoba.nazwisko = pojedynczaInformacja;
            break;
        case 5:
            osoba.nr_telefonu = pojedynczaInformacja;
            break;
        case 6:
            osoba.email = pojedynczaInformacja;
            break;
        case 7:
            osoba.adres = pojedynczaInformacja;
            break;
        }
        nrLinii++;
    }

    if  (idZalogowanegoUzytkownika==osoba.idUzytkownika) adresaci.push_back(osoba);

    return adresaci;
}


void odczytajDane(vector <Adresat> &adresaci,int &idZalogowanegoUzytkownika) {

    string linia;
    fstream plik;
    adresaci.clear();

    plik.open("Adresaci.txt", ios::in);
    if (plik.good() == false) {
        cout << "Ksiazka adresowa jest pusta."<<endl;
        Sleep(1000);
    } else {
        while(getline(plik,linia)) {
            rozdzielDaneNaPojedynczeInformacjeOsobowe (adresaci,linia,idZalogowanegoUzytkownika);
        }
        cout << "...";
        Sleep(200);
    }
    plik.close();
}

int sprawdzOstatnieID() {

    int ostatnieID = 0;
    string linia;
    fstream plik;
    int nr_linii = 1;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good()==false) {
        return ostatnieID;
    }

    while (getline(plik,linia,'|')) {

        switch(nr_linii) {
        case 1:
            if (atoi(linia.c_str()) == 0) {

                return ostatnieID;
            } else {
                ostatnieID = atoi(linia.c_str());
            }
            break;
        }

        if (nr_linii == 7) {
            nr_linii = 0;
        }
        nr_linii++;
    }
    plik.close();
    return ostatnieID;
}

void zapiszDane(vector <Adresat> &adresaci,int idZalogowanegoUzytkownika ) {
    Adresat osoba;
    int ostatnieID =0 ;

    ostatnieID = sprawdzOstatnieID();

    if (ostatnieID == 0) {
        osoba.idAdresata=1;
        osoba.idUzytkownika=idZalogowanegoUzytkownika;
    } else {
        osoba.idAdresata = ostatnieID + 1;
        osoba.idUzytkownika=idZalogowanegoUzytkownika;
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
    plik.open("Adresaci.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << osoba.idAdresata <<"|"<<osoba.idUzytkownika<<"|"<<osoba.imie<<"|"<<osoba.nazwisko <<"|"<< osoba.nr_telefonu << "|" << osoba.adres << "|"<< osoba.email << "|"<< endl;

        plik.close();

        cout <<endl<< "Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: Adresaci.txt" << endl;
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
        cout << "ID: " << itr -> idAdresata << endl;
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

    plik.open("Adtesaci.txt", ios::trunc| ios::out);
    if (plik.good()) {
        for (itr; itr != itrEnd; ++itr) {
            plik << itr -> idAdresata <<"|"<<itr -> imie<<"|"<<itr -> nazwisko <<"|"<< itr -> nr_telefonu << "|" << itr -> adres << "|"<< itr -> email << endl;
        }
        plik.close();
        cout << endl<<"Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: Adresaci.txt" << endl;
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
        if (itr->idAdresata == wybraneID) {
            cout << "Czy na pewno chcesz usunac tego adresata? Jesli tak, kliknij t"<<endl;

            potwierdzenieUsuniecia = wczytajZnak();
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
        if (id == itr -> idAdresata) {

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
            cout<<"Wybierz 1-6: ";
            wybor = wczytajZnak();

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
                cin.sync();
                getline(cin, itr -> adres);
                //cin>>itr -> adres;
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

vector <Uzytkownik> rozdzielDaneNaPojedynczeDaneOUzytkowniku (vector <Uzytkownik> &uzytkownicy, string linia) {
    Uzytkownik uzytkownik;
    int nrLinii = 1;
    stringstream ss(linia);
    string pojedynczaInformacja = " ";

    while (getline(ss, pojedynczaInformacja, '|')) {
        switch (nrLinii) {
        case 1:
            uzytkownik.idUzytkownika = (atoi(pojedynczaInformacja.c_str()));
            break;
        case 2:
            uzytkownik.nazwa = pojedynczaInformacja;
            break;
        case 3:
            uzytkownik.haslo = pojedynczaInformacja;
            break;
        }
        nrLinii++;
    }
    uzytkownicy.push_back(uzytkownik);

    return uzytkownicy;
}

void odczytajDaneUzytkownikow(vector <Uzytkownik> &uzytkownicy) {

    string linia;
    fstream plik;
    uzytkownicy.clear();

    plik.open("Uzytkownicy.txt", ios::in);
    if (plik.good() == false) {
        cout << "Plik z uzytkownikami jest pusty."<<endl;
        Sleep(1000);
    } else {
        while(getline(plik,linia)) {
            rozdzielDaneNaPojedynczeDaneOUzytkowniku (uzytkownicy,linia);
        }
        cout << "...";
        Sleep(500);
    }
    plik.close();
}


void rejestracja ( vector <Uzytkownik> &uzytkownicy) {

    Uzytkownik uzytkownik;
    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    vector <Uzytkownik> ::iterator itrEnd = uzytkownicy.end();

    if (uzytkownicy.empty() == true) {
        uzytkownik.idUzytkownika=1;
    } else {
        uzytkownik.idUzytkownika=uzytkownicy.back().idUzytkownika+1;
    } ;


    cout<< "Podaj nazwe uzytkownika: ";
    cin>>uzytkownik.nazwa;

    while (itr<itrEnd) {
        if (itr->nazwa == uzytkownik.nazwa) {
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>> uzytkownik.nazwa;
            itr=uzytkownicy.begin();
        } else {
            itr++;
        }
    }



    cout<<"Podaj haslo: ";
    cin>> uzytkownik.haslo;
    uzytkownicy.push_back(uzytkownik);

    cout<<"Konto zalozone."<<endl;
    Sleep(1000);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << uzytkownik.idUzytkownika <<"|"<<uzytkownik.nazwa<<"|"<<uzytkownik.haslo  << endl;

        plik.close();

        cout <<endl<< "Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
}

int logowanie (vector <Uzytkownik>& uzytkownicy) {
    Uzytkownik uzytkownik;
    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    vector <Uzytkownik> ::iterator itrEnd = uzytkownicy.end();
    string nazwa, haslo;
    cout<<"Podaj nazwe: ";
    cin>>nazwa;


    while (itr<itrEnd) {
        if (itr->nazwa == nazwa) {
            for (int proba=0; proba<3; proba++) {
                cout<<"Podaj haslo. Pozostalo prob: "<<3-proba<<": ";
                cin>> haslo;
                if (itr->haslo == haslo) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return itr->idUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo."<<endl;
            Sleep(3000);
            return 0;
        }
        itr++;
    }
    cout<<"Nie ma uzytkownika z takim loginem."<<endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector <Uzytkownik>& uzytkownicy,int idZalogowanegoUzytkownika) {
    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    vector <Uzytkownik> ::iterator itrEnd = uzytkownicy.end();
    string haslo;
    cout <<"Podaj nowe haslo: ";
    cin>>haslo;

    for(itr; itr != itrEnd; ++itr)

    {
        if(itr->idUzytkownika == idZalogowanegoUzytkownika) {
            itr->haslo = haslo;
            cout<<"Haslo zostalo zmienione."<<endl;
            Sleep(3000);
        }

    }
}

void przepiszPlik(vector <Uzytkownik>& uzytkownicy) {

    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    vector <Uzytkownik> ::iterator itrEnd = uzytkownicy.end();
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::trunc| ios::out);
    if (plik.good()) {
        for (itr; itr != itrEnd; ++itr) {
            plik << itr->idUzytkownika <<"|"<<itr->nazwa<<"|"<<itr -> haslo << endl;
        }
        plik.close();
        cout << endl<<"Dane zostaly zapisane." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: Uzytkowinc.txt" << endl;
    }
}


int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    int idZalogowanegoUzytkownika=0;
    int temp=0;

    char wybor=' ';
    while(1) {
        if (idZalogowanegoUzytkownika==0) {

            odczytajDaneUzytkownikow(uzytkownicy);
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin.sync();
            cin>> wybor;

            if (wybor=='1') {
                rejestracja(uzytkownicy);
            } else if (wybor=='2') {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy);
            } else if (wybor=='9') {
                exit(0) ;
            }
        }

        else {

            odczytajDane(adresaci,idZalogowanegoUzytkownika);
            temp = sprawdzOstatnieID();
            cout<<"Sprawdzamy id ostatniego uzytkownika"<<temp <<endl;
            Sleep(3000);
            wybor=wyswietlMenu();

            if (wybor == '1') {
                zapiszDane(adresaci,idZalogowanegoUzytkownika);
                Sleep(3000);
            } else if (wybor == '2') {
                wyszukajImie(adresaci);
            } else if (wybor == '3') {
                wyszukajNazwisko(adresaci);
            } else if (wybor == '4') {
                wyswietlAdresatow(adresaci);
                Sleep(19000);
            } else if (wybor == '5') {
                usunAdresata(adresaci);
                Sleep(3000);
            } else if (wybor == '6') {
                edycja (adresaci);
            } else if (wybor == '7') {
                zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
                przepiszPlik(uzytkownicy);
            } else if (wybor == '8') {
                idZalogowanegoUzytkownika=0 ;
            }
        }
    }
    return 0;
}
