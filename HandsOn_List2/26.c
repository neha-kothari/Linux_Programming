#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	int msgid;
	size_t size;
	key_t key;
	struct msg
	{
		long mtype;
		char message[80];
	}mq;
	key = ftok(".", 'a');
	msgid = msgget(key, 0644 | IPC_CREAT);
	printf("Enter the message type: ");
	scanf("%ld", &mq.mtype);
	printf("Enter the message: ");
	scanf(" %[^\n]", mq.message);
	size = strlen(mq.message);

	msgsnd(msgid, &mq, size + 1, 0);
	printf("Data sent successfully to message queue.\n"); 
	printf("msgid: %d, message type: %ld and size: %lu.\nmessage: %s\n", msgid, mq.mtype, size, mq.message);
}