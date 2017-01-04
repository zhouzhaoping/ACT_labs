#include "CFG.h"
#include "Graph.h"
using namespace std;

void CFG::initCFG(istream &is)
{
	string buf;
	Function curFunction(-1);
	int curFunctionLineNumeber = -1;

	while (getline(is, buf))
	{
		//cout << "input:" << buf << endl;
		
		Code3addr temp(buf);
		//temp.print();
		if (temp.isFunctionHead())
		{
			curFunctionLineNumeber = temp.getlineNumber();
			curFunction = Function(curFunctionLineNumeber);
		}
		if (curFunctionLineNumeber != -1)
			curFunction.addCode(temp);
		if (temp.isFunctionTail())
		{
			curFunction.setEnd(temp.getlineNumber());
			//curFunction.print();
			curFunction.genCFG();
			functions[curFunctionLineNumeber] = curFunction;
		}
	}
}

void CFG::printCFG()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		it->second.printCFG();
	}
}

void CFG::genSCR()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		it->second.printCFG();
		it->second.genSCR();
	}
}
