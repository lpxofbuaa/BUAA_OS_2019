#include <asm/regdef.h>
#include<asm/cp0regdef.h>
#include<asm/asm.h>
#include<stackframe.h>

NESTED(handle_ov, TF_SIZE, sp)
nop

li	t0, 0
sb 	t0, 0xb5000100 

li 	t0, 0
li 	t1, 0
li 	t2, 0
li 	t3, 0
li 	t4, 0
li	t5, 0
li	t6, 0
li	t7, 0
nop
SAVE_ALL
CLI
mfc0	k0, CP0_EPC
lw 	a0, 0(k0)
jal	handle_ov_output
nop

nop
jal 	ov_check
nop

li 	t0, 1
sb	t0, 0xb5000100

RESTORE_SOME
lw 	k0,TF_EPC(sp)
lw	sp,TF_REG29(sp)
nop
jr	k0
rfe
nop
END(handle_ov)
 




