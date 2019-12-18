#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
	int	fd[2];
	ssize_t	size;
	char	string[] = "Hello, Arkadiy!";
	char	resstring[16];

	if (pipe(fd) < 0) {
		printf ("Can\'t open pipe\n");
		exit (-1);
	}

	size = write (fd[1], string, 16);

	if (size != 16) {
		printf ("Can\'t write all string to pipe\n");
		exit (-1);
	}

	size = read (fd[0], resstring, 16);

	if (size < 0) {
		printf ("Can\'t read string from pipe\n");
		exit (-1);
	}

	printf ("%s\n", resstring);

	close (fd[0]);
	close (fd[1]);

	return 0;
}

