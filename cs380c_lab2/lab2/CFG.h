#pragma once
#include "Function.h"
#include <sstream>
#include <map>
using namespace std;

class CFG
{
private:
	int mainFun;
	map<int, Function> functions;
	
public:
	CFG() {};
	void print();
	void initCFG(istream &is);
	void genSCR(ostream &os);
	void printCFG();

	void reportSCP();
	void runSCP();


	void runDSE();
	void reportDSE();

	void printCode3Addr();
};