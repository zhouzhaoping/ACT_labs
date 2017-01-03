#include "CFG.h"
#include "Graph.h"
#include <string>
#include <list>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

vector<string> split(string &str, const char* c);
string trim(string &str);

Code3addr::Code3addr(string str)
{
	code = str.substr(str.find(":") + 2);
	code = trim(code);
	codesplit = split(code, " ");

	lineNumber = atoi(str.substr(10, str.find(":") - 10).c_str());

	isfunctionhead = codesplit[0] == "enter" ? true : false;
	isfunctiontail = codesplit[0] == "ret" ? true : false;

	if (codesplit[0] == "br" || codesplit[0] == "blbc" || codesplit[0] == "blbs")
	{
		string last = *codesplit.rbegin();
		branch = atoi(last.substr(1, last.length() - 2).c_str());
	}
	else if (codesplit[0] == "call")
	{
		string last = *codesplit.rbegin();
		call = atoi(last.substr(1, last.length() - 2).c_str());
	}
	else
		branch = call = -1;
}

void Code3addr::print()
{
	cout << "source:" << code << endl;
	cout << "split:";
	for (vector<string>::iterator str = codesplit.begin(); str != codesplit.end(); ++str)
	{
		cout << "|" << *str;
	}
	cout << endl;
	cout << "lineNumber:" << lineNumber << endl;
	cout << "branch:" << branch << endl;
	cout << "isFunctionHead:" << isfunctionhead << endl;
	cout << "isFunctionTail:" << isfunctiontail << endl;
}

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

vector<vector<int> > Graph::result = vector<vector<int> >();

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

void CFG::initCFG(istream &is)
{
	string buf;
	Function curFunction(-1);
	int curFunctionLineNumeber = -1;

	while (getline(is, buf))
	{
		//cout << "input:" << buf << endl;
		
		Code3addr temp(buf);
		//temp.print();
		if (temp.isFunctionHead())
		{
			curFunctionLineNumeber = temp.getlineNumber();
			curFunction = Function(curFunctionLineNumeber);
		}
		if (curFunctionLineNumeber != -1)
			curFunction.addCode(temp);
		if (temp.isFunctionTail())
		{
			curFunction.setEnd(temp.getlineNumber());
			//curFunction.print();
			curFunction.genCFG();
			functions[curFunctionLineNumeber] = curFunction;
		}
	}
}

void CFG::printCFG()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		it->second.printCFG();
	}
}

void CFG::genSCR()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		it->second.printCFG();
		it->second.genSCR();
	}
}

vector<string> split(string& str, const char* c)
{
	char *cstr, *p;
	vector<string> res;
	cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	p = strtok(cstr, c);
	while (p != NULL)
	{
		res.push_back(p);
		p = strtok(NULL, c);
	}
	return res;
}

string trim(string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}
