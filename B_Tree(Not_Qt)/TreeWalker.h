#ifndef TREE_WALKER_H
#define TREE_WALKER_H

#pragma once

#include "b_tree.h"

class TreeWalker
{
private:
	std::ofstream checkStream(std::ostream& tt);
public:
	TreeWalker();
	~TreeWalker();

	template<typename TYPE> void printData(std::ostream& str, TYPE data);

	friend std::ostream& operator<<(std::ostream& str, B_Tree& b);

	void print(std::ostream& os, B_Tree& tr);
};

template<typename TYPE>
inline void TreeWalker::printData(std::ostream& str, TYPE data)
{
	std::ostream* fff;
	if (!str)
		fff = &cout;
	else
		fff = &str;
	*fff << data;	
}

#endif