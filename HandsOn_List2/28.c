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
	struct msqid_ds msq;

	if(msgctl(msgid, IPC_STAT, &msq) == -1) {
        perror("msgctl()");
        exit(1);
    }
	printf ("The access permissions before modification = 0%o\n",msq.msg_perm.mode);
	
	msq.msg_perm.mode = 0777;
	if(msgctl(msgid, IPC_SET, &msq) == -1){
        perror("msgctl()");
        exit(0);
    }

	printf ("The access permissions after modification = 0%o\n",msq.msg_perm.mode);
	
	exit(0); 
	
	
}