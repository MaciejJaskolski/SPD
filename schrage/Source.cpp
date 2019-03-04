/**
* SCHRAGE
*/

#include <cstdlib>
#include<iostream>
#include<fstream>
#include<string.h>
#include<climits>
//#include<conio.h>
#include<vector>

using namespace std;

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

void wypiszdane(int **tab, int m) {
	cout << "Dane wejsciowe" << endl;
	cout << "czas dostepnosci:czas obslugi:czas dostarczenia" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 3; j++) {
			cout << tab[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

class Zadanie {
	int czasDostepnosci;
	int czasObslugi;
	int czasDostarczenia;
public:
	Zadanie() {czasDostepnosci = czasObslugi = czasDostarczenia = 0;}
	~Zadanie(){}
	void WczytajDostepnosc(int r){ czasDostepnosci = r; }
	void WczytajObsuge(int p){ czasObslugi = p; }
	void WczytajDostarczenie(int q){ czasDostarczenia = q; }
	void Wczytajdane(int r, int p, int q)
	{
		WczytajDostepnosc(r);
		WczytajObsuge(p);
		WczytajDostarczenie(q);
	}
	int WypiszDostepnosc() { return czasDostepnosci; }
	int WypiszObsluge() { return czasObslugi; }
	int WypiszDostarczenie() { return czasDostarczenia; }
	void Wypiszdane()
	{
		cout << "czas dostepnosci:czas obslugi:czas dostarczenia" << endl;
		cout << WypiszDostepnosc() << "\t:" << WypiszObsluge() << "\t:" << WypiszDostarczenie() << endl;
	}

};

int schrage(vector<Zadanie> z)
{
	int t = 0;//chwila czasowa
	int k = 0;//pozycja w permutacji
	int cMax = 0;//maksymalny z termin�w dostarczenia zadan
	vector<Zadanie> N;//zbior zadan nieuszeregowanych
	vector<Zadanie> G;//zbior zadan gotowych do realizacji 
	vector<Zadanie> tmp;//zbior zadan tymczasowy
	Zadanie temp;//zadanie tymczasowe
	int minR = INT_MAX;//minimalny czas dostepnosci
	tmp = z;

	//sortowanie zbioru N ze wzgledu na minimalny czas dostepnosci
	for(int i=0;i<tmp.size();i++)
	{
		for (int j = 1; j < tmp.size(); j++)
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
		//znajdowanie elementu zbioru G o najwiekszym czasie dostarczenia - sortowanie element�w zbioru
		for (int j = 0; j < G.size(); j++) {
			for (int i = 1; i < G.size(); i++)//krok7
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

int main()
{
	ifstream plik;
	plik.open("SCHRAGE1.DAT", ios_base::binary | ios_base::in);

	int iloscZadan = 0;
	plik >> iloscZadan;
	int **zad = new int*[iloscZadan];
	for (int i = 0; i < iloscZadan; i++) {
		zad[i] = new int[3];
	}

	for (int i = 0; i < iloscZadan; i++) {
		for (int j = 0; j < 3; j++) {
			zad[i][j] = 0;
		}
	}

	for (int i = 0; i < iloscZadan; i++) {
		for (int j = 0; j < 3; j++) {
			plik >> zad[i][j];
		}
	}
	plik.close();
	vector<Zadanie> Zadania;
	Zadania.resize(iloscZadan);
	wypiszdane(zad, iloscZadan);
	for (int i = 0; i < iloscZadan; i++)
	{
			Zadania[i].Wczytajdane(zad[i][0], zad[i][1], zad[i][2]);
	}
	cout << "CMAX: " << schrage(Zadania) << endl;
	for (int i = 0; i < iloscZadan; i++) {
		delete[] zad[i];
	}
	delete[] zad;
	//_getch();
	return 0;
}
