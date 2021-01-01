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
	msgid = msgget(key, 0);
	printf("Enter the message type: ");
	scanf("%ld", &mq.mtype);

	msgrcv(msgid, &mq, sizeof(mq.message), mq.mtype, 0);
	printf(" Message type: %ld\n", mq.mtype); 
	printf(" Message text: %s\n", mq.message);
}