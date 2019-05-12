#include "lib.h"
#include <mmu.h>
#include <env.h>

void
exit(void)
{
	//close_all();
	syscall_env_destroy(0);
}


struct Env *env;
int global_a;

void
libmain(int argc, char **argv)
{
	// set env to point at our env structure in envs[].
	env = 0;	// Your code here.
	//writef("xxxxxxxxx %x  %x  xxxxxxxxx\n",argc,(int)argv);
	//global_a = 0;
	int envid;
	envid = syscall_getenvid();
	envid = ENVX(envid);
	env = &envs[envid];
	// call user main routine
	umain(argc, argv);
	// exit gracefully
	exit();
	//syscall_env_destroy(0);
}
