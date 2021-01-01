#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(void) {
    fd_set rfds;
    struct timeval tv;
    int retval;

    /* Watch stdin (fd 0) to see when it has input. */

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    /* Wait up to ten seconds. */

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

    if (retval == -1)
        perror("select()");
    else if (retval) {
		char data[512];
		int i;
		for (i = 0; i < 511; ++i)
		{
			scanf("%c", &data[i]);
			if(data[i] == '\n') break;
		}
		data[i] = '\0';
		printf("Data is available in 10 secs.\n");
		printf("Data: %s\n", data);
	}
    /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within ten seconds.\n");

    return 0;
}


