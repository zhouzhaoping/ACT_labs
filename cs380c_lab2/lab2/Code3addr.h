#pragma once
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
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
	string defValue;
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
	void setCodesplit(string str, string val)
	{
		for (int i = 1; i < codesplit.size(); ++i)
		{
			if (codesplit[0] == "move" && i == 2)
				continue;
			if (codesplit[i] == str)
				codesplit[i] = val;

		}
		use.erase(use.find(str));
	};

	void setBlockHead() { isblockhead = true; };
	void setBlockTail() { isblocktail = true; };
	bool isBlockHead() { return isblockhead; };
	bool isBlockTail() { return isblocktail; };
	string getDef() { return def; };
	set<string> getUse() { return use; };
	string getDefValue() { return defValue; }
	string setDefValue(string str) { return defValue = str; };

	void update(map<string, string> use2value);
};