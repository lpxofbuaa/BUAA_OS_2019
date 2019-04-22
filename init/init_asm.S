#include<asm/asm.h>
#include<asm/regdef.h>

LEAF(test)
loop:
li	t0, 0x7fffffff
add	t0,t0,t0
	j 	loop
	nop

END(test)
