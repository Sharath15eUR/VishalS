#!/bin/bash

# Initialize error log file
ERROR_LOG="errors.log"
touch "$ERROR_LOG"

# Function to log errors
log_error() {
    local error_msg="$1"
    echo "[ERROR] $(date '+%Y-%m-%d %H:%M:%S') - $error_msg" | tee -a "$ERROR_LOG" >&2
}

# Function to display help menu
show_help() {
    cat << 'EOH'
File Analyzer - Search for keywords in files
Usage:
    ./file_analyzer.sh -d <directory> -k <keyword>
    ./file_analyzer.sh -f <file> -k <keyword>
    ./file_analyzer.sh --help
Options:
    -d <directory>  Directory to search recursively
    -k <keyword>    Keyword to search for
    -f <file>       Specific file to search in
    --help          Display this help menu
Example:
    ./file_analyzer.sh -d logs -k error
    ./file_analyzer.sh -f script.sh -k TODO
EOH
}

# Recursive function to search files
search_files() {
    local dir="$1"
    local keyword="$2"
    
    # Check if directory exists and is readable
    if [ ! -d "$dir" ] || [ ! -r "$dir" ]; then
        log_error "Cannot access directory: $dir"
        return 1
    fi
    
    # Iterate through directory contents
    for item in "$dir"/*; do
        if [ -d "$item" ]; then
            # Recursively search subdirectories
            search_files "$item" "$keyword"
        elif [ -f "$item" ] && [ -r "$item" ]; then
            # Search for keyword in file
            if grep -q "$keyword" "$item" 2>/dev/null; then
                echo "Found match in: $item"
                echo "Lines containing keyword:"
                grep --color=auto "$keyword" "$item"
                echo "-------------------"
            fi
        fi
    done
}

# Function to validate keyword
validate_keyword() {
    local keyword="$1"
    if [[ ! "$keyword" =~ ^[a-zA-Z0-9_.-]+$ ]]; then
        log_error "Invalid keyword format: $keyword"
        return 1
    fi
    return 0
}

# Function to search in a single file
search_file() {
    local file="$1"
    local keyword="$2"
    
    if [ ! -f "$file" ] || [ ! -r "$file" ]; then
        log_error "Cannot access file: $file"
        return 1
    fi
    
    if grep -q "$keyword" "$file" 2>/dev/null; then
        echo "Found match in: $file"
        echo "Lines containing keyword:"
        grep --color=auto "$keyword" "$file"
        echo "-------------------"
    else
        echo "No matches found in: $file"
    fi
}

# Main script
if [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

# Initialize variables
directory=""
keyword=""
file=""

# Parse command line arguments
while getopts ":d:k:f:" opt; do
    case $opt in
        d) directory="$OPTARG" ;;
        k) keyword="$OPTARG" ;;
        f) file="$OPTARG" ;;
        \?) log_error "Invalid option: -$OPTARG"; exit 1 ;;
        :) log_error "Option -$OPTARG requires an argument"; exit 1 ;;
    esac
done

# Validate inputs
if [ -z "$keyword" ]; then
    log_error "Keyword is required"
    show_help
    exit 1
fi

# Validate keyword format
if ! validate_keyword "$keyword"; then
    exit 1
fi

# Execute search based on input
if [ -n "$directory" ]; then
    search_files "$directory" "$keyword"
elif [ -n "$file" ]; then
    search_file "$file" "$keyword"
else
    log_error "Either -d or -f option is required"
    show_help
    exit 1
fi

exit $?
