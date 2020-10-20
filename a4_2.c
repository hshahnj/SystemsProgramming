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
    int i=0, pubFifo;
    long j=0;
    key_t key;
    int intValue, mid;
    struct msgbuf value;
    char intStr[PIPE_BUF];
    char intStr2[50];
    key = ftok("/tmp/tmp2", 'q');
    if ((pubFifo=open(PIPE1234, O_RDONLY)) == -1) {
        perror(PIPE1234);
        exit(1);
    }
    if((mid = msgget(key, IPC_CREAT | 0666)) == -1){
        perror("MS QUEUE Creation");
        exit(1);
    }

    for(i=0;i<=10;i++){
        intValue = read(pubFifo, intStr,PIPE_BUF);
        printf("Int Value: %s\n", intValue);
        if(intValue >= 20 && intValue <= 40){
                sprintf(intStr2, "%d/t", intValue);
                if(intValue%2 == 0){
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
        } else {
                i--;
        }
    }
}