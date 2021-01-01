#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key = ftok(".", 'a');
	int msgid = msgget(key, 0);
    printf("Removing msgq with msgid: %d\n", msgid);
    if(msgctl(msgid, IPC_RMID, 0)==-1) {
        perror("msgctl()");
        exit(1);
    }
    printf("Removed the message queue succesfully");
}