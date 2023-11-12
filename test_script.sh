#!/bin/bash

# Loop through directories from 01 to 20
for i in {01..20}; do
    input_file="test_data/$i/Instructions"
    output_file="test_data/$i/Output.txt"
    my_output_file="test_data/$i/myOutput.txt"

    # Run the command
    ./test_data/$i/Execution < "$input_file" > "$my_output_file"

    # Compare output files
    if cmp -s "$output_file" "$my_output_file"; then
        echo "Test $i passed"
    else
        echo "Test $i failed"
    fi
done
