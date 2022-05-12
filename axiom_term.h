/* axiom_term.h - A C/C++ Terminal User Interface utility library - v0.01 - public domain

========================================================================================================================

	YOU MUST

		#define AXIOM_TERM_IMPL

	in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
	include like this:

		#define AXIOM_TERM_IMPL
		#include "axiom_term.h"

	All other files should just #include "axiom_term.h" without the #define

========================================================================================================================

LICENSE
	This software is placed under the public domain. See the end of this file
    for the full license.

CREDITS
	Written by Evan Dobson

TODOS
    - Timeout in term_read()
    - Color
    - More keys

VERSION HISTORY
    0.01  (2022-05-12) Initial version
*/

#ifndef AXIOM_TERM_H
#define AXIOM_TERM_H

#define TERM_KEY_UP    (0xFFFF - 0)
#define TERM_KEY_DOWN  (0xFFFF - 1)
#define TERM_KEY_LEFT  (0xFFFF - 2)
#define TERM_KEY_RIGHT (0xFFFF - 3)

void    term_open        (void);
void    term_close       (void);
int     term_read        (void);
void    term_getxy      (int *x, int *y);
void    term_getwh        (int *w, int *h);
void    term_move        (int x, int y);
void    term_clear       (void);
void    term_printc      (char c);
void    term_prints      (char const *s);
void    term_mvprintc    (int x, int y, char c);
void    term_mvprints    (int x, int y, char const *s);

/***********************************************************************************************************************
************************************************************************************************************************
****                                                                                                               *****
****                                                                                                               *****
****                                                 Implementation                                                *****
****                                                                                                               *****
****                                                                                                               *****
************************************************************************************************************************
***********************************************************************************************************************/

#if defined(AXIOM_TERM_IMPL) || defined(AXIOM_IMPL)
#ifndef AXIOM_TERM_C
#define AXIOM_TERM_C

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static struct {
    struct termios old_termios;
} _term = {0};

void term_open(void) {
    tcgetattr(STDIN_FILENO, &_term.old_termios);
    struct termios raw = _term.old_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\e[?1049h\e[?25l");
}

void term_close(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_term.old_termios);
    printf("\e[?25h\e[?1049l");
}

int term_read(void) {
    int n;
    char c;
    while ((n = read(STDIN_FILENO, &c, 1)) != 1) {
        if (n == -1) {
            return -1;
        }
    }
    if (c == '\x1b') {
        char seq[3];
        // Read 2 characters
        if (read(STDIN_FILENO, &seq[0], 1) != 1 || read(STDIN_FILENO, &seq[1], 1) != 1) {
            return '\x1b';
        }
        if (seq[0] == '[') {
          switch (seq[1]) {
            case 'A': return TERM_KEY_UP;
            case 'B': return TERM_KEY_DOWN;
            case 'C': return TERM_KEY_RIGHT;
            case 'D': return TERM_KEY_LEFT;
          }
        }
        return '\x1b';
    }
    return c;
}

void term_getxy(int *x, int *y) {
    char buf[32];
    printf("\x1b[6n");
    for (int i = 0; i < sizeof(buf) - 1; i++) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1 || buf[i] == 'R') {
            buf[i] = '\0';
            break;
        }
    }
    if (buf[0] == '\x1b' && buf[1] == '[') {
        sscanf(&buf[2], "%d;%d", x, y);
    } else {
        *x = *y = -1;
    }
}

void term_getwh(int *w, int *h) {
    int tw, th;
    term_getxy(&tw, &th);

    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) {
            term_getxy(w, h);
            term_move(tw, th);
        }
    } else {
        *w = ws.ws_col;
        *h = ws.ws_row;
    }
}

void term_move(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void term_clear(void) {
    printf("\033[2J\033[Hm");
}

void term_printc(char c) {
    printf("%c", c);
}

void term_prints(char const *s) {
    printf("%s", s);
}

void term_mvprintc(int x, int y, char c) {
    int tx, ty;
    term_getxy(&tx, &ty);
    term_printc(c);
    term_move(tx, ty);
}

void term_mvprints(int x, int y, char const *s) {
    int tx, ty;
    term_getxy(&tx, &ty);
    term_prints(s);
    term_move(tx, ty);
}

#endif // AXIOM_TERM_C
#endif // AXIOM_TERM_IMPL || AXIOM_IMPL
#endif // AXIOM_TERM_H

/// ## License
/// This is free and unencumbered software released into the public domain.
/// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
/// software, either in source code form or as a compiled binary, for any purpose,
/// commercial or non-commercial, and by any means.
///
/// In jurisdictions that recognize copyright laws, the author or authors of this
/// software dedicate any and all copyright interest in the software to the public
/// domain. We make this dedication for the benefit of the public at large and to
/// the detriment of our heirs and successors. We intend this dedication to be an
/// overt act of relinquishment in perpetermty of all present and future rights to
/// this software under copyright law.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
/// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
/// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// For more information, please refer to <http://unlicense.org/>
