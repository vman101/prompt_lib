#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "prompt.h"

int main()
{
	char buffer[20];
	terminal_raw_mode_enable_internal();
	atexit(terminal_raw_mode_disable_internal);
    while (1) {
		memset(buffer, 0, sizeof(buffer));
		_read(_fileno(stdin), buffer, sizeof(buffer));
        if (buffer[0] == '\r') {
            printf("Received: \\r (carriage return)\n");
        }
		if (buffer[1] == '\n') {
            printf("Received: \\n (newline)\n");
        }
		if (buffer[0] == 'q') {
            printf("Exiting.\n");
            break;
        } else {
            printf("Received: %s (ASCII code: %d)\n", buffer, (unsigned char)buffer[0]);
        }
	}
	terminal_raw_mode_disable_internal();
}
