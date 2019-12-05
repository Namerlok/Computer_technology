#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

long int ReadNovelToBuf (char** buf,
					   	 const char* filename,
						 const char* mode) {

	assert (buf != NULL);
	assert (filename != NULL);
	assert (mode != NULL);

	FILE* in = fopen (filename, mode);
	if (in == NULL)
		perror ("Открытие входного файла\n");

	fseek (in, 0, SEEK_END);
	long int size_f = ftell (in);
	fseek (in, 0, SEEK_SET);

	*buf = calloc (size_f / sizeof(**buf) + 2, sizeof(**buf));
	long int readcount = fread (*buf , sizeof(**buf), size_f / sizeof(**buf), in);
	(*buf)[size_f / sizeof(**buf)] = '\n';
	(*buf)[size_f / sizeof(**buf) + 1] = '\0';

	fclose (in);

	if (readcount != size_f)
		fprintf (stderr, "The number of bytes read differs from the specified\n");

	return readcount;
}

int main() {
	char    *array;
	int     shmid;
	int     new = 1;
	char    pathname[] = "task2-a.c";
	char	*buf = NULL;
	key_t   key;
	
	int size = ReadNovelToBuf (&buf, pathname, "rb");

	if((key = ftok(pathname,0)) < 0) {
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, size, 0666|IPC_CREAT|IPC_EXCL)) < 0) {
		if(errno != EEXIST){
			printf("Can\'t create shared memory\n");
			exit(-1);
		} else {
			if((shmid = shmget(key, size, 0)) < 0){
				printf("Can\'t find shared memory\n");
				exit(-1);
			}
			new = 0;
		}
	}
	
	if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	
	if(new){
		memcpy (array, buf, size);
	}
	
	
	if(shmdt(array) < 0) {
		printf("Can't detach shared memory\n");
		exit(-1);
	}
	
	free (buf); buf = NULL;

	return 0;
}

