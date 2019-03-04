#pragma once

#include<iostream>

using namespace std;

class Zadanie {
	int czasDostepnosci;
	int czasObslugi;
	int czasDostarczenia;
public:
	Zadanie() { czasDostepnosci = czasObslugi = czasDostarczenia = 0; }
	~Zadanie() {}
	void WczytajDostepnosc(int r) { czasDostepnosci = r; }
	void WczytajObsuge(int p) { czasObslugi = p; }
	void WczytajDostarczenie(int q) { czasDostarczenia = q; }
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

int max(int a, int b);
int min(int a, int b);