#! /bin/bash

gcc 2.c
./a.out &
PID=$!
echo "PID of the process $PID"
echo "The process related information in /proc/$PID :"
ls /proc/$PID