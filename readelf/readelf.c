/* This is a simplefied ELF reader.
 * You can contact me if you find any bugs.
 *
 * Luming Wang<wlm199558@126.com>
 */

#include "kerelf.h"
#include <stdio.h>
/* Overview:
 *   Check whether it is a ELF file.
 *
 * Pre-Condition:
 *   binary must longer than 4 byte.
 *
 * Post-Condition:
 *   Return 0 if `binary` isn't an elf. Otherwise
 * return 1.
 */
int is_elf_format(u_char *binary)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
                ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
                ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
                ehdr->e_ident[EI_MAG3] == ELFMAG3) {
                return 1;
        }

        return 0;
}

int check_format(u_char *binary)
{
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
	return ehdr->e_ident[5];
}

/* Overview:
 *   read an elf format binary file. get ELF's information
 *
 * Pre-Condition:
 *   `binary` can't be NULL and `size` is the size of binary.
 *
 * Post-Condition:
 *   Return 0 if success. Otherwise return < 0.
 *   If success, output address of every section in ELF.
 */
int readelf(u_char *binary, int size)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;

        int Nr;
	int format;
	unsigned char *buffer;
	u_int32_t buf;
	u_int32_t t;
	u_int32_t shoff;

        Elf32_Shdr *shdr = NULL;

        u_char *ptr_sh_table = NULL;
        Elf32_Half sh_entry_count;
        Elf32_Half sh_entry_size;


        // check whether `binary` is a ELF file.
        if (size < 4 || !is_elf_format(binary)) {
                printf("not a standard elf format\n");
                return 0;
        }
	format = check_format(binary);

        // get section table addr, section header number and section header size
	if (format == 1) {
		ptr_sh_table = binary + ehdr->e_shoff;
		sh_entry_count = ehdr->e_shnum;
		sh_entry_size = ehdr->e_shentsize;
	} else if (format == 2) {
		shoff = (u_int32_t)*(binary + 33);
		shoff <<8;
		shoff += (u_int32_t)*(binary + 34);
		shoff <<8;
		shoff += (u_int32_t)*(binary + 35);
		shoff <<8;
		shoff += (u_int32_t)*(binary + 36);
		ptr_sh_table = binary + shoff;
		sh_entry_count = (u_int16_t)*(binary + 49);
		sh_entry_count << 8;
		sh_entry_count += (u_int16_t)*(binary + 50);
		sh_entry_size = (u_int16_t)*(binary + 51);
		sh_entry_size <<8;
		sh_entry_size += (u_int16_t)*(binary + 52);	
	}
		
        // for each section header, output section number and section addr.
	for (Nr = 0; Nr < sh_entry_count; Nr++) {
		if (format == 1) 
		{
			shdr = (Elf32_Shdr *)ptr_sh_table;
			printf("%d:0x%x\n", Nr, shdr->sh_addr);
			ptr_sh_table += sh_entry_size;
		} else if (format == 2)
		{
			buffer = (ptr_sh_table + 12);
			buf = (u_int32_t)*buffer;
			buf = buf<<8;
			buf += (u_int32_t)*(buffer+1);
			buf = buf<<8;
			buf += (u_int32_t)(*(buffer+2));
			buf = buf<<8;
			buf += (u_int32_t)(*(buffer+3));
			printf("%d:0x%x\n", Nr,buf);
			
			ptr_sh_table += sh_entry_size;	
		}
	}

        return 0;
}

