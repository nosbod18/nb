out := bin
src := $(wildcard examples/*/*.c)

CFLAGS := -std=c99 -g3 -I. -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter

ifeq ($(shell uname -s), Darwin)
    CFLAGS += -Wno-deprecated-declarations -x objective-c
    LFLAGS := -framework Cocoa -framework OpenGL
else
    CFLAGS += -D_GNU_SOURCE
    LFLAGS := -lX11 -lGL
endif

all: $(src:examples/%.c=$(out)/%)
.PHONY: all

clean:
	rm -r $(out)

$(out)/%: examples/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
