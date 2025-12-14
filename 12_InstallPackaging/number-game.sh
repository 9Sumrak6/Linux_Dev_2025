#!/bin/bash
# run.sh

export PATH=$PWD/.local/bin:$PATH

if [ -n "$LANGUAGE" ]; then
    number-game "$@"
else
    LANGUAGE=ru_RU.UTF-8 number-game "$@"
fi