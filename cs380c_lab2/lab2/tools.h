#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

vector<string> split(string& str, const char* c);

string trim(string& str);

bool isnum(string s);

bool isVariable(string name);

bool isArithmeticOperations(string optname);
bool isBranchClearedOrSet(string optname);

int preOpt(string opt, string val1, string val2 = "-1");

string int2string(int value);

string getValue(string &name, map<string, string> &use2value);

static int lineNumberGlobal = 0;
void toCode3Addr(const string &cmd);
void toCode3Addr(vector<string> &cmd);

