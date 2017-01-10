//test multiple function calls
#include <stdio.h>
#define WriteLine() printf("\n");
#define WriteLong(x) printf(" %lld", (long)x);
#define ReadLong(a) if (fscanf(stdin, "%lld", &a) != 1) a = 0;
#define long long long


void dd()
{
				long a;
				long b;
				a = 3 + (-1) + (7 - 6) + (8/9);
				b = a;
}

void hihi(long a, long b)
{
				long c;
				a = 2;
				b = 1;
				if (a == b + 1)
				{
								c = 1;
				}
				else
				{
								c = 2;
				}
				while (c == 2)
				{
								a = a + 1;
				}
				if (a == 2)
				{
								b = 3;
				}

}
void hh()
{
				long a;
				long b;
				a = 1;
				b = 2;
				hihi(a, b);
				WriteLong(a);
}

void main()
{
				dd();
}

/*
 expected output:
 25733 48611 25733
 48611 25733 22878
 25733 22878 2855
 22878 2855 38
 2855 38 5
 38 5 3
 5 3 2
 3 2 1
 2 1 0
 1

 7485671 7480189 5482
 7480189 5482 2741
 5482 2741 0
 2741
*/
