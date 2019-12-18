#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char *envp[]) {

	close ((int)argv[2]);
	char	resstring[16];
	size_t	size;
	
	printf ("hello\n");
	
	size = read ((int)argv[1], resstring, 16);
	
	if (size < 0) {
		printf ("Can\'t read string from pipe\n");
		exit (-1);
	}
	
	printf ("Child exit, resstring: %s\n", resstring);

	close ((int)argv[1]);
	
	return 0;
}
