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
	set<int> scrblock;
	map<int, vector<int> > edges;	// edges of blocks
	map<int, vector<int> > edges_jump_from;// blockhead -> jumpfrompos
	map<int, vector<int> > edges_jump_to;// blocktail -> jumptopos

	map<string, set<int> > variable_defpos;		// positions of varias def
	map<int, set<int> > in, out;
	int propagationCount;

	map<int, set<string> > in_string, out_string;
	int dseInSCR, dseOutSCR;
public:
	Function() {};
	Function(int n) { funStartLineNumber = n; };

	void addCode(Code3addr c3a);
	void addEdge(int from, int to);
	void removeEdge(int from, int to);
	void releaseUnreachable(int to);

	void genCFG();
	void genSCR(ostream &os);
	void setEnd(int n) { funEndLineNumber = n; };
	void printCFG();
	void print();

	void runSCP();
	void makeInOut_SCP();
	bool defValueChange_SCP(vector<int> &branchChange);
	void preBranch_SCP(vector<int> &branchChange);
	int getPropagationCount() { return propagationCount; }

	void runDSE();
	void makeInOut_DSE();
	bool deadStatementChange_DSE();
	int getDseInSCR() { return dseInSCR; }
	int getDseOutSCR() { return dseOutSCR; }

	void printCode3Addr();
};

