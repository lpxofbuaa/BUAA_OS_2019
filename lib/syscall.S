#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>
#include <stackframe.h>
#include <unistd.h>

NESTED(handle_sys,TF_SIZE, sp)
    SAVE_ALL                            // Macro used to save trapframe
    CLI                                 // Clean Interrupt Mask
    nop
    .set at                             // Resume use of $at

    // TODO: Fetch EPC from Trapframe, calculate a proper value and store it back to trapframe.
	lw	v0, TF_EPC(sp)
	addiu	v0, v0, 4
	sw	v0, TF_EPC(sp)

    // TODO: Copy the syscall number into $a0.
	lw	a0, TF_REG4(sp)
	lw	a1, TF_REG5(sp)
    
    addiu   a0, a0, -__SYSCALL_BASE     // a0 <- relative syscall number
    sll     t0, a0, 2                   // t0 <- relative syscall number times 4
    la      t1, sys_call_table          // t1 <- syscall table base
    addu    t1, t1, t0                  // t1 <- table entry of specific syscall
    lw      t2, 0(t1)                   // t2 <- function entry of specific syscall

    lw      t0, TF_REG29(sp)            // t0 <- user's stack pointer

    // TODO: Allocate a space of six arguments on current kernel stack and copy the six arguments to proper location
	lw	a0, TF_REG4(sp)
	lw	a1, TF_REG5(sp)
	lw	a2, TF_REG6(sp)
	lw	a3, TF_REG7(sp)
	move 	s4, t0
	li	s0, 4
	mult	s0, a1
	mflo	s0
	addiu	s0, s0, 4
	addiu	sp, sp, -40

	move	s0, a1
	move	a1, a2
	move	a2, a3
	addiu	s4, s4, 16
	lw	s1, 0(s4)
	move	a3, s1
	li	s2, 16
	addiu	s0, s0, -3  
toask:	
	blez	s0, tonext
	nop
	addiu	s4, s4, 4
	lw	s1, 0(s4)
	addu	s3, sp, s2
	sw	s1, 0(s3)
	addiu	s2, s2, 4
	addiu	s0, s0, -1
  	j 	toask
	nop

tonext:
    jalr    t2                          // Invoke sys_* function
    nop
    
    // TODO: Resume current kernel stack
	addiu	sp, sp, 40
	
    
    sw      v0, TF_REG2(sp)             // Store return value of function sys_* (in $v0) into trapframe

    j       ret_from_exception          // Return from exeception
    nop
END(handle_sys)

sys_call_table:                         // Syscall Table
.align 2
    .word sys_putchar
    .word sys_getenvid
    .word sys_yield
    .word sys_env_destroy
    .word sys_set_pgfault_handler
    .word sys_mem_alloc
    .word sys_mem_map
    .word sys_mem_unmap
    .word sys_env_alloc
    .word sys_set_env_status
    .word sys_set_trapframe
    .word sys_panic
    .word sys_ipc_can_send
    .word sys_ipc_recv
    .word sys_cgetc
