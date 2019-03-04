/**
* NEH
*/

#include<iostream>
#include<vector>
#include<string.h>
#include<fstream>
#include<climits>
//#include<conio.h>

using namespace std;

struct Data
{
	vector<int> data;
	int sum;

	int size() { return data.size(); }
};

vector<Data> times;
int numJobs, numMachines = 1;

//*
int ReturnSum(int num) {
	int suma  =0;
	for (int i = 0; i < numMachines; i++)
		suma += times[num].data[i];

	return suma;
}

//*returns greater value
int Max( int a, int b ){
	if (a >= b) return a;
	return b;
}

//*loads data from file
void LoadFromFile(string filename)
{
	ifstream is;
	is.open(filename, ios_base::in | ios_base::binary);

	//wczytanie liczby zadan i liczby maszyn
	is >> numJobs;
	is >> numMachines;

	times.resize(numJobs);
	for (int i = 0; i < numJobs; i++)
	{
		times[i].data.resize(numMachines);
	}

	int t;
	vector<int> tmp;
	for (int i = 0; i < numJobs; i++) 
	{
		for (int j = 0; j < numMachines; j++)
		{
			is >> t;
			tmp.push_back(t);
		}	
		times[i].data = tmp;
		tmp.clear();
	}
}

//*shows data
void Show()
{
	for (int i = 0; i < numJobs; i++)
	{
		for (int j = 0; j < numMachines; j++)
		{
			std::cout << times[i].data[j] << ": ";
		}
		cout<<"SUMA: " << times[i].sum << std::endl;
	}
}

//*swaps vectors
void Swap(Data &a, Data &b)
{
	Data tmp =a ;
	a = b;
	b = tmp;
}

//*sorts vectors by descending order by sum of finishing a job on diffeent machines
void Sort(string filename)
{
	LoadFromFile(filename);
	for (int i = 0; i < numJobs; i++) {
			times[i].sum = ReturnSum(i);
	}
	
	//times[i] po sumie czasu
	for (int i = 1; i < numJobs; i++)
	{
		for(int j=0;j<numJobs;j++)
			if (times[i].sum > times[j].sum)
				Swap(times[i], times[j]);
	}

	Show();
	
	//odwracanie kolejnosci wektora
	//reverse(times.begin(), times.end());

}

//return max time 
int cmax(vector<Data> &a)
{
	const int jb = a.size();
	const int mc = a[0].size();

	vector<Data> vecCmax;
	Data tmp;
	int x = 0;
	for (int i = 0; i < mc; i++)
		tmp.data.push_back(x);
	for (int i = 0; i < jb; i++) 
		vecCmax.push_back(tmp);
	
	for (int i = 0; i < jb; i++) {
		for (int j = 0; j < mc; j++) {
			if (i == 0 && j == 0)
				vecCmax[i].data[j] = a[i].data[j];
			else if (j == 0)
				vecCmax[i].data[j] = a[i].data[j] + vecCmax[i - 1].data[j];
			else if (i == 0)
				vecCmax[i].data[j] = a[i].data[j] + vecCmax[i].data[j - 1];
			else {
				vecCmax[i].data[j] = Max(
					a[i].data[j] + vecCmax[i].data[j - 1],
					a[i].data[j] + vecCmax[i - 1].data[j]
				); //end of MAX()
			} //end of else
		} //end of for(j)
	} //end of for(i)

	return vecCmax[jb-1].data[mc-1];
}

//*inserts element into given position
void InsertElement(vector<Data> &v, int pos, Data newElem)
{
	v.insert(v.begin() + pos, newElem);
}

//*copies old vector into a new one
void CopyVector(vector<Data> old, vector<Data> &newVec)
{
	for (int i = 0; i < newVec.size(); i++) {
		newVec[i].data.clear();
	}
	newVec.clear();
	
	copy(old.begin(), old.end(), back_inserter(newVec));
}

int AllInserts(vector<Data> list, Data job, vector<Data> &result)
{
	int maxCmax = INT_MAX;
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		vector<Data> data;

		CopyVector(list, data);
		InsertElement(data, i, job);

		int tmpCmax = cmax(data);
		if (tmpCmax < maxCmax)
		{
			maxCmax = tmpCmax;
			CopyVector(data, result);
		}

	}
	return maxCmax;
}

int NEH()
{
	int maxCmax = 0;
	vector<Data> bestPerm;
	Data job;
	int prevCmax = 0;
	for (int i = 0; i < times[numJobs - 1].size(); i++)
	{
		job.data.push_back(times[numJobs - 1].data[i]);
	}
	times.pop_back();
	
	bestPerm.push_back(job);

	job.data.clear();

	int n = times.size();
	while (n--)
	{
		for (int i = 0; i < times[n].size(); i++)
		{
			job.data.push_back(times[n].data[i]);
		}

		times.pop_back();
		
		vector<Data> res;
		maxCmax = AllInserts(bestPerm, job, res);
		//if (maxCmax > prevCmax)
		CopyVector(res, bestPerm);
		
		prevCmax = maxCmax;
		job.data.clear();
	}
	return  maxCmax;
}


//******
//-MAIN-
//******
int main() {
	Sort("NEH1.DAT");
	cout << "CMAX: " << NEH() << endl;

	//_getch();

	return 0;
}

