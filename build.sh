#!/bin/bash

EFILES="engine/core/*.c"
SFILES="sandbox/main.c"

CFLAGS="-std=c99 -Wall -Wextra -Werror"
LFLAGS=""

if [[ "$(uname -s)" == Darwin ]]; then
    EFILES="$EFILES engine/graphics/window.cocoa.m"
    CFLAGS="$CFLAGS -x objective-c"
    LFLAGS="$LFLAGS -framework Cocoa -framework OpenGL"
fi

gcc $CFLAGS $EFILES $SFILES -o game $LFLAGS
