#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <stdlib.h>
#include <time.h> 

int main() {
    
    struct stat sb;
    if (stat("file_s.txt", &sb) == -1) {
        
        perror("lstat");
        exit(EXIT_FAILURE);
    }

	printf("Inode number: %ld\n", (long)sb.st_ino);
	printf("Number of hard links: %ld\n", (long)sb.st_nlink);
	printf("User ID of owner: %ld\n", (long)sb.st_uid);
	printf("Group ID of owner: %ld\n", (long)sb.st_gid);
	printf("Total size: %lld bytes\n", (long long)sb.st_size);
	printf("Block size for FS I/O: %ld\n", (long)sb.st_blksize);
	printf("Number of 512B blocks allocated: %lld\n", (long long)sb.st_blocks);
	printf("Time of last access: %s", ctime(&sb.st_atime));
	printf("Time of last modification:  %s", ctime(&sb.st_mtime));
	printf("Time of last change: %s", ctime(&sb.st_ctime));
	return 0;
}