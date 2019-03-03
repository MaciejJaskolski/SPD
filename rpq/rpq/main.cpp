#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<climits>

using namespace std;

struct Maszyna {
	int liczbaZadan;
	vector<int> czasTrwania;
	vector<int> czasRozpoczecia;
	vector<int> czasZakonczenia;
};

Maszyna maszyna;

int Max(int a, int b)
{
	if (a >= b) return a;
	return b;
}
void WczytajDaneZPliku(string nazwaPliku) {
	fstream stream;
	stream.open(nazwaPliku, ios_base::binary | ios_base::in);
	stream >> maszyna.liczbaZadan;
	for (int i = 0; i < maszyna.liczbaZadan; i++)
	{
		int tmp = 0;
		stream >> tmp;
		maszyna.czasRozpoczecia.push_back(tmp);
		stream >> tmp;
		maszyna.czasTrwania.push_back(tmp);
		stream >> tmp;
		maszyna.czasZakonczenia.push_back(tmp);
	}
}
void Pokaz()
{
	for (int i = 0; i < maszyna.liczbaZadan; i++)
	{
		cout<< "Czas rozpoczecia: " << maszyna.czasRozpoczecia[i] << endl;
		cout << "Czas trwania: " << maszyna.czasTrwania[i] << endl;
		cout << "Czas zakonczenia: " << maszyna.czasZakonczenia[i] << endl;
		cout << "---\n";
	}
}
void Swap(int &a,int &b) 
{
	int tmp = a;
	a = b;
	b = tmp;
}
void Posortuj()
{
	for (int i = 1; i < maszyna.liczbaZadan; i++)
	{
		for (int j = 0; j<maszyna.liczbaZadan; j++)
			if (maszyna.czasRozpoczecia[i] < maszyna.czasRozpoczecia[j])
			{
				Swap(maszyna.czasRozpoczecia[i], maszyna.czasRozpoczecia[j]);
				Swap(maszyna.czasTrwania[i], maszyna.czasTrwania[j]);
				Swap(maszyna.czasZakonczenia[i], maszyna.czasZakonczenia[j]);
			}

	}
}

int Cmax()
{	
	Posortuj();
	int cmax = 0;
	int m = 0;
	for(int i =0;i<maszyna.liczbaZadan;i++) {
		m = Max(m, maszyna.czasRozpoczecia[i]) + maszyna.czasTrwania[i];
		cmax = Max(cmax, m + maszyna.czasZakonczenia[i]);
	}
	return cmax;
}

int main()
{
	WczytajDaneZPliku("JACK1.DAT");
	Pokaz();
	cout << "CMAX: " << Cmax() << endl;
	return 0;
}