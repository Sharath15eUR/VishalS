#!/bin/bash

# Ensure exactly three arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <source_directory> <backup_directory> <file_extension>"
    exit 1
fi

# Assign command-line arguments to variables
SOURCE_DIR="$1"
BACKUP_DIR="$2"
FILE_EXT="$3"

# Validate source directory
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory does not exist."
    exit 1
fi

# Create backup directory if it doesn't exist
if [ ! -d "$BACKUP_DIR" ]; then
    mkdir -p "$BACKUP_DIR" || { echo "Error: Failed to create backup directory."; exit 1; }
fi

# Find matching files using globbing and store them in an array
shopt -s nullglob  # Ensure empty glob does not return the pattern itself
files=($SOURCE_DIR/*$FILE_EXT)

# Check if files matching the extension exist
if [ "${#files[@]}" -eq 0 ]; then
    echo "No files with extension '$FILE_EXT' found in $SOURCE_DIR."
    exit 0
fi

# Export a variable to track backed-up file count
export BACKUP_COUNT=0

# Print file details and perform backup
TOTAL_SIZE=0
for file in "${files[@]}"; do
    filename=$(basename "$file")
    filesize=$(stat -c%s "$file")
    TOTAL_SIZE=$((TOTAL_SIZE + filesize))

    echo "Backing up: $filename ($filesize bytes)"
   
    # Check if file already exists in backup directory and compare timestamps
    if [ -e "$BACKUP_DIR/$filename" ]; then
        if [ "$file" -nt "$BACKUP_DIR/$filename" ]; then
            cp "$file" "$BACKUP_DIR/"
            ((BACKUP_COUNT++))
        fi
    else
        cp "$file" "$BACKUP_DIR/"
        ((BACKUP_COUNT++))
    fi

done

# Generate backup summary report
REPORT_FILE="$BACKUP_DIR/backup_report.log"
echo "Backup Summary Report" > "$REPORT_FILE"
echo "----------------------" >> "$REPORT_FILE"
echo "Total files processed: ${#files[@]}" >> "$REPORT_FILE"
echo "Total files backed up: $BACKUP_COUNT" >> "$REPORT_FILE"
echo "Total size backed up: $TOTAL_SIZE bytes" >> "$REPORT_FILE"
echo "Backup location: $BACKUP_DIR" >> "$REPORT_FILE"

echo "Backup completed. Report saved to $REPORT_FILE."
