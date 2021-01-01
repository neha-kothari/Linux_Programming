int main () {
    int i,fd;
    struct{
        int ticket_no;
    } db;
    int fd = open("record.txt", O_RDWR);
    write(fd, db, sizeof(db));
    close(fd);
    
}