#include <stdio.h>
#define WriteLine() printf("\n");
#define WriteLong(x) printf(" %lld", (long)x);
#define ReadLong(a) if (fscanf(stdin, "%lld", &a) != 1) a = 0;
#define long long long


long global_array[24];
	
struct Point {
    long x;
    long y;
} p;

void init_globals() {
    long i;

    i = 0;
    while(i < 24) {
        global_array[i] = i;
        i = i + 1;
    }

    p.x = 13;
    p.y = 7;
}

void simple_function(long a, long b) {
    long local_array[3];

    local_array[0] = a;
    local_array[1] = b;
    local_array[2] = a + b;

    if (global_array[2] > a) {
        global_array[3] = b + p.y;
    }
    p.x = local_array[a % 3];
}


void main()
{
	long a, b, i;

	init_globals();
	a = 25733;
	b = 48611;
	simple_function(a, b);


	i = 0;
	while(i < 24) {
	    WriteLong(global_array[i]);
	    i = i + 1;
	}

	WriteLine();
	WriteLong(p.x);
	WriteLong(p.y);
}
