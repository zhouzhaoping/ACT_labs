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
	void initCFG(istream &is);
	void genSCR();
	void printCFG();

	void genSCP();
	void reportSCP();
	void runSCP();
};