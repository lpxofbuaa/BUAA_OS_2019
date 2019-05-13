#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>
#include <kclock.h>
#include <kcons.h>

LEAF(set_cons)

	li t0, 0x1401
	mfc0 t1, CP0_STATUS
	or	t1, t0, t1
	mtc0	t1, CP0_STATUS

	jr ra
	nop

END(set_cons)
