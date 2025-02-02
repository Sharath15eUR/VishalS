#!/bin/bash

# Checking the command-line-inputs
if [[ $# -ne 2 ]]; then
    echo -e "\nERROR : Input and Output file is not given\n"
    exit 1
fi

input_file="$1"
output_file="$2"

# Clear the output file content
> "$output_file"

# Read line by line and extract the particular line alone
while IFS= read -r line; do
    # Extract "frame.time | wlan.fac.type | wlan.fc.subtype" parameters
    if echo "$line" | grep -Eq '"(frame\.time|wlan\.fc\.type|wlan\.fc\.subtype)"\s*:\s*'; then
        # Trim leading and trailing spaces from the line
        trim_line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
        echo "$trim_line" >> "$output_file"
    fi
done < "$input_file"

echo "Successfully extracted and saved at $output_file at $(date)"
