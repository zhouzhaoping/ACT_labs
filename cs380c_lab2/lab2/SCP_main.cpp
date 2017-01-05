#include "CFG.h"
#include <iostream>
using namespace std;
int main()
{
	CFG cfg = CFG();
	cfg.initCFG(cin);
	cfg.genSCR();
	//cfg.genSCP();
	//cfg.reportSCP();
	//cfg.runSCP();
	return 0;
}