// Ping-pong a counter between two processes.
// Only need to start one of these -- splits into two with fork.

#include "lib.h"

void
umain(void)
{
	int i = 0;
	int j = 0;
	int whom,perm;
	while (i < 10) {
		i = ipc_recv(&whom,0,&perm);
		writef("b recv num %d\n",i);
		if (i == 10)
			break;
		i++;
		writef("b send num %d\n",i);
		ipc_send(2048,i,0,0);

	}
	
/*	u_int who, i;

	if ((who = fork()) != 0) {
		// get the ball rolling
		writef("\n@@@@@send 0 from %x to %x\n", syscall_getenvid(), who);
		ipc_send(who, 0, 0, 0);
		//user_panic("&&&&&&&&&&&&&&&&&&&&&&&&m");
	}

	for (;;) {
		writef("%x am waiting.....\n", syscall_getenvid());
		i = ipc_recv(&who, 0, 0);

		writef("%x got %d from %x\n", syscall_getenvid(), i, who);

		//user_panic("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
		if (i == 10) {
			return;
		}

		i++;
		writef("\n@@@@@send %d from %x to %x\n",i, syscall_getenvid(), who);
		ipc_send(who, i, 0, 0);

		if (i == 10) {
			return;
		}
	}*/

}

