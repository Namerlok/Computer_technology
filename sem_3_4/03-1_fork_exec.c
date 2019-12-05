/* Программа 03-1.с – пример создания нового процесса
с одинаковой работой процессов ребенка и родителя */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv, char **envp) {
	pid_t pid_f, pid, ppid;

	int a = 0;
	pid_f = fork();
	/* При успешном создании нового процесса с этого
	места псевдопараллельно начинают работать два
	процесса: старый и новый */

	/* Перед выполнением следующего выражения значение
	переменной a в обоих процессах равно 0 */
	a = a + 1;

	if (pid_f == -1) {
		printf ("ERROR\n");
	} else if (pid_f == 0) {
		(void) execle ("/bin/cat", "bin/cat", "03-1_fork_exec.c", NULL, envp);
		fprintf(stderr, "Eroor on program start\n");
		exit(-1);
	} else {
		printf ("Родитель: 5 + 4 = %i\n", 5 + 4);
	}

	/* Узнаем идентификаторы текущего и родительского
	процесса (в каждом из процессов !!!) */
	pid = getpid();
	ppid = getppid();

	/* Печатаем значения PID, PPID и вычисленное
	значение переменной a (в каждом из процессов !!!) */
	printf("My pid = %d, my ppid = %d, result = %d\n",
		(int)pid, (int)ppid, a);

	return 0;
}
