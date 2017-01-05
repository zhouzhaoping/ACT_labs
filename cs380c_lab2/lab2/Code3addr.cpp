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

	def = "";
	// gen use and def
	if (codesplit[0] == "move" || codesplit[0] == "store")
	{
		if (codesplit[1].find("#") != string::npos)
		{
			use.insert(split(codesplit[1], "#")[0]);
		}
		if (codesplit[2].find("#") != string::npos)
			def = split(codesplit[2], "#")[0];
	}
	else
	{
		for (int i = 1; i < codesplit.size(); ++i)
		{
			string arg = split(codesplit[i], "#")[0];
			if (codesplit[i].find("#") != string::npos && arg.find("_base") == string::npos)//ignore global
			{
				use.insert(arg);
			}
		}
	}
}

void Code3addr::print()
{
	cout << lineNumber << ":" << code << endl;
	/*cout << "split:";
	for (vector<string>::iterator str = codesplit.begin(); str != codesplit.end(); ++str)
	{
		cout << "|" << *str;
	}
	cout << endl;*/
	//cout << "lineNumber:" << lineNumber << endl;
	if (branch != -1) cout << "branch:" << branch << endl;
	if (call != -1) cout << "call:" << call << endl;
	if (isfunctionhead) cout << "is FunctionHead!" << endl;
	if (isfunctiontail) cout << "is FunctionTail!" << endl;
	if (isblockhead) cout << "is BlockHead!" << endl;
	if (isblocktail) cout << "is BlockTail!" << endl;
	if (def != "") cout << "Def:" << def << endl;
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