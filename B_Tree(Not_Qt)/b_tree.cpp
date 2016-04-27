#include "b_tree.h"

void B_Tree::print()
{
	vector<Page*> v;// = new QList<Page*>();
	vector<Page*> v2;// = new QList<Page*>();
    v.push_back(root);
    bool work = true;
    uint h = height;
    while (v.size()>0 && work)
    {
        work = false;
		string space;
		//Page* buff;
        for (uint k = 0; k<h*2; k++)
            space+=" ";
        *str << space;
		h--;
		v2.clear();
        for (uint i = 0; i < v.size(); i++)
        {
			if (v[i] != NULL)
			{
				for (uint j = 0; j < v[i]->GetSize(); j++)
				{
					v2.push_back(v[i]->GetChildren(j));
					*str << v[i]->GetKey(j) << ";";
					if (v[i]->GetChildren(j) != NULL)
						work = true;
				}
				v2.push_back(v[i]->GetChildren(v[i]->GetSize()));
				if (v[i]->GetChildren(v[i]->GetSize()) != NULL)
					work = true;
				*str << "  ";
			}
			else
			{
				*str << "N;" << " ";
				v2.push_back(NULL);
			}
        }
        *str << endl;
        *str << space;
        if (work)
            for (uint i = 0; i < v.size(); i++)
            {
				if (v[i] != NULL)
				{
					uint s = v[i]->GetSize();
					for (uint j = 0; j <= s; j++)
					{
						if ((float)j < s / 2.0)
							*str << "/" << " ";
						else if ((float)j == s / 2.0)
							*str << "|" << " ";
						else
							*str << "\\" << " ";
					}
				}
				else
					*str << "   ";
            }
		*str << endl;
		v = v2;
		v2.clear();
    }
}

bool B_Tree::Paste(const int val)
{
	if (this->root->AddKey(val))
	{
		Balance();
		return true;
	}
    return false;
}

bool B_Tree::Remove(const uint pos)
{
    if (this->root->RemoveKey(pos))
        return true;
    return false;
}

int B_Tree::GetVal(const uint pos)
{
    return this->root->GetKey(pos);
}

bool B_Tree::SwapL()
{
	Page* t = root->SwapL();
	if (t != NULL)
	{
		root = t;
		return true;
	}
	return false;
}

bool B_Tree::SwapR()
{
	Page* t = root->SwapR();
	if (t != NULL)
	{
		root = t;
		return true;
	}
	return false;
}

bool B_Tree::TurnRight()
{
	if (root != NULL)
	{
		Page* pp = root->TurnRight();
		if (pp!=NULL)
		{
			root = pp;
			return true;
		}
	}
	return false;
}

bool B_Tree::TurnLeft()
{
	if (root != NULL)
	{
		Page* pp = root->TurnLeft();
		if (pp!=NULL)
		{
			root = pp;
			return true;
		}
	}
	return false;
}

void B_Tree::merge()
{
	root->merge();
}

void B_Tree::Balance()
{
	int v;
	Page* r = new Page(power);
	Page* temp = NULL;
	bool isNotBalanced = this->root->Balance(&v, r);
	while (isNotBalanced)
	{
		if (r->GetSize() > 0)
		{
			temp = new Page(power);
			temp->RemoveChildren(0);
			temp->addToKeys(v);
			temp->AddChildren(root);
			temp->AddChildren(r);
			root = temp;
		}
		else
			delete r;
		r = new Page(power);
		r->RemoveChildren(0);
		bool kk = true;
		while (kk)
		{
			kk=SwapL();
			kk = SwapR();
			kk=TurnLeft();
			kk=TurnRight();
		}
		isNotBalanced = this->root->Balance(&v, r);
	}
	if (r != NULL)
		delete r;
}

bool B_Tree::needTurns()
{
	if (root->child[0] != NULL && root->child[root->GetSize()] != NULL)
		if (abs((int)root->child[0]->GetDepth() - (int)root->child[root->GetSize()]->GetDepth())>1)
			return true;
	return false;
}

bool B_Tree::needMerge()
{
	if (root->child[0] != NULL && root->child[root->GetSize()] != NULL)
		if (abs((int)root->child[0]->GetDepth() - (int)root->child[root->GetSize()]->GetDepth())==1)
			return true;
	return false;
}

uint B_Tree::GetPos(const int val)
{
    return this->root->GetPos(val);
}

bool B_Tree::SetVal(const uint pos, const int val)
{
    if (this->root->SetKey(pos, val))
        return true;
    return false;
}

B_Tree::B_Tree(int pw, std::ostream& s)
{
    power = pw;
    height = 16;
    root = new Page(t);
	str = &s;
}

B_Tree::B_Tree(std::ostream& s)
{
    power = 2;
    height = 16;
    root = new Page(t);
	str = &s;
}

B_Tree::~B_Tree()
{
	if (root != NULL) delete root;
}
