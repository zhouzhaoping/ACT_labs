#include "tools.h"
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
using namespace std;

vector<string> split(string& str, const char* c)
{
	char *cstr, *p;
	vector<string> res;
	cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	p = strtok(cstr, c);
	while (p != NULL)
	{
		res.push_back(p);
		p = strtok(NULL, c);
	}
	return res;
}

string trim(string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}

bool isnum(string s)
{
	if (s == "")
		return false;
	for (int i = 0; i < s.length(); ++i)
	{
		if (i == 0 && s[i] == '-')
			continue;
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

bool isVariable(string name)
{
	if (name.find("#") != string::npos && name.find("_base#") == string::npos && name.find("_offset#") == string::npos)
		return true;
	return false;
}

bool isArithmeticOperations(string optname)
{
	if (optname == "add" || optname == "sub" || optname == "mul" || optname == "div" || optname == "mod" || optname == "neg" || optname == "cmpeq" || optname == "cmple" || optname == "cmplt")
		return true;
	return false;
}

int preOpt(string opt, string val1, string val2)
{
	int v1 = atoi(val1.c_str()), v2 = atoi(val2.c_str());
	if (opt == "add")
		return v1 + v2;
	else if (opt == "sub")
		return v1 - v2;
	else if (opt == "mul")
		return v1 * v2;
	else if (opt == "div")
		return v1 / v2;
	else if (opt == "mod")
		return v1 % v2;
	else if (opt == "neg")
		return -v1;
	else if (opt == "cmpeq")
		return (v1 == v2) ? 1 : 0;
	else if (opt == "cmple")
		return (v1 <= v2) ? 1 : 0;
	else if (opt == "cmplt")
		return (v1 < v2) ? 1 : 0;
	return 0;//
}

string int2string(int value)
{
	ostringstream s1;
	s1 << value;
	return s1.str();
}

string getValue(string &name, map<string, string> &use2value)
{
	if (name[0] == '(' && use2value.find(name) != use2value.end())
	{
		return use2value[name];
	}
	else if (isnum(name))
	{
		return name;
	}
	return "";
}

void toCode3Addr(const string &cmd)
{
	cout << "    instr " << ++lineNumberGlobal << ": " <<  cmd << endl;
}
void toCode3Addr(vector<string> &cmd)
{
	cout << "    instr " << ++lineNumberGlobal << ":";
	for (vector<string>::iterator i = cmd.begin(); i != cmd.end(); ++i)
		cout << " " << *i;
	cout << endl;
}