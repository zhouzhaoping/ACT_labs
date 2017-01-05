#pragma once
#include <string>
#include <vector>
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

	bool isblockhead, isblocktail;
	string def;
	set<string> use;
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

	void setBlockHead() { isblockhead = true; };
	void setBlockTail() { isblocktail = true; };
	bool isBlockHead() { return isblockhead; };
	bool isBlockTail() { return isblocktail; };
	string getDef() { return def; };
	set<string> getUse() { return use; };
};