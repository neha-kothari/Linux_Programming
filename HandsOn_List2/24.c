#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>

int main()
{ 
	key_t key = ftok(".", 'a');
	int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0744);
	printf("Key = %d\n", key);
	printf("Msgid = %d\n", msgid);
	
} 