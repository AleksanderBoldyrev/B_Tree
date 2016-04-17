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
        cout << space;
		h--;
		v2.clear();
        for (uint i = 0; i < v.size(); i++)
        {
			if (v[i] != NULL)
			{
				for (uint j = 0; j < v[i]->GetSize(); j++)
				{
					v2.push_back(v[i]->GetChildren(j));
					cout << v[i]->GetKey(j) << ";";
					if (v[i]->GetChildren(j) != NULL)
						work = true;
				}
				v2.push_back(v[i]->GetChildren(v[i]->GetSize()));
				if (v[i]->GetChildren(v[i]->GetSize()) != NULL)
					work = true;
				cout << "  ";
			}
			else
			{
				cout << "N;" << " ";
				v2.push_back(NULL);
			}
        }
        cout << endl;
        cout << space;
        if (work)
            for (uint i = 0; i < v.size(); i++)
            {
				if (v[i] != NULL)
				{
					uint s = v[i]->GetSize();
					for (uint j = 0; j <= s; j++)
					{
						if ((float)j < s / 2.0)
							cout << "/" << " ";
						else if ((float)j == s / 2.0)
							cout << "|" << " ";
						else
							cout << "\\" << " ";
					}
				}
				else
					cout << "   ";
            }
		cout << endl;
		v = v2;
		v2.clear();
    }
}

bool B_Tree::Paste(const int val)
{
	//cout << "======================================================================" << endl;
	//print();
	//cout << " before paste " << endl;
	if (this->root->AddKey(val))
	{
		//print();
		//cout << " after paste " << endl;
		Balance();
		//print();
		//cout << " after balance " << endl;
		//cout << "===================================================================" << endl;
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
		//print();
		//cout << "SWAP L" << endl;
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
		//print();
		//cout << "SWAP R" << endl;
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
			//print();
			//cout << "TURN R" << endl;
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
			//print();
			//cout << "TURN L" << endl;
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
	//cout << "before" << endl;
	//print();
	bool isNotBalanced = this->root->Balance(&v, r);
	//cout << "after" << endl;
	//print();
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
		//print();
		//cout << "root - > balance" << endl;
		//print();
		//cout << "S1" << endl;
		//print();
		//cout << "after" << endl;
		//print();
		//cout << "S2" << endl;
		bool kk = true;
		while (kk)
		{
			//cout << "S2.1" << endl;
			
			kk=SwapL();
			//print();
			//cout << kk << " 1 " << root->keys[0] << endl;
			kk=SwapR();
			//print();
			//cout << kk << " 2 " << root->keys[0] << endl;
			kk=TurnLeft();
			//print();
			//cout << kk << " 3 " << root->keys[0] << endl;
			kk=TurnRight();
			//print();
			//cout << kk << " 4 " << root->keys[0] << endl;
			//if (needTurns())
				//kk = true;
		}
		//print();
		//cout << "SWAPS" << endl;
		//if(needMerge()) merge();
		//print();
		//cout << "MERGE" << endl;

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

B_Tree::B_Tree(int pw)
{
    power = pw;
    height = 16;
    root = new Page(t);
}

B_Tree::B_Tree()
{
    power = 2;
    height = 16;
    root = new Page(t);
}

B_Tree::~B_Tree()
{
    if (root != NULL) delete root;
}
