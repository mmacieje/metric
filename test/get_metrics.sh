#!/bin/bash
for i in {0..99}
do
   input=$(printf "tc/%03d_tc.json" $i)
   output=$(printf "tc/%03d_metric.json" $i)
   curl -X POST -H "Content-Type: application/json" -d @$input http://127.0.0.1:9000 | tee $output
done
