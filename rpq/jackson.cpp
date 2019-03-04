/**
* JACKSON
*/

#include<iostream>
#include<fstream>
#include<vector>
//#include<conio.h>
#include<string.h>
#include<algorithm>

using namespace std;

struct Maszyna {
	int liczbaZadan;
	vector<int> czasTrwania;
	vector<int> czasRozpoczecia;
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
	}
}
void Pokaz()
{
	for (int i = 0; i < maszyna.liczbaZadan; i++)
	{
		cout<< "Czas rozpoczecia: " << maszyna.czasRozpoczecia[i] << endl;
		cout << "Czas trwania: " << maszyna.czasTrwania[i] << endl;
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
			}

	}
}
void print(int x) {
	//cout << x << endl;
}
int Cmax()
{
	//Pokaz();
	vector<int> start;
	start.push_back(maszyna.czasRozpoczecia[0]);	
	for (int i = 1; i < maszyna.liczbaZadan; i++)
	{
		start.push_back(Max(start.back() + maszyna.czasTrwania[i-1],
						    maszyna.czasRozpoczecia[i]));
	}
	for_each(start.begin(), start.end(), print);
	return start.back() + maszyna.czasTrwania[maszyna.liczbaZadan-1];
}

int main()
{
	WczytajDaneZPliku("JACK1.DAT");
	Posortuj();
	cout << "CMAX: " << Cmax() << endl;
	//_getch();
	return 0;
}
