#include<iostream>
#include<fstream>
//#include<conio.h>
#include"Carlier.h"

using namespace std;

void wypiszdane(int **tab, int m)
{
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


int main()
{
	ifstream plik;
	plik.open("SCHRAGE1.DAT", ios_base::binary | ios_base::in);
	int iloscZadan = 0;
	plik >> iloscZadan;
	int **zad = new int*[iloscZadan];
	for (int i = 0; i < iloscZadan; i++)
	{
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
	Carlier Carl(Zadania);

	for (int i = 0; i < iloscZadan; i++) {
		delete[] zad[i];
	}
	delete[] zad;
	//_getch();
	return 0;
}
