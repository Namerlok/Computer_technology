#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	printf ("PID = %i, PPID = %i\n", getpid(), getppid());

	return 0;
}
