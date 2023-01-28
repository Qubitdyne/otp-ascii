#!/bin/bash

for i in $(seq 0 $(($(nproc)-1))); do
    (taskset --cpu-list $i quantumd &)
done
