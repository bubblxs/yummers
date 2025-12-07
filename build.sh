#!/bin/bash

set -e

print_usage ()
{
        echo "usage: bash $0 <source.cpp> <optional flag for release build: -r> <optional flag for cleaning debug dir: -c>"
}

if [[ $# -lt 1 ]]; then
        echo "where args, fam?"
        print_usage
        exit -1
fi

if [[ ! -f "$1" ]]; then
        print_usage
        exit -1
fi

IS_RELEASE=1
IS_CLEANING_UP=1
RELEASE_DIR="./release/bin"
DEBUG_DIR="./debug"
SOURCE_FILE="$1"
COMPILED_FILE="$(basename $1 .cpp).node"; shift

for flag in $@; do
        case "$flag" in
                "-r")
                        IS_RELEASE=0
                        ;;
                "-c")
                        IS_CLEANING_UP=0
                        ;;
                *)
                        echo "$0. $flag: flag not found"
                        print_usage
                        exit -1
                        ;;
        esac

        shift
done

[[ ! -d "$DEBUG_DIR" ]] && mkdir "$DEBUG_DIR"

g++ -std=c++20 -I$HOME/.nvm/versions/node/v22.21.1/include/node -fpic -shared "$SOURCE_FILE" -o "$DEBUG_DIR"/"$COMPILED_FILE"

if [[ "$IS_RELEASE" -eq 0 ]]; then
        [[ ! -d "$RELEASE_DIR" ]] && mkdir "$RELEASE_DIR"
        
        cp "$DEBUG_DIR"/"$COMPILED_FILE" "$RELEASE_DIR"

        if [[ "$IS_CLEANING_UP" -eq 0 ]]; then
                rm -fr "$DEBUG_DIR"
        fi
fi