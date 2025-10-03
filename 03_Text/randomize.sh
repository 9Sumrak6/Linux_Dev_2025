#!/bin/bash

delay=${1:-0.1}

mapfile -t lines

rows=${#lines[@]}

tput clear

all_positions=""
for ((i=0; i<rows; i++)); do
    line="${lines[i]}"
    for ((j=0; j<${#line}; j++)); do
        char="${line:$j:1}"

        encoded_char=$(printf "%s" "$char" | od -v -An -tx1 | tr -d ' \n')
        all_positions+="$i $j $encoded_char"$'\n'
    done
done

echo "$all_positions" | shuf | while IFS= read -r record; do
    if [ -n "$record" ]; then
        row=$(echo "$record" | cut -d' ' -f1)
        col=$(echo "$record" | cut -d' ' -f2)
        encoded_char=$(echo "$record" | cut -d' ' -f3-)
        
        char=$(echo "$encoded_char" | sed 's/\([0-9a-f]\{2\}\)/\\x\1/g' | xargs -0 printf "%b" 2>/dev/null || echo " ")
        
        tput cup $row $col
        printf "%s" "$char"
        sleep $delay
    fi
done

tput cup $rows 0