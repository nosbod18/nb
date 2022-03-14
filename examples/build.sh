#!/bin/bash
set -e

# Setup
CFLAGS="-std=c99 -Wall -Wextra -Wpedantic -Werror -g -DDEBUG"

if [ "$(uname -s)" == "Linux" ]; then
        LFLAGS="-lxcb"
fi

# Compile
pushd $(dirname $0) 2>&1 > /dev/null
mkdir -p bin
for f in $(ls *.c); do
        cmd="gcc $CFLAGS $f -o bin/$(basename $f .c) $LFLAGS"
        echo $cmd
        $cmd
done
popd 2>&1 > /dev/null
