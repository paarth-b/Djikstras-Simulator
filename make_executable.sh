#!/bin/bash

# Loop through folders 01 to 20
for i in {01..20}; do
    folder="test_data/$i"

    # Check if the folder exists
    if [ -d "$folder" ]; then
        # Change directory to the folder
        cd "$folder" || exit

        # Make all files executable
        chmod +x *

        # Print a message indicating the current directory
        echo "Made files in $folder executable."

        # Move back to the parent directory
        cd - || exit
    else
        echo "Folder $folder does not exist."
    fi
done
