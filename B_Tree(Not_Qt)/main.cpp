#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

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

void testSorted(int c, std::ostream& s)
{
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(s);
	s << endl << "Adding "<< c << " elements sorted: " << endl;
 	b = clock();
	for (int i = 1; i <= c; i++)
	{
		tr->Paste(i);
	}
	e = clock();
	s << "Time: " << (e - b) / 1000.0 << " seconds" << endl;
	//tr->print();
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

void testUnsorted(int c, std::ostream& s)
{
	vector<int> v;
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(s);
	s << endl << "Adding " << c << " elements unsorted: " << endl;
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
	s << "Time: " << (e - b) / 1000.0 << " seconds" << endl;
	//tr->print();
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

void testZeroLen(int c, std::ostream& s)
{
	vector<int> v;
	clock_t b;
	clock_t e;
	B_Tree* tr = new B_Tree(s);
	s << endl << "Adding " << c << " elements unsorted: " << endl;
	v.clear();
	srand(time(NULL));
	unsigned int t;
	b = clock();
	t = rand() % c;
	while (contains(&v, t))
	{
		t = rand() % c;
	}
	tr->Paste(t);
	v.push_back(t);
	e = clock();
	s << "Time: " << (e - b) / 1000.0 << " seconds" << endl;
	//tr->print();
	delete tr;
}
//////////////////////////////////////////////////////////////////////////////

int main()
{
	std::ostream* s;
	std::ofstream f("result.txt", std::ofstream::out);
	// modify this to use another output thread
	s = &cout;

	B_Tree* tr = new B_Tree(*s);
	for (int j = 1; j < 66; j++)
	{
		tr->Paste(j);
	}
	tr->print();
	for (int k = 25; k < 5000; k *= 2)
	{
		testSorted(k, *s);
		testUnsorted(k, *s);
	}
	testZeroLen(1, *s);
	f.close();
	system("pause");
    return 0;
}
