#pragma once
#include "Function.h"
#include <sstream>
#include <map>
using namespace std;

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