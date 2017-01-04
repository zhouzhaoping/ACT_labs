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
}

void Code3addr::print()
{
	cout << "source:" << code << endl;
	cout << "split:";
	for (vector<string>::iterator str = codesplit.begin(); str != codesplit.end(); ++str)
	{
		cout << "|" << *str;
	}
	cout << endl;
	cout << "lineNumber:" << lineNumber << endl;
	cout << "branch:" << branch << endl;
	cout << "isFunctionHead:" << isfunctionhead << endl;
	cout << "isFunctionTail:" << isfunctiontail << endl;
}