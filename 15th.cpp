#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Parent process: pid = %d\n", getpid());


    if (pid < 0) {
        printf("Error: fork() failed.\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child process: pid = %d\n", getpid());
    } else {
        printf("Parent process: child pid = %d\n", pid);
    }

    return 0;
}



    

