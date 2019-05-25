#include "lib.h"
#define ARRAYSIZE 10*1024
int bigarray[ARRAYSIZE] = {0};
void
umain(int argc, char **argv) 
{
	int i;
	writef("mytest begin!\n");
	for (i = 0; i < ARRAYSIZE; ++i) {
		if (bigarray[i] != 0)
			user_panic("bigarray[%d] isnot clear!\n",i);
	}
	for (i = 0; i < ARRAYSIZE; ++i) {
		bigarray[i] = i;
	}
	for (i = 0; i < ARRAYSIZE; ++i) {
		if (bigarray[i] != i)
			user_panic("bigarray[%d] didnot hold its value!\n",i);
	}
	writef("now try doing a wild write off the end\n");
	bigarray[ARRAYSIZE + 1024] = 0;
	user_panic("SHOULD HAVE TRAPPED!!!");
}
