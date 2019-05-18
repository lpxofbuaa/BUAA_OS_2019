/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = offset_begin;
	char tmp = 0;
	u_int result;

	while (offset < offset_end) {
		if (syscall_write_dev(&diskno,0x13000010,4))
			user_panic("panic at ide_read^^^can not set diskno");
		if (syscall_write_dev(&offset,0x13000000,4))
			user_panic("panic at ide_read^^^can not set offset");
		tmp = 0;
		if (syscall_write_dev(&tmp,0x13000020,1))
			user_panic("panic at ide_read^^^can not set begin");
		if (syscall_read_dev(&result,0x13000030,4))
			user_panic("panic at ide_read^^^can not get result");
		if (result == 0)
			user_panic("panic at ide_read^^^read fail");
		if (syscall_read_dev(dst + offset - offset_begin,0x13004000,0x200))
			user_panic("panic at ide_read^^^copy buff fail");
		offset += 0x200;
            // Your code here
            // error occurred, then panic.
	}
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
        // Your code here
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = offset_begin;
	char tmp = 0;
	u_int result;
	writef("diskno: %d\n", diskno);
	while (offset < offset_end) {
	    // copy data from source array to disk buffer.
		if (syscall_write_dev(src + offset - offset_begin,0x13004000,0x200))
			user_panic("panic at ide_write^^^copy to buff fail");
		if (syscall_write_dev(&diskno,0x13000010,4))
			user_panic("panic at ide_write^^^can not set diskno");
		if (syscall_write_dev(&offset,0x13000000,4))
			user_panic("panic at ide_write^^^can not set offset");
		tmp = 1;
		if (syscall_write_dev(&tmp,0x13000020,1))
			user_panic("panic at ide_write^^^can not set begin");
		if (syscall_read_dev(&result,0x13000030,4))
			user_panic("panic at ide_write^^^can not get result");
		if (result == 0)
			user_panic("panic at ide_write^^^read fail");
		offset += 0x200;
            // if error occur, then panic.
	}
}

