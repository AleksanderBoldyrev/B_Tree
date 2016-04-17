#include <iostream>
#include <ctime>
#include <cstdlib>

typedef unsigned int uint;

using namespace std;

#include "b_tree.h"
#include "page.h"

bool contains(vector<int>* v, int val)
{
	for (uint i = 0; i < v->size(); i++)
	{
		if (v->at(i) == val)
		{
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////

void testSorted(int c)
{
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree();
	cout << endl << "Adding "<< c << " elements sorted: " << endl;
	b = clock();
	for (int i = 1; i <= c; i++)
	{
		tr->Paste(i);
	}
	e = clock();
	cout << "Time: " << (e - b) / 1000.0 << " seconds" << endl;
	//tr->print();
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

void testUnsorted(int c)
{
	vector<int> v;
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree();
	cout << endl << "Adding " << c << " elements unsorted: " << endl;
	v.clear();
	srand(time(NULL));
	unsigned int t;
	b = clock();
	for (int i = 1; i <= c; i++)
	{
		t = rand() % c;
		while (contains(&v, t))
		{
			t = rand() % c;
		}
		tr->Paste(t);
		v.push_back(t);
	}
	e = clock();
	cout << "Time: " << (e - b) / 1000.0 << " seconds" << endl;
	//tr->print();
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

int main()
{
	for (int k = 25; k < 20000; k *= 2)
	{
		testSorted(k);
		testUnsorted(k);
	}
	system("pause");
    return 0;
}
