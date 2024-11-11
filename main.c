#include "prompt.h"

#include <conio.h>  // For _getch()
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

int main() {

	char *str;
	do
	{
		str = prompt_get("> "); 
		ft_printf("\n%s\n", str);
	}
	while (str);
 //    char ch[2];
 //    printf("Press any key (press 'q' to quit):\n");
	//
 //    while (1) {
	// 	_read(_fileno(stdin), &ch, 2);
 //        if (ch[0] == '\r') {
 //            printf("Received: \\r (carriage return)\n");
 //        } if (ch[1] == '\n') {
 //            printf("Received: \\n (newline)\n");
 //        }  if (ch[0] == 'q') {
 //            printf("Exiting.\n");
 //            break;
 //        } else {
 //            printf("Received: %s (ASCII code: %d)\n", ch, (unsigned char)ch[0]);
 //        }
 //    }
}
