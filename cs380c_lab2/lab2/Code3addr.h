#pragma once
#include <string>
#include <vector>
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
};