#pragma once
#include "Code3addr.h"
#include "Graph.h"
#include <map>
#include <set>
#include <vector>

class Function
{
private:
	int funStartLineNumber, funEndLineNumber;
	int lastBlock;
	map<int, Code3addr> codelist;
	set<int> block;
	map<int, vector<int> > edges;
public:
	Function() {};
	Function(int n) { funStartLineNumber = n; };

	void addCode(Code3addr c3a);
	void addEdge(int from, int to);
	void genCFG();
	void genSCR();
	void setEnd(int n) { funEndLineNumber = n; };
	void printCFG();
	void print();
};

