#pragma once

#include<vector>
#include"Zadanie.h"
#include"Schrage.h"
#include"SchrageP.h"

using std::vector;

class Carlier
{
	vector<Zadanie> zad;
	int cmax;
	int UB, U, LB;
	int a, b, c;
	int r_prim, p_prim, q_prim;
	int r_mem, q_mem;
	int n;
public:
	Carlier(vector<Zadanie> zad);
	~Carlier();
	void A();
	void B();
	void C();
	int WykonajAlgorytm();
};
