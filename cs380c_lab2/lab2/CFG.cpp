#include "CFG.h"
#include "Graph.h"
#include "tools.h"
#include <iostream>
using namespace std;

void CFG::initCFG(istream &is)
{
	string buf;
	Function curFunction(-1);
	int curFunctionLineNumeber = -1;
	bool nextMain = false;

	while (getline(is, buf))
	{
		//cout << "input:" << buf << endl;
		
		Code3addr temp(buf);
		//temp.print();

		if (temp.getCodesplit()[0] == "entrypc")
			nextMain = true;

		if (temp.isFunctionHead())
		{
			curFunctionLineNumeber = temp.getlineNumber();
			curFunction = Function(curFunctionLineNumeber);
			if (nextMain)
			{
				mainFun = curFunctionLineNumeber;
				nextMain = false;
			}
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
		//it->second.print();
		it->second.genSCR();
	}
}

void CFG::reportSCP()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		cout << "Function: " << it->first << endl;
		cout << "Number of constants propagated: " << it->second.getPropagationCount() << endl;
	}
}

void CFG::runSCP()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		cerr << "run scp in func" << it->first << endl;
		it->second.runSCP();
	}
}

void CFG::printCode3Addr()
{
	toCode3Addr("nop");
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		if (it->first == mainFun)
			toCode3Addr("entrypc");
		it->second.printCode3Addr();
		//it->second.genSCR();
	}
	toCode3Addr("nop");
}

void CFG::print()
{
	for (map<int, Function>::iterator it = functions.begin(); it != functions.end(); ++it)
	{
		it->second.print();
	}
}