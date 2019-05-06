#include "lib.h"


void umain()
{
	extern int global_a;
	int a = 0;
	int id = 0;

	if ((id = fork()) == 0) {
		if ((id = tfork()) == 0) {
			global_a += 3;

			for (;;) {
				writef("\t\tthis is child2 :a:%d\n", global_a);
				for (;;) {}
			}
		}

		global_a += 2;

		for (;;) {
			writef("\tthis is child :a:%d\n", global_a);
			for (;;) {
				/*if ((a!=2)&(a!=100)) {
					a = 100;
					break;
				}*/
			}
		}
	}

	global_a++;

	for (;;) {
		writef("this is father: a:%d\n", global_a);
		for (;;) {}
	}
}
