#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
	int	fd_p[2], fd_c[2], result;

	size_t	size;
	char	resstring[14];

	if (pipe(fd_p) < 0) {
		printf ("Can\'t open pipe\n");
		exit (-1);
	}

	if (pipe(fd_c) < 0) {
		printf ("Can\'t open pipe\n");
		exit (-1);
	}


	result = fork();

	if (result < 0) {
		printf("Can\'t fork child\n");
		exit(-1);
	} else if (result > 0) {

		/* Parent process */

		close (fd_p[0]);
		close (fd_c[1]);

		size = write (fd_p[1], "Hello, Child!", 14);

		if (size != 14) {
			printf ("Can\'t write all string to pipe\n");
			exit (-1);
		}
		
		size = read (fd_c[0], resstring, 14);
		
		if (size != 14) {
			printf ("Can\'t read string from pipe\n");
			exit (-1);
		}
		
		printf ("Parent exit, resstring: %s\n", resstring);

		close (fd_p[1]);
		close (fd_c[0]);

	} else {

		/* Child process */

		close (fd_c[0]);
		close (fd_p[1]);
		
		
		size = read (fd_p[0], resstring, 14);

		if (size < 0) {
			printf ("Can\'t read string from pipe\n");
			exit (-1);
		}

		printf ("Child exit, resstring: %s\n", resstring);
		
		size = write (fd_c[1], "Hello, Parent", 14);

		if (size < 0) {
			printf ("Can\'t write all string to pipe\n");
			exit (-1);
		}

		close (fd_c[1]);
		close (fd_p[0]);
		
	}

	return 0;
}


