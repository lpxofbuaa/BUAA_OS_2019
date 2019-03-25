#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>


.text
LEAF(calculator) /*LEAF is defined in asm.h and LEAF functions don't call other functions*/                       
	
	 .set    mips2      /*.set is used to instruct how the assembler works and control the order of instructions */
         .set    reorder

         /* Disable interrupts */
         mtc0    zero, CP0_STATUS

         /* Disable watch exception. */
         mtc0    zero, CP0_WATCHLO
         mtc0    zero, CP0_WATCHHI

         /* disable kernel mode cache */
         mfc0    t0, CP0_CONFIG
         and     t0, ~0x7
         ori     t0, 0x2
         mtc0    t0, CP0_CONFIG
     /*.set is used to instruct how the assembler works and control the order of instructions *

	/* Disable interrupts */
	

	li	s0,0
	li 	s1,0
	li 	s2,0
	li	s3,0
	li	s4,10

	li 	a0,0x90000000
	li 	t1,43
	li	t2,45
	li	t3,10
	li	t4,68
	li	t5,81
	li	t6,2
	li	a1,48

read: 	
	lbu	t0,0(a0)
	beq	t0,zero,read
	nop
	
	sb	t0,0(a0)	
	
	bne 	t0,t1,notadd
	nop
	li 	s2,1
	j	 read
	nop
notadd:
	bne	t0,t2,notsub
	nop
	li	s2,2
	j	 read
	nop
notsub:
	beq	t0,t3,cal
	nop

	bne	t0,t5,notend
	nop
	li 	s3,2
	j	read
	nop
notend:
	beq	t0,t4,putnum
	nop
	sub	t0,t0,a1
	bne	s3,zero,nowisb
	nop
nowisa:
	mult	s4,s0
	mflo	s5
	addu	s0,t0,s5
	j read
	nop
nowisb:
	mult	s4,s1
	mflo	s5
	addu	s1,s5,t0
	j read
	nop
putnum:
	beq	s3,zero,putb
	nop
	li	s3,0
	j read
	nop
putb:
	li 	s3,1
	j read
	nop

cal:	
	beq	s3,t6,end
	nop
	beq	s2,t6,sub
	nop
add:
	addu	s5,s0,s1
	j 	output
	nop
sub:
	subu	s5,s0,s1
	j 	output
	nop

output:
	div	s5,s4
	mfhi	t7
	add	t7,t7,a1
	sb	t7,0(a0)
	mflo	s5
	bne	s5,zero,output
	nop
	li	s0,0
	li	s1,0
	li	s2,0
	li	s3,0
	sb	t3,0(a0)
	j	read
	nop

end:
	sb	zero,16(a0)
	jr	ra

END(calculator)            /*the function defined in asm.h*/
