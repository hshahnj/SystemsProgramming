#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>

struct msgbuf {
    long mtype;
    char mtext[1];
};


int
main() {
    key_t key;
    long i=0;
    int k = 0;
    int mid, n;
    int flag = 1;
    struct msgbuf value;
    int val;
    key = ftok("/tmp/1", 'q');
    if ((mid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("MS Queue Creation");
        exit(1);
    }
    
    for(i = 1;i<=10;i++) {
/*        n = msgrcv(mid, &value, sizeof(value), 3, 0);
        val = atoi(value.mtext);
        if(n==-1){
            perror("WE IN ERROR");
            exit(2);
        }
        printf("Loop iteration: %d\n", val);
*/
        if ((n=msgrcv(mid, &value, sizeof(value), 1, IPC_NOWAIT)) == -1) {
            perror("MS Queue Creation");
            exit(2);
        }
        val = atoi(value.mtext);
//        printf("Value = %d\n", val);
        flag = 0;
        for(k = 2; k < val; k++){
            if(val%k==0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            printf("Prime: %d\n",val);
        }
    }
//    msgctl(mid, IPC_RMID, (struct msqid_ds *) 0); //NULL
}

