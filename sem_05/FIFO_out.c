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
	char    resstring[16];
	
	if ((fd = open(name, O_RDONLY)) < 0) {
		printf ("Can\'t open FIFO for reading\n");
		exit (-1);
	}
	
	size = read (fd, resstring, 16);
	
	if (size < 0) {
		printf ("Can\'t read string from FIFO\n");
		exit (-1);
	}
	
	printf ("resstring: %s\n", resstring);

	close (fd);

	return 0;
}
