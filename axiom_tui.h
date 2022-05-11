#ifndef AXIOM_TUI_H
#define AXIOM_TUI_H

#include <stdint.h>

#define AXT_NONE       0x00
#define AXT_BOLD       0x01
#define AXT_FAINT      0x02
#define AXT_ITALIC     0x04
#define AXT_UNDERLINE  0x08
#define AXT_BLINK      0x10
#define AXT_INVERSE    0x20
#define AXT_INVISIBLE  0x40
#define AXT_STRIKE     0x80

#define AXT_SEQ_MAX    32

#define AXT_UTF8_REPLACEMENT_CHAR "\xEF\xBF\xBD" // �

typedef struct axt_sgr {
    uint64_t at : 16;
    uint64_t fg : 24;
    uint64_t bg : 24;
} axt_sgr;

typedef struct axt_seq {
    char        data[AXT_SEQ_MAX];
    uint32_t    len;
    int32_t     x;
    int32_t     y;
    uint32_t    ch;
    uint16_t    key;
    uint8_t     mod;
    uint8_t     type;
} axt_seq;

typedef struct axt_stream {
	char buf[1024];
	struct termios tc;
    int  len;
	int  cap;
	int  fd;
} axt_stream;


int     axt_open      (void);
void    axt_close     (void);
int     axt_read      (axt_stream const *s, axt_seq *seq);
void    axt_move      (int x, int y);
void    axt_clear     (char const *color, char c);
void    axt_fill      (int x, int y, int w, int h, char const *color, char c);
void    axt_printc    (char c);
void    axt_prints    (char const *s);
void    axt_mvprintc  (int x, int y, char c);
void    axt_mvprints  (int x, int y, char const *s);
void    axt_mvcprintc (int x, int y, char const *color, char c);
void    axt_mvcprints (int x, int y, char const *color, char const *s);
void    axt_flush     (void);

int     axt_utf8_seq_len(char ch);
int     axt_utf8_seq_to_codepoint(uint32_t *codepoint, const char *seq, size_t len);
int     axt_utf8_codepoint_to_seq(char *seq, uint32_t codepoint);

/******************************************************************************
*                                                                             *
*                                Implementation                               *
*                                                                             *
******************************************************************************/

// #ifdef AXT_IMPL
#ifndef AXIOM_AXT_C
#define AXIOM_AXT_C

#include <sys/ioctl.h>
#include <locale.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

static char const *old_locale = NULL;
static struct termios old_termios = {0};

int axt_open(void) {
    old_locale = setlocale(LC_ALL, NULL);
    tcgetattr(STDIN_FILENO, &old_termios);

    if (setlocale(LC_ALL, "en_US.UTF-8") == NULL) {
        axt_close();
        return 0;
    }

    return 1;
}

void axt_close(void) {
    setlocale(LC_ALL, old_locale);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
}

int axt_read(axt_stream const *s, axt_seq *seq) {
}

void axt_move(int x, int y) {
}

void axt_clear(char const *color, char c) {
}

void axt_fill(int x, int y, int w, int h, char const *color, char c) {
    for (int yy = y; yy < y + h; yy++) {
        for (int xx = x; xx < x + w; xx++) {
            axt_mvcprintc(xx, yy, color, c);
        }
    }
}

void axt_printc(char c) {
}

void axt_prints(char const *s) {
}

void axt_mvprintc(int x, int y, char c) {
}

void axt_mvprints(int x, int y, char const *s) {
}

void axt_mvcprintc(int x, int y, char const *color, char c) {
}

void axt_mvcprints(int x, int y, char const *color, char const *s) {
}

void axt_flush(void) {
}



#endif // AXIOM_AXT_C
// #endif // AXT_IMPL
#endif // AXIOM_AXT_H
