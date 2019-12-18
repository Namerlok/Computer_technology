#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()	{

	int     fd = 0;
	size_t	size = 0;
	char    name[] = "aaa.fifo";
	
	if ((fd = open(name, O_WRONLY)) < 0) {
		printf ("Can\'t open FIFO for writting\n");
		exit (-1);
	}
	
	size = write (fd, "Hello, Arkadiy!", 16);

	if (size != 16) {
		printf ("Can\'t write all string to FIFO\n");
		exit (-1);
	}
	
	close (fd);
	
	return 0;
}
