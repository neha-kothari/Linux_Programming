#! /bin/bash

gcc 5.c
./a.out &
PID=$!
echo "PID of the process : $PID"
ls -l /proc/$PID/fd/
echo "Killing process : $PID"
kill -9 $PID
rm file* a.out
echo "Fin."