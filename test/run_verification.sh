#!/bin/bash
for i in {0..99}
do
   input=$(printf "tc/%03d_tc.json" $i)
   python3 verify.py $input
done
