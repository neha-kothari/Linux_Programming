echo "Calling mkfifo to create pipe1"
strace -c mkfifo pipe1
echo "Calling mknod to create pipe2"
strace -c mknod pipe2 p