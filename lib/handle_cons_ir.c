#include <printf.h>

void handle_cons_ir(char c, int status) {
	static char buffer[100];
	static int size = 0;
	printf("cp0 status: %x\n",status);
	if (c == '\r') {
		printf("length: %d\n",size);
		buffer[size] = '\0';
		printf("content: %s\n",buffer);
		size = 0;
	} else {
		buffer[size] = c;
		++size;
	}
}
