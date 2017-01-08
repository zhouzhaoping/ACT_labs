#include "Code3addr.h"
#include "tools.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Code3addr::Code3addr(string str)
{
	code = str.substr(str.find(":") + 2);
	code = trim(code);
	codesplit = split(code, " ");

	lineNumber = atoi(str.substr(10, str.find(":") - 10).c_str());

	isfunctionhead = codesplit[0] == "enter" ? true : false;
	isfunctiontail = codesplit[0] == "ret" ? true : false;

	isblockhead = isblocktail = false;

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

	def = defValue = "";

	// gen use and def
	// include line temp value, ignore global/array/struct
	if (codesplit[0] == "move")
	{
		if (isVariable(codesplit[1]) || codesplit[1].find("(") != string::npos)
			use.insert(codesplit[1]);
		if (isnum(codesplit[1]))
			defValue = codesplit[1];
		if (isVariable(codesplit[2]))
			def = codesplit[2];
	}
	else
	{
		int preoptFlag = true;
		for (int i = 1; i < codesplit.size(); ++i)
		{
			if (isVariable(codesplit[i]) || codesplit[i].find("(") != string::npos)
			{
				use.insert(codesplit[i]);
			}
			if (preoptFlag && !isnum(codesplit[i]))
				preoptFlag = false;
		}
		if (isArithmeticOperations(codesplit[0]) && preoptFlag)
		{
			
			if (codesplit.size() < 3)
				defValue = int2string(preOpt(codesplit[0], codesplit[1]));
			else
				defValue = int2string(preOpt(codesplit[0], codesplit[1], codesplit[2]));
		}
	}
}

void Code3addr::print()
{
	cout << lineNumber << ":" << code << endl;
	cout << "split:";
	for (vector<string>::iterator str = codesplit.begin(); str != codesplit.end(); ++str)
	{
		cout << "|" << *str;
	}
	cout << "|" << endl;
	//cout << "lineNumber:" << lineNumber << endl;
	if (branch != -1) cout << "branch:" << branch << endl;
	if (call != -1) cout << "call:" << call << endl;
	if (isfunctionhead) cout << "is FunctionHead!" << endl;
	if (isfunctiontail) cout << "is FunctionTail!" << endl;
	if (isblockhead) cout << "is BlockHead!" << endl;
	if (isblocktail) cout << "is BlockTail!" << endl;
	if (def != "") cout << "Def:" << def << endl;
	if (defValue != "") cout << "DefValue:|" << defValue << "|" << endl;
	if (!use.empty())
	{
		cout << "Use:";
		for (set<string>::iterator itr = use.begin(); itr != use.end(); ++itr)
		{
			cout << *itr << " ";
		}
		cout << endl;
	}
}

void Code3addr::update(map<string, string> use2value)
{
	if (codesplit[0] == "move")//or store?
	{
		defValue = codesplit[1] = getValue(codesplit[1], use2value);
	}
	else if (isArithmeticOperations(codesplit[0]))
	{
		string v1 = "-1", v2 = "-1";
		v1 = getValue(codesplit[1], use2value);
		if (codesplit[0] != "neg")
		{
			v2 = getValue(codesplit[2], use2value);
		}
		if (v1 != "" && v2 != "")
			defValue = int2string(preOpt(codesplit[0], v1, v2));
	}
};