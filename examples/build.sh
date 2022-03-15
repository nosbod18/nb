#!/bin/bash
set -e

# Setup
CFLAGS="-std=c99 -Wall -Wextra -Wpedantic -Werror -g -DDEBUG"

if [ "$(uname -s)" == "Linux" ]; then
        CFLAGS="$CFLAGS -D_GNU_SOURCE"
        LFLAGS="-lxcb"
elif [ "$(uname -s)" == "Darwin" ]; then
        CFLAGS="$CFLAGS -x objective-c"
        LFLAGS="-framework Cocoa"
fi

# Compile
pushd $(dirname $0) 2>&1 > /dev/null

mkdir -p bin
FILES=${1:-$(ls *.c)}

for f in $FILES; do
        cmd="gcc $CFLAGS $f -o bin/$(basename $f .c) $LFLAGS"
        echo $cmd
        $cmd
done

popd 2>&1 > /dev/null
