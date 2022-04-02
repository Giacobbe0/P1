#include "Algorytmy_sortowania.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;


//Funkcja wypisujaca tablice na stdout
template<typename Typ>
void wypisz_tabele(Typ *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << tab[i] << " ";
    }
      cout<<endl;
}


//Funkja dynamicznie alokujaca miejsce na tablice
template<typename Typ>
Typ *stworz_tabele(int n)
{
	return new Typ[n];
}

//Funkcja usuwajaca zaalokowana pamiec
template<typename Typ>
void usun_tabele(Typ *tab)
{
	delete[] tab;
}


//Funkja wypelniajaca tablice n losowych elementow z przedzialu 1-100000
template<typename Typ>
void zapelnij_tabele(Typ *tab, int n)
{
	for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 100000 + 1;
    }
}


//Funkja sortujaca zadany procent tablicy
template<typename Typ>
void procent_sortowania(Typ *tab, int n, double procent)
{
    if (procent == 100) //Jesli tablica ma byc posortowana w 100% to trzeba ja obrocic
    {
        sort(tab, tab + n, greater<Typ>());
        return;
    }
	sort(tab, tab + (int)((n*procent) / 100));
}

//Funkja sprawdzjaca czy tablica jest posortowana
template<typename Typ>
void czy_posortowana(Typ *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            cout << "Tablica zle posortowana";
            cin.get();
            exit(1);
        }
    }
}

//Funcja sprawdzajaaca czy zostala otworzona scierzka do zapisu
void check_if_open (ofstream &file)
{
    if (!file.is_open())
     {
        cout << "Plik do zapisu nie zostal otworzony";
        cin.get();
        exit(1);
     }
}


//Funkcje sortowania tabeli za pomoca algorytmu przekazywanego przez wskaznik
//Zwraca rowniez czas sortowania w milisekundach
template<typename Typ>
double sortowanie_szybkie(int n, Typ *tab)
{
    auto t_start = chrono::high_resolution_clock::now(); //Uruchomienie zegara
    quicksort(tab, 0, n-1);
    auto t_end = chrono::high_resolution_clock::now(); //zatrzymanie zegara

    return chrono::duration<double, milli>(t_end - t_start).count(); //Zwraca czas sortowania
}
template<typename Typ>
double sortowanie_scalanie(int n, Typ *tab,Typ *tmp)
{
    auto t_start = chrono::high_resolution_clock::now();
    mergesort(tab,tmp, 0, n-1);
    auto t_end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t_end - t_start).count();
}

template<typename Typ>
double sortowanie_introspektywne(int n, Typ *tab, Typ *tmp)
{
    auto t_start = chrono::high_resolution_clock::now(); 
    introspectivesort(tab, 0,n-1, log(n) * 2);
    auto t_end = chrono::high_resolution_clock::now(); 

    return chrono::duration<double, milli>(t_end - t_start).count();
}

int main()
{
    ofstream file("Dane.txt");
    check_if_open(file);

    srand(time(NULL));

	int liczba_tabeli = 1; //Liczba tabel ktore beda sortowane w danej konfiguracji
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000}; //tablica zawierajaca rozmiary tablic do sortowania
	double procenty[8] = {0, 25, 50, 75, 95, 99, 99.7, 100 }; //tablica zawierajaca informacje o procencie posortowanych tablic

	double licznik = 0;
	int nazwa = 0;
	string sortowania[3] = {"Sortowanie Szybkie", "Sortowanie przez Scalanie", "Sortowanie Introspektywne"};

       cout << sortowania[nazwa++] << endl;
        for (double procent : procenty) //Sortowanie tablic dla kazdej wartosci wczesniejszego posortowania
        {
            cout << procent << " % Posortowanej Tablicy" << endl;
            for (int n : ntab) // Sortowanie dla kazdego rozmiaru tablic
            {
                int *tab = stworz_tabele<int>(n); //Tworzenie dynamicznie tabel
                int *tmp = stworz_tabele<int>(n);

                for (int i = 0; i < liczba_tabeli; i++) //Sotowanie zadanej liczby tabel w danej konfiguracji
                {
                    zapelnij_tabele<int>(tab, n); //Wypelnienie tablicy losowymi elementami
                    procent_sortowania<int>(tab, n, procent);//Sortowanie zadanego procenta tabeli
                    licznik += sortowanie_szybkie<int>(n, tab);//Wykonanie sortowania pozostalej czesci tablicy
                    czy_posortowana<int>(tab, n);//Sprawdzenie czy tablica zostala prawidlowo posortowana

                    cout << i << "%" << "\r";
                }
                usun_tabele<int>(tab);//Usuwanie dynamicznie zaalokowanej tablicy
                usun_tabele<int>(tmp);

                cout << n << " Elementowa tablica Posortowana" << endl;

                file << licznik/liczba_tabeli  << " "; //Zapisanie srednego czasu sortowania do pliku
                licznik = 0;
            }
    
        }
        file << "\n";
    cout << "Wykonano Sortowanie Szybkie!"<<endl;
	
     cout << sortowania[nazwa++] << endl;
        for (double procent : procenty)
        {
            cout << procent << " % Posortowanej Tablicy" << endl;
            for (int n : ntab) 
            {
                int *tab = stworz_tabele<int>(n);
                int *tmp = stworz_tabele<int>(n);

                for (int i = 0; i < liczba_tabeli; i++)
                {
                    zapelnij_tabele<int>(tab, n);
                    procent_sortowania<int>(tab, n, procent);
                    licznik += sortowanie_scalanie<int>(n, tab,tmp);
                    czy_posortowana<int>(tab, n);

                    cout << i << "%" << "\r";
                }
                usun_tabele<int>(tab);
                usun_tabele<int>(tmp);

                cout << n << " Elementowa tablica Posortowana" << endl;

                file << licznik/liczba_tabeli << " ";
                licznik = 0;
            }
        }
        file << "\n";
    cout << "Wykonano sortowanie przez scalanie"<<endl;
	
     cout << sortowania[nazwa++] << endl;
        for (double procent : procenty) 
        {
            cout << procent << " % Posortowanej Tablicy" << endl;
            for (int n : ntab) 
            {
                int *tab = stworz_tabele<int>(n);
                int *tmp = stworz_tabele<int>(n);

                for (int i = 0; i < liczba_tabeli; i++) 
                {
                    zapelnij_tabele<int>(tab, n);
                    procent_sortowania<int>(tab, n, procent);
                    licznik += sortowanie_introspektywne<int>(n, tab,tmp);
                    czy_posortowana<int>(tab, n);

                    cout << i << "%" << "\r";
                }
                usun_tabele<int>(tab);
                usun_tabele<int>(tmp);

                cout << n << " Elementowa tablica posortowana" << endl;

                file << licznik/liczba_tabeli << " ";
                licznik = 0;
            }
        }
        file << "\n";
    cout << "Wykonano sortowanie Introspektywne"<<endl;

    file.close();

    /*int t=10;         //Wizualne sprawdzenie poprawnosci sortowania dla malych tabel
    int *tabt = stworz_tabele<int>(t);
    int *tmpt = stworz_tabele<int>(t);
    zapelnij_tabele<int>(tabt, t);
    cout<<"Tabela przed sortowaniem:"<<endl;
    wypisz_tabele(tabt,t);
    procent_sortowania<int>(tabt, t, 0);
    sortowanie_szybkie<int>(t, tabt);
    czy_posortowana<int>(tabt, t);
    cout<<"Tabela po sortowaniu"<<endl;
    wypisz_tabele(tabt,t);
    usun_tabele<int>(tabt);
    usun_tabele<int>(tmpt);*/

	return 0;
}

