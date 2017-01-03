#include "CFG.h"
#include <iostream>
using namespace std;
int main()
{
	CFG cfg = CFG();
	cfg.initCFG(cin);
	cfg.genSCR();
	return 0;
}