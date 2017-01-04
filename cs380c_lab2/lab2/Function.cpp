#include "Function.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int> > Graph::result = vector<vector<int> >();

void Function::addEdge(int from, int to)
{
	if (edges.find(from) == edges.end())
		edges[from] = vector<int>();
	edges[from].push_back(to);
}

void Function::addCode(Code3addr c3a)
{
	codelist[c3a.getlineNumber()] = c3a;
	if (c3a.getBranch() != -1)
	{
		block.insert(c3a.getBranch());
		block.insert(c3a.getlineNumber() + 1);
		addEdge(c3a.getlineNumber(), c3a.getBranch());
	}
	else if (c3a.getCall() != -1)
	{
		block.insert(c3a.getlineNumber() + 1);
	}
	else if (c3a.isFunctionHead())
		block.insert(c3a.getlineNumber());
}

void Function::genCFG()
{
	for (set<int>::iterator it = block.begin(); it != block.end(); ++it)
	{
		if (*it != funStartLineNumber && codelist[*it - 1].getCodesplit()[0] != "br")
			addEdge(*it - 1, *it);
	}

	int curBlock = -1;
	for (int instr = funStartLineNumber; instr != funEndLineNumber + 1; ++instr)
	{
		if (block.find(instr) != block.end())
		{
			curBlock = instr;
		}
		if (edges.find(instr) != edges.end() && instr != curBlock)
		{
			edges[curBlock] = edges[instr];
			edges.erase(edges.find(instr));
		}
	}
	lastBlock = curBlock;
}

void Function::print()
{
	cout << "Function: " << funStartLineNumber << endl;
	cout << "Basic blocks: ";
	for (set<int>::iterator i = block.begin(); i != block.end(); ++i)
		cout << *i << " ";
	cout << endl << "jump:" << endl;
	for (map<int, vector<int> >::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		cout << it->first << " -> ";
		for (vector<int>::iterator i = it->second.begin(); i != it->second.end(); ++i)
		{
			cout << *i << " ";
		}
		cout << endl;
	}
}

void Function::printCFG()
{
	cout << "Function: " << funStartLineNumber << endl;
	cout << "Basic blocks:";
	for (set<int>::iterator i = block.begin(); i != block.end(); ++i)
		cout << " " << *i;
	cout << endl << "CFG:" << endl;
	for (map<int, vector<int> >::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		cout << it->first << " ->";
		vector<int> v = it->second;
		sort(v.begin(), v.end(), less<int>());
		unique(v.begin(), v.end());
		for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
		{
			cout << " " << *i;
		}
		cout << endl;
	}
	cout << lastBlock << " ->" << endl;
}

void Function::genSCR()
{
	Graph g(block.size());
	map<int, int> block2node;
	map<int, int> node2block;
	int count = 0;
	for (set<int>::iterator i = block.begin(); i != block.end(); ++i, ++count)
	{
		block2node[*i] = count;
		node2block[count] = *i;
		//cout << count << ":" << *i << endl;
	}
	for (map<int, vector<int> >::iterator i = edges.begin(); i != edges.end(); ++i)
	{
		int from = block2node[i->first];
		for (vector<int>::iterator j = i->second.begin(); j != i->second.end(); ++j)
		{
			g.addEdge(from, block2node[*j]);
			//cout << "add edge: " << i->first << "->" << *j << endl;
		}
	}

	g.getStrongConnected();
	cout << "SCR:" << endl;
	for (vector<vector<int> >::iterator i = Graph::result.begin(); i != Graph::result.end(); ++i)
	{
		if (i->size() > 1)
		{
			sort(i->begin(), i->end(), less<int>());
			for (vector<int>::iterator j = i->begin(); j != i->end(); ++j)
			{
				cout << node2block[*j] << " ";
			}
			cout << endl;
		}
	}
}