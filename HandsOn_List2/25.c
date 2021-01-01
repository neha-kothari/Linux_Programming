#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h>
#include <time.h>

int main()
{ 
	key_t key = ftok(".", 'a');
	int msgid = msgget(key, 0);
	struct ipc_perm msg_perm;
    struct msqid_ds msq;
    struct msginfo info;
    if(msgctl(msgid, IPC_STAT, &msq)==-1){
        perror("msgctl()");
        exit(0);
    }
            
    printf ("a. The access permissions = 0%3o\n",msq.msg_perm.mode & 0777);
	printf ("b. The USER ID = %d\n",msq.msg_perm.uid);
	printf ("   The GROUP ID = %d\n",msq.msg_perm.gid);
	printf ("c. Time of last message sent = %s\n", ctime(&msq.msg_stime));
	printf ("   Time of last message received = %s\n",ctime(&msq.msg_rtime));
	printf ("d. Time of last change in the message queue = %s\n",ctime(&msq.msg_ctime));
	printf ("e. The msg_qbytes = %lu\n",msq.msg_qbytes);
    printf ("   Current number of bytes in queue = %lu\n",msq.__msg_cbytes);
	printf ("f. Current number of messages in queue = %lu\n",msq.msg_qnum);
	printf ("g. Maximum number of bytes allowed  = %lu\n",msq.msg_qbytes);
	printf ("h. Pid of last message sent = %d\n",msq.msg_lspid);
	printf ("   Pid of last message received = %d\n",msq.msg_lrpid);
} 