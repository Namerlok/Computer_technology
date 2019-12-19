#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 100

//mtype = 1 - for mes from prog1 
//mtype = 2 - for mes from prog2

struct Info{
	int int_info;
	double double_info;
};
typedef struct Info Info;

int main() {
    
	int msqid;
    char pathname[] = "09-3a.c";
    key_t  key;

    struct mymsgbuf{
       	long mtype;
		Info info;
    } mybuf;

    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }

   	/*messaging*/
    
    for (int i = 1; i <= 5; i++){
       
	   /*sending message*/

		mybuf.mtype = 2;
		mybuf.info.int_info = i + 5;
		mybuf.info.double_info = pow(i + 5, 2);
       
		if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(Info), 0) < 0){
			printf("Can\'t send message to queue\n");
        	msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        	exit(-1);
       }
	}

	/*sending the last message*/   
       
    mybuf.mtype = 2;
	mybuf.info.int_info = -1;
	mybuf.info.double_info = -1;
       
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(Info), 0) < 0){
       printf("Can\'t send message to queue\n");
       msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
       exit(-1);
    }

	/*receiving message*/

	while(1){

		if(msgrcv(msqid, (struct msgbuf *) &mybuf, MAX_LEN, 1, 0) < 0){
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}	
		
		if(mybuf.info.int_info == -1 && mybuf.info.double_info == -1){
			exit(-1);
		}

		printf ("message type = %ld, int_info = %d, double_info = %lf\n",
				mybuf.mtype, mybuf.info.int_info, mybuf.info.double_info);
	}

    return 0;    
}
