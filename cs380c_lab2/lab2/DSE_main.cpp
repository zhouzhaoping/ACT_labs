#include "CFG.h"
#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, char **argv)
{
	CFG cfg = CFG();
	cfg.initCFG(cin);
	ostringstream hehe;
	cfg.genSCR(hehe);
	cfg.runDSE();
	if (strcmp(argv[1], "rep") == 0) cfg.reportDSE();
	if (strcmp(argv[1], "3addr") == 0) cfg.printCode3Addr();
	if (strcmp(argv[1], "cfg") == 0) cfg.printCFG();
	return 0;
}