#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
using namespace std;

class Code3addr
{
private:
	int lineNumber;
	string code;
	vector<string> codesplit;
	bool isfunctionhead;
	bool isfunctiontail;
	int branch, call;
public:
	Code3addr() {};
	Code3addr(string str);
	void print();

	int getlineNumber() { return lineNumber; };
	bool isFunctionHead() { return isfunctionhead; };
	bool isFunctionTail() { return isfunctiontail; };
	int getBranch() { return branch; };
	int getCall() { return call; };
	vector<string> getCodesplit() { return codesplit; };
};

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

class CFG
{
private:
	map<int, Function> functions;
	
public:
	CFG() {};
	void initCFG(istream &is);
	void genSCR();
	void printCFG();
};