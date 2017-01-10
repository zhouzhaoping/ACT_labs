#include <stdio.h>
#define WriteLine() printf("\n");
#define WriteLong(x) printf(" %lld", (long)x);
#define ReadLong(a) if (fscanf(stdin, "%lld", &a) != 1) a = 0;
#define long long long



// Global Declarations

//Functions
void function_1()	
{
// Local Variable Declarations
	long a;
	long b;
// Function Body
	(((3 + (-1)) + (7 - 6)) + (8 / 9));
	a = 3;
	b = 3;
}
void function_2(long a, long b)	
{
// Local Variable Declarations
	long c;
// Function Body
	a = 2;
	b = 1;
	if (2 == (1 + 1)) {
	c = 1;
	}
else
	{
	c = 2;
	}
	while (c == 2) {
	a = a + 1;
	}
	if (a == 2) {
	b = 3;
	}
}
void function_3()	
{
// Local Variable Declarations
	long a;
	long b;
// Function Body
	a = 1;
	b = 2;
	function_2(1, 2);
	WriteLong(1);
}
void main()	
{
// Local Variable Declarations
// Function Body
	function_1();
}

