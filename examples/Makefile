out := bin
src := $(wildcard */*.c)

CFLAGS := -std=c99 -g3 -I.. -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter

ifeq ($(shell uname -s), Darwin)
    CFLAGS += -x objective-c -Wno-deprecated-declarations
    LFLAGS := -framework Cocoa -framework OpenGL
else
    CFLAGS += -D_GNU_SOURCE
    LFLAGS := -lX11 -lGL
endif

all: $(src:%.c=$(out)/%)
.PHONY: all

clean:
	rm -r $(out)

$(out)/%: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)