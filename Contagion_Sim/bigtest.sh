#!/bin/bash

for p in $(seq 0.13 0.01 0.99) 
do
   for v in $(seq 0.01 0.01 0.99)
   do
      ./Ext.o <<< "$p
      $v
	  "
      sleep 1
   done
done
