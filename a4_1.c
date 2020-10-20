#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PIPE1234 "/tmp/PIPE1234"

int main() {
        int i = 0, intValue, pubFifo;
        char intStr[PIPE_BUF];
        if(mknod(PIPE1234,S_IFIFO | 0666, 0) == -1){
                perror("Named Pipe Creation Failed!");
                exit(1);
        }

        if((pubFifo = open(PIPE1234, O_WRONLY)) == -1){
                perror(PIPE1234);
                exit(2);
        }

        for(;;){
                i++;
                srand(getpid()+i);
                intValue = (random()*100)/RAND_MAX + 1;
                sprintf(intStr, "%d", intValue);
                write(pubFifo, intStr,PIPE_BUF);
        }
}
