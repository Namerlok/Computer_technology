#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_STR 255

int main () {
	int     fd;
	size_t  size;
	char    string[SIZE_STR];

	if ((fd = open ("myfile", O_RDWR, 0666)) < 0) {
		printf ("Can\'t open file\n");
		exit (-1);
	}

	size = read (fd, string, SIZE_STR);

	if (size < 0) {
		printf ("Can\'t read file\n");
		exit(-1);
	}

	printf ("string = %s\n", string);

	if (close(fd) < 0) {
		printf("Can\'t close file\n");
	}

	return 0;
}


