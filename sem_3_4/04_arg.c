#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
 
int main (int argc, char** argv, char** env) {
    
	char** ptr;

	switch (fork()) {
		case -1 :
		fprintf (stderr, "forking error!\n");
		return 1;
	case  0 :
		printf ("Процесс-родитель:\n"
			"\tАргументы командной строки:\n");
		for (ptr = argv; *ptr; ++ptr)
			printf("\t\t%s\n", *ptr);
		printf ("\tПараметры окружающей среды:\n");
		for (ptr = env; *ptr; ++ptr)
			printf ("\t\t%s\n", *ptr);
		printf ("\n");
	default :
		printf ("Процесс-ребенок:\n"
			"\tАргументы командной строки:\n");
		for ( ptr = argv; *ptr; ++ptr )
			printf("\t\t%s\n", *ptr);
		printf("\tПараметры окружающей среды:\n");
		for ( ptr = env; *ptr; ++ptr )
			printf("\t\t%s\n", *ptr);
		printf("\n");
		break;
	}
    
	return 0;
}
