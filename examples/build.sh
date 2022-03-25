#!/bin/bash
set -e

CFLAGS="-std=c99 -Wall -Wextra -Wpedantic -Werror -g -I.."

if [ "$(uname -s)" == "Linux" ]; then
        CFLAGS="$CFLAGS -D_GNU_SOURCE"
        LFLAGS="-lxcb"
elif [ "$(uname -s)" == "Darwin" ]; then
        CFLAGS="$CFLAGS -x objective-c"
        LFLAGS="-framework Cocoa"
fi

pushd $(dirname $0) 2>&1 > /dev/null

mkdir -p bin
FILES=${1:-$(ls tiny_{app,ds,gfx,math}/*.c)}

for f in $FILES; do
        cmd="gcc $CFLAGS $f -o bin/$(basename $f .c) $LFLAGS"
        echo $cmd
        $cmd
done

popd 2>&1 > /dev/null
