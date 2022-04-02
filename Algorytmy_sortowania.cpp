#include "Algorytmy_sortowania.h"

using namespace std;

//Funkcja scala dwie tablice do jednej tablicy
//tab - tablica do posortowania
//tmp - tablica tymczasowa(pomocnicza)
//pierwszy - indeks pierwszego elementu do scalenia(pierwsza tablica)
//ostatni - indeks ostatniego elementu do scalenia (druga tablica)
//srodek - indeks elementu dzielacego tablice
template<typename Typ>
void scalanie(Typ *tab, Typ *tmp, int pierwszy,int ostatni,int srodek)
{
	int j=pierwszy,k=srodek;
    
    for(int i=pierwszy;i<=ostatni;i++){ //Dopoki nie scalona
       if( (j==srodek) || ( (k<=ostatni) && (tab[j]>tab[k]) ) ) 
        {
            tmp[i]=tab[k];
            k++;
           
        }else{
           tmp[i]=tab[j];
           j++;
        }  

    }   
    for(int i=pierwszy;i<=ostatni;i++)
    tab[i]=tmp[i];
}

//Funkcja wykonujaca sortowanie przez scalanie
//tab - tablica do posortowania
//tmp - tablica tymczasowa(pomocnicza)
//pierwszy - indeks pierwszego elementu do scalenia(pierwsza tablica)
//ostatni - indeks ostatniego elementu do scalenia (druga tablica)
template<typename Typ>
void mergesort(Typ *tab, Typ *tmp, int pierwszy,int ostatni)
{
	int j=(pierwszy+ostatni)/2;  // Dzielimy problem na 2 czesci

  if(ostatni!=pierwszy){   // Wykonujemy gdy jest wiecej niz 1 element
    mergesort<Typ>(tab,tmp,pierwszy,j);  // Sortujemy pierwsza czesc problemu
    mergesort<Typ>(tab,tmp,j+1,ostatni);  // Sortujemy druga czesc problemu
    scalanie<Typ>(tab,tmp,pierwszy,ostatni,j+1); // Scalamy ze soba 2 posortowane problemy
  }
}

//Funkcja znajdujaca pivota
//tab - tablica do posortowania
//pierwszy - indeks pierwszego elementu
//ostatni - indeks ostatniego elementu
template<typename Typ>
int pivot(Typ *tab,int pierwszy,int ostatni)
{
     int j=tab[(pierwszy+ostatni)/2],k=pierwszy; // Wybranie pivota jako srodkowy element
  
  tab[(pierwszy+ostatni)/2]=tab[ostatni];
  
  for(int i=pierwszy;i<ostatni;i++){  //Od pierwszego do ostatniego
  
    
      if(tab[i]<j){
        swap(tab[i],tab[k]); //Zamiana elementow miejscami jesli sa zle ustawione
        k++;
      }
    }
  
  tab[ostatni]=tab[k];
  tab[k]=j;
return k;
}

//Funkcja wykonujaca sortowanie szybkie
//tab - tablica do posortowania
//pierwszy - indeks pierwszego elementu
//ostatni - indeks ostatniego elementu
template<typename Typ>
void quicksort(Typ *tab, int pierwszy, int ostatni)
{
    if (pierwszy < ostatni) // Jesli jest co sortowac
    {
        int j = pivot(tab, pierwszy, ostatni); //Dzielimy na 2 tablice
        quicksort(tab, pierwszy, j);//Sortujemy pierwsza tablice
        quicksort(tab, j + 1, ostatni);//Sortujemy druga tablice
    }
}



//Funkcja wykonujaca sortowanie przez wstawienie
//Potrzebna do wykonania sortowania introspketywnego
//tab - tablica do posortowania
//pierwszy - indeks pierwszego elementu
//ostatni - indeks ostatniego elementu
template<typename Typ>
void insertionsort(Typ *tab, int pierwszy,int ostatni)
{
	  int tmp=0,i;
  
  for(int j=ostatni-2;j>=pierwszy;j--)
  {
    tmp= tab[j]; // Wyciagamy element nieposortowany
    i = j + 1;
    while((i < ostatni) && (tmp > tab[i])) //Porownujemy wyciagniety element do pozostalych
    {
      tab[i - 1] = tab[i];//Wyciagniety element wstawiamy tam gdzie skonczylismy porownywac
      i++;
    }
    tab[i - 1] = tmp;
  }
}

//Funkcja tworzaca kopiec, potrzebny do wykonania sortowania przez kopcowanie
//tab - tablica do stworzenia kopca
//n - ilosc elementow do posortowania
//id - korzen kopca
template<typename Typ>
void kopiec(Typ *tab,int n,int id){
  int idt=id,j=2*id+1,k=2*id+2;

  if(j<n && tab[j]>tab[idt]) //Sprawdzamy ktory elemnt kopca jest najwiekszy
  {
    idt=j;
  }
  else idt=id;
  
  if(k<n && tab[k]>tab[idt])
    idt=k;

  if(idt !=id){
    swap(tab[id],tab[idt]);
    kopiec(tab,n,idt);
  }

}

//Funkja wykonujaca sortowanie przez kopcowanie
//Potrzebna do wykonania sortowania introspketywnego
//tab - tablica do posortowania
//n - ilosc elementow do posortowania
template<typename Typ>
void heapsort(Typ *tab, int n)
{
	for (int i=n/2-1;i>=0;i--) 
        kopiec(tab,n,i); 
  
    for (int i=n-1; i>=0; i--) 
    { 
        swap(tab[0], tab[i]);  //Przenosimy korzen na koniec kopca
        kopiec(tab,i,0);  // Budujemy kopiec na zmniejszonej ilosci danych (pomniejszonym kopcu)
    } 
}


//Funkcja wykonujaca sortowanie introspektwne
//tab - tablica do posortowania
//pierwszy - indeks pierwszego elementu
//ostatni - indeks ostatniego elementu
//maxdepth - parametr na okreslenie glebokosci rekurencji (logarytm liczby elementow do posortowania)
template<typename Typ>
void introspectivesort(Typ *tab, int pierwszy,int ostatni,int maxdepth)
{
	int j;
  if((ostatni-pierwszy)<=0) return;

  if(ostatni-pierwszy>16){
    
    if(maxdepth==0){
    heapsort(tab+pierwszy,(ostatni-pierwszy+1));  //Jesli jest kwadratowa zlozonosc to  wykonujemy sortowanie przez kopcowanie
    }
    
    maxdepth--;
    j=pivot(tab,pierwszy,ostatni); // Dzielimy tablice na 2 podtablice tak jak w sortowaniu szybkim
    introspectivesort(tab,pierwszy,j-1,maxdepth); //Wykonujemy sortowanie pierwszej podtablicy
    introspectivesort(tab,j+1,ostatni,maxdepth);//Wykonujemy sortowanie drugiej podtablicy
   
  }else{
  insertionsort(tab,pierwszy,ostatni+1); // Dla malych tablic sortujemy przez wstawianie
  }
}





template void introspectivesort<int>(int*, int, int,int);
template void mergesort<int>(int*, int*, int,int);
template void quicksort<int>(int*, int, int);

