#include "Carlier.h"
#include<climits>

int schrageP(vector<Zadanie> z)
{
	int t = 0;//chwila czasowa
	Zadanie l;//aktualnie wykonywane zadanie
	int cMax = 0;//maksymalny z terminow dostarczenia zadan
	vector<Zadanie> N;//zbior zadan nieuszeregowanych
	vector<Zadanie> G;//zbior zadan gotowych do realizacji
	vector<Zadanie> tmp;//zbior zadan tymczasowy
	Zadanie temp;//zadanie tymczasowe
	int minR = INT_MAX;//minimalny czas dostepnosci
	tmp = z;
	l.Wczytajdane(0, 0, INT_MAX);//zerowe aktualnie wykonywane zadanie r0=0,p0=0,q0=inf.

	//sortowanie zbioru N ze wzgledu na minimalny czas dostepnosci
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		for (unsigned int j = 1; j < tmp.size(); j++)
		{
			if (tmp[j].WypiszDostepnosc() < tmp[j - 1].WypiszDostepnosc())
			{
				int t = tmp[j].WypiszDostepnosc();
				tmp[j].WczytajDostepnosc(tmp[j - 1].WypiszDostepnosc());
				tmp[j - 1].WczytajDostepnosc(t);

				t = tmp[j].WypiszObsluge();
				tmp[j].WczytajObsuge(tmp[j - 1].WypiszObsluge());
				tmp[j - 1].WczytajObsuge(t);

				t = tmp[j].WypiszDostarczenie();
				tmp[j].WczytajDostarczenie(tmp[j - 1].WypiszDostarczenie());
				tmp[j - 1].WczytajDostarczenie(t);
			}
		}
		minR = (tmp[i].WypiszDostepnosc() < minR);
	}
	N = tmp;
	tmp.clear();

	//algorytm Schrage
	while ((!G.empty()) || (!N.empty()))//krok 2
	{
		while (!N.empty() && N.front().WypiszDostepnosc() <= t)//krok 3
		{
			G.push_back(N.front());//krok 4
			//N.erase(N.begin());
			if (N.front().WypiszDostarczenie() > l.WypiszDostarczenie())//krok 5
			{
				l.Wczytajdane(t -N.front().WypiszDostepnosc(),t-N.front().WypiszDostepnosc(),t -N.front().WypiszDostarczenie());
				//l.WczytajDostepnosc(t - N.front().WypiszDostepnosc());
				t = N.front().WypiszDostepnosc();
				if (l.WypiszObsluge() > 0)
				{
					G.push_back(l);
				}
			}
			N.erase(N.begin());
		}
		if (G.empty())//krok 6
		{
			t = N.front().WypiszDostepnosc();//krok 7
			continue;
		}
		//znajdowanie elementu zbioru G o najwiekszym czasie dostarczenia - sortowanie elementow zbioru
		//krok 8
		for (unsigned int j = 0; j < G.size(); j++)
		{
			for (unsigned int i = 1; i < G.size(); i++)
			{
				if (G[i].WypiszDostarczenie() > G[i - 1].WypiszDostarczenie())
				{
					temp = G[i];
					G[i] = G[i - 1];
					G[i - 1] = temp;
				}
			}
		}
		tmp.push_back(G.front());
		G.erase(G.begin());
		l = tmp.back();//krok 9
		t += tmp.back().WypiszObsluge();
		cMax = max(cMax, t + tmp.back().WypiszDostarczenie());
	}
	z.clear();
	z = tmp;
	tmp.clear();
	return cMax;
}


int schrage(vector<Zadanie> z)
{
	int t = 0;//chwila czasowa
	int k = 0;//pozycja w permutacji
	int cMax = 0;//maksymalny z terminów dostarczenia zadan
	vector<Zadanie> N;//zbior zadan nieuszeregowanych
	vector<Zadanie> G;//zbior zadan gotowych do realizacji
	vector<Zadanie> tmp;//zbior zadan tymczasowy
	Zadanie temp;//zadanie tymczasowe
	int minR = INT_MAX;//minimalny czas dostepnosci
	tmp = z;

	//sortowanie zbioru N ze wzgledu na minimalny czas dostepnosci
	for(unsigned int i=0;i<tmp.size();i++)
	{
		for (unsigned int j = 1; j < tmp.size(); j++)
		{
			if (tmp[j].WypiszDostepnosc() < tmp[j - 1].WypiszDostepnosc())
			{
				int t = tmp[j].WypiszDostepnosc();
				tmp[j].WczytajDostepnosc(tmp[j - 1].WypiszDostepnosc());
				tmp[j - 1].WczytajDostepnosc(t);

				t = tmp[j].WypiszObsluge();
				tmp[j].WczytajObsuge(tmp[j - 1].WypiszObsluge());
				tmp[j - 1].WczytajObsuge(t);

				t = tmp[j].WypiszDostarczenie();
				tmp[j].WczytajDostarczenie(tmp[j - 1].WypiszDostarczenie());
				tmp[j - 1].WczytajDostarczenie(t);
			}
		}
		minR = (tmp[i].WypiszDostarczenie() < minR);
	}
	N = tmp;
	tmp.clear();

	//algorytm Schrage
	while ((!G.empty()) || (!N.empty()))//krok 2
	{
		while (!N.empty() && N.front().WypiszDostepnosc() <= t)//krok 3
		{
			G.push_back(N.front());//krok 4
			N.erase(N.begin());
		}
		if (G.empty())//krok 5
		{
			t = N.front().WypiszDostepnosc();//krok 6
			continue;
		}
		//znajdowanie elementu zbioru G o najwiekszym czasie dostarczenia - sortowanie elementów zbioru
		for (unsigned int j = 0; j < G.size(); j++) {
			for (unsigned int i = 1; i < G.size(); i++)//krok7
			{
				if (G[i].WypiszDostarczenie() > G[i - 1].WypiszDostarczenie())
				{
					temp = G[i];
					G[i] = G[i - 1];
					G[i - 1] = temp;
				}
			}
		}
		tmp.push_back(G.front());//krok 8
		G.erase(G.begin());
		t += tmp.back().WypiszObsluge();
		cMax = max(cMax, t + tmp.back().WypiszDostarczenie());
		tmp.clear();
	}
	z.clear();
	z = tmp;
	tmp.clear();
	return cMax;
}


Carlier::Carlier(vector<Zadanie> tmp)
{
	zad = tmp;			//lista zadan
	n = zad.size();		//rozmiar listy zadan
	a = 0;
	b = 0;
	c = -1;
	UB = INT_MAX; // gorne oszacowanie
	U = 0; // wartosc funkcji celu Cmax
	LB = 0; // dolne oszacowanie
	r_prim = INT_MAX;
	q_prim = INT_MAX;
	p_prim = 0;
	r_mem = -2;
	q_mem = -2;
}

Carlier::~Carlier()
{
}

void Carlier::A() {
	int suma = 0;
	int najmniejsze = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i; j <= b; j++) {
			suma += zad[j].WypiszObsluge();
		}
		if (UB == suma + zad[i].WypiszDostarczenie() + zad[b].WypiszDostepnosc()) {
			if (i < najmniejsze) {
				najmniejsze = i;
			}
		}
	}
	a=najmniejsze;
}

void Carlier::B() {
	int najwieksze = 1;
	for (int i = 0; i < n; i++) {
		if (UB == zad[i].WypiszDostarczenie() + zad[i].WypiszDostepnosc()) {
			if (i > najwieksze) {
				najwieksze = i;
			}
		}
	}
	b=najwieksze;
}

void Carlier::C() {
	int najwieksze = -1;
	for (int i = b; i >= a; i--) {
		if (zad[i].WypiszDostepnosc() < zad[b].WypiszDostepnosc()) {
			if (i > najwieksze){
				najwieksze = i;
			}
		}
	}
	c=najwieksze;
}

int Carlier::WykonajAlgorytm() {
	U = schrage(zad);	//krok 1
	if (U < UB){    //krok 2
		UB = U;
	}

	B();   //krok 3
	A();
	C();

	//krok 4
	if (c == -1) {
		return U; //schrage znalazl rozwiazanie optymalne
	}

	//krok 5
	for (int i = c+1; i <= b; i++) {
		r_prim = min(zad[i].WypiszDostarczenie(), r_prim);
		q_prim = min(zad[i].WypiszDostepnosc(), q_prim);
		p_prim += zad[i].WypiszObsluge();
	}
	//zapamietanie r
	if (r_mem == -2)
	{
		r_mem = zad[c].WypiszDostarczenie();
	}
	//krok 6
	zad[c].WczytajDostarczenie(max(zad[c].WypiszDostarczenie(), r_prim + p_prim));

	//krok 7
	LB = schrageP(zad);

	//krok 8-9
	if (LB < UB) {
		UB=WykonajAlgorytm();
	}

	//krok 10
	zad[c].WczytajDostarczenie(r_mem);
	r_mem = -2;

	//zapamietanie q
	if (q_mem == -2)
	{
		q_mem = zad[c].WypiszDostepnosc();
	}
	//krok 11
	zad[c].WczytajDostepnosc(max(zad[c].WypiszDostepnosc(), q_prim + p_prim));

	//krok 12
	LB = schrageP(zad);

	//krok 13-14
	if (LB < UB) {
		UB=WykonajAlgorytm();
	}

	//krok 15
	zad[c].WczytajDostepnosc(q_mem);
	q_mem = -2;
}
