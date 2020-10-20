#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[1];
};

int
main() {
        key_t key;
        long i=0;
        int mid, n;
           struct msgbuf value;
        key = ftok("/tmp", 'q');
   if ((mid = msgget(key, IPC_CREAT | 0666)) == -1) {
            perror("MS Queue Creation");
            exit(1);
    }

   for(i=1; i<=10; i++) {
            if ((n=msgrcv(mid, &value, sizeof(value), 2, 0)) == -1) {
                     perror("MS Queue Creation");
                 exit(2);
           }
      printf("%s", value.mtext);
   }
//    msgctl(mid, IPC_RMID, (struct msqid_ds *) 0); //NULL
}

