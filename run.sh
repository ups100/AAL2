#!/bin/sh

cities=2000
max=12800

while [ $cities -le $max ]
do
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
./aal $cities -s
cities=`expr $cities + 200`
done
