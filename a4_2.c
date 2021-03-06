#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define PIPE1234 "/tmp/PIPE1234"

struct msgbuf{
    long mtype;
    char mtext[1];
};

int
main() {
    int i=0, pubFifo, val;
    int count = 0;
    key_t key;
    int intValue, mid;
    struct msgbuf value;
    char intStr[PIPE_BUF];
    char intStr2[PIPE_BUF];
    key = ftok("/tmp/1", 'q');
    if ((pubFifo=open(PIPE1234, O_RDONLY)) == -1) {
        perror(PIPE1234);
        exit(1);
    }
    if((mid = msgget(key, IPC_CREAT | 0666)) == -1){
        perror("MS QUEUE Creation");
        exit(1);
    }

    while(count != 10){
        read(pubFifo, intStr, PIPE_BUF);
        val = atoi(intStr);
        if(val >= 20 && val <= 40){
            count++;
            sprintf(intStr2, "%d\t", val);
            if((val%2) == 0){
                value.mtype=2;
            }
            else {
                value.mtype=1;
            }
            strcpy(value.mtext,intStr2);
            if(msgsnd(mid,&value, sizeof(value),0) == -1){
                perror("Message send error!");
                exit(2);
            }
        } 
    }
}
