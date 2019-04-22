#include <asm/regdef.h>
#include<asm/cp0regdef.h>
#include<asm/asm.h>
#include<stackframe.h>

NESTED(handle_ov, TF_SIZE, sp)
nop

mfc0 	t0, CP0_STATUS
li	t1, 0xfffffffe
and 	t0,t0,t1
mtc0	t0, CP0_STATUS

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
nop
mfc0	k0, CP0_EPC
lw 	a0, 0(k0)
jal	handle_ov_output
nop

nop
jal 	ov_check
nop


RESTORE_SOME
lw 	k0,TF_EPC(sp)
lw	sp,TF_REG29(sp)
nop
mfc0	t0, CP0_STATUS
li	t1, 1
or 	t0, t0, t1
mtc0	t0, CP0_STATUS
li	t0, 0
li	t1, 0
jr	k0
rfe
nop
END(handle_ov)
 




