#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include "page.h"

typedef unsigned int uint;

using std::cin;
using std::cout;
using std::endl;
//using std::vector;

class B_Tree
{
private:
    Page* root;
    uint power;
    uint height;
    const uint t = 2;
	std::ostream* str;
public:
	bool SwapL();
	bool SwapR();
	bool TurnLeft();
	bool TurnRight();
	void Balance();
    bool Paste(const int val);
    bool Remove(const uint pos);
	bool needTurns();
	bool needMerge();
	void merge();

    int GetVal(const uint pos);
    uint GetPos(const int val);

    bool SetVal(const uint pos, const int val);

    void print();

    B_Tree(int pw, std::ostream& s);
    B_Tree(std::ostream& s);
    ~B_Tree();
};

#endif // B_TREE_H
