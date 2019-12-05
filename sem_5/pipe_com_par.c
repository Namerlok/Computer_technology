#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char *envp[]) {
	
	int	fd[2];
	size_t	size;
	
	if (pipe(fd) < 0) {
		printf ("Can\'t open pipe\n");
		exit (-1);
	}
	
	size = write (fd[1], "Hello, Arkadiy", 16);

	(void) execle ("/root/sem_5/pipe_com_ch.exe", 
				   "/root/sem_5/pipe_com_ch.exe",
				   (char)fd[0],
				   (char)fd[1],
				   "03-2_exec.c",
				    NULL, envp);

	return 0;
}
