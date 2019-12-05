#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main () {
	int		pfd = 0, size = 0, fd[2];
	
	if ((pfd = pipe(fd)) < 0)	{
		printf("ошибка");
		exit(-1);
	}
	
	while (write (fd[1], "C", 1) == 1) {
		size++;
		printf ("\tsize pipe = %5d byte, %2.3f kilobyte\n",
				size, (double)size / 1024);
	}
	
	close (fd[0]);
	close (fd[1]);
	
	return 0;
}

