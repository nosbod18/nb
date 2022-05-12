#define AXIOM_TERM_IMPL
#include "axiom_term.h"

int main(void) {
    term_open();
    term_clear();
    term_mvprints(5, 5, "Hello World!");
    term_read();
    term_close();
}
