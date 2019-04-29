#include "lib.h"


void umain()
{
	
	writef("begin1!\n");
	syscall_mem_alloc(2048,0x6000000,PTE_V);
	writef("end!");
	/*int a = 0;
	int id = 0;

	if ((id = fork()) == 0) {
		if ((id = fork()) == 0) {
			a += 3;

			for (;;) {
				writef("\t\tthis is child2 :a:%d\n", a);
			}
		}

		a += 2;

		for (;;) {
			writef("\tthis is child :a:%d\n", a);
		}
	}

	a++;

	for (;;) {
		writef("this is father: a:%d\n", a);
	}*/
}
