#include "Function.h"
#include "tools.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int> > Graph::result = vector<vector<int> >();

void Function::addEdge(int from, int to)
{
	if (edges.find(from) == edges.end())
		edges[from] = vector<int>();
	edges[from].push_back(to);

	if (edges_jump_from.find(to) == edges_jump_from.end())
		edges_jump_from[to] = vector<int>();
	edges_jump_from[to].push_back(from);
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

	if (c3a.getDef() != "")
	{
		string name = c3a.getDef();
		if (variable_defpos.find(name) == variable_defpos.end())
			variable_defpos[name] = set<int>();
		variable_defpos[name].insert(c3a.getlineNumber());
	}
}

void Function::genCFG()
{
	for (set<int>::iterator it = block.begin(); it != block.end(); ++it)
	{
		if (*it != funStartLineNumber && codelist[*it - 1].getCodesplit()[0] != "br")
			addEdge(*it - 1, *it);
		codelist[*it].setBlockHead();
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
			codelist[instr].setBlockTail();
		}
	}
	lastBlock = curBlock;
}

void Function::print()
{
	for (map<int, Code3addr>::iterator itr = codelist.begin(); itr != codelist.end(); ++itr)
	{
		itr->second.print();
		cout << endl;
	}

	cout << "Function: " << funStartLineNumber << endl;
	cout << "Basic blocks: ";
	for (set<int>::iterator i = block.begin(); i != block.end(); ++i)
		cout << *i << " ";
	cout << endl << "jump from:" << endl;
	for (map<int, vector<int> >::iterator it = edges_jump_from.begin(); it != edges_jump_from.end(); ++it)
	{
		cout << it->first << " -> ";
		for (vector<int>::iterator i = it->second.begin(); i != it->second.end(); ++i)
		{
			cout << *i << " ";
		}
		cout << endl;
	}

	for (map<string, set<int> >::iterator it = variable_defpos.begin(); it != variable_defpos.end(); ++it)
	{
		cout << it->first << " def in : ";
		for (set<int>::iterator i = it->second.begin(); i != it->second.end(); ++i)
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

void Function::runSCP()
{
	in.clear();
	out.clear();
	for (int i = funStartLineNumber; i != funEndLineNumber + 1; ++i)
	{
		in[i] = out[i] = set<int>();
	}

	bool change = true;
	while (change)
	{
		change = false;
		for (int i = funStartLineNumber + 1; i != funEndLineNumber + 1; ++i)
		{
			if (codelist[i].isBlockHead())
			{
				in[i].clear();
				for (vector<int>::iterator it_from = edges_jump_from[i].begin(); it_from != edges_jump_from[i].end(); ++it_from)
				{
					for (set<int>::iterator it_from_ele = out[*it_from].begin(); it_from_ele != out[*it_from].end(); ++it_from_ele)
					{
						in[i].insert(*it_from_ele);
					}
				}
			}
			else
				in[i] = out[i - 1];

			set<int> out_old = out[i];
			if (codelist[i].getDef() != "")
			{
				set<int> defSet = variable_defpos[codelist[i].getDef()];
				out[i].clear();
				set_difference(in[i].begin(), in[i].end(), defSet.begin(), defSet.end(), inserter(out[i], out[i].begin()));
				out[i].insert(i);
			}
			else
				out[i] = in[i];

			if (!change)
			{
				set<int> temp;
				set_symmetric_difference(out_old.begin(), out_old.end(), out[i].begin(), out[i].end(), inserter(temp, temp.begin()));
				if (!temp.empty())
					change = true;
			}
		}
	}

	int count = 0;
	cout << "Function: " << funStartLineNumber << endl;
	for (int i = funStartLineNumber; i != funEndLineNumber + 1; ++i)
	{
		codelist[i].print();
		if (!codelist[i].getUse().empty() && !in[i].empty())
		{
			set<string> uselist = codelist[i].getUse();
			for (set<string>::iterator name = uselist.begin(); name != uselist.end(); ++name)
			{
				//cout << "name = " << *name << endl;
				bool isConst = true;
				string value = "";
				for (set<int>::iterator defpos = in[i].begin(); defpos != in[i].end(); ++defpos)
				{
					//cout << "find in line:" << *defpos << endl;
					if (codelist[*defpos].getDef() == *name)
					{
						if (value == "")
						{
							value = codelist[*defpos].getCodesplit()[1];
						}
						else if (value != codelist[*defpos].getCodesplit()[1])
						{
							isConst = false;
						}
					}
					if (!isConst)
						break;
				}
				if (isConst && isnum(value))
				{
					cout << "in line " << i << ":" << *name << " = " << value << endl;
					++count;
				}
			}
		}
	}
	cout << "Number of constants propagated: " << count << endl;
}