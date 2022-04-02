#include <algorithm>

//Prototypy funkcji
template<typename Typ>
void introspectivesort(Typ *tab, int pierwszy,int ostatni,int maxdepth);

template<typename Typ>
void quicksort(Typ *tab, int pierwszy, int ostatni);

template<typename Typ>
void mergesort(Typ *tab, Typ *tmp, int pierwszy,int ostatni);
