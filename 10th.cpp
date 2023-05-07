#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 100

// define a struct for the message queue
struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf buf;

    // generate a key for the message queue
    if ((key = ftok("msgq_example", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    // create the message queue
    if ((msgid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created with id %d\n", msgid);

    // send a message to the queue
    buf.mtype = 1;
    strcpy(buf.mtext, "Hello, world!");
    if (msgsnd(msgid, &buf, sizeof(buf.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Sent message: %s\n", buf.mtext);

    // wait for a message to be received
    sleep(1);
    if (msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received message: %s\n", buf.mtext);

    // delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Message queue deleted\n");

    return 0;
}

