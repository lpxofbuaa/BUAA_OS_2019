

#include "lib.h"




//void halt(void);

static void user_lab5output(void *arg, const char *s, int l)
{
	int i;

	// special termination call
	if ((l == 1) && (s[0] == '\0')) {
		return;
	}

	for (i = 0; i < l; i++) {
		syscall_write_dev(&s[i],0x10000000,1);

		if (s[i] == '\n') {
			syscall_write_dev(&s[i],0x100000000,1);
		}
	}
}

void uwritef(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	user_lp_Print(user_lab5output, 0, fmt, ap);
	va_end(ap);
}

char ugetc() {
	char now = 0;
	while (now == 0) {
		syscall_read_dev(&now,0x10000000,1);
	}
	syscall_write_dev(&now,0x10000000,1);
	return now;
}

