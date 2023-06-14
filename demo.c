#define NB_IMPL
#include "nb.h"

int main(void) {
    nb_error err = NB_ERROR_NONE;

    nb_context ctx = {.title = "Demo", .width = 640, .height = 480};
    if ((err = nb_context_init(&ctx))) goto exit;

    while (!ctx.closed && nb_key_state(&ctx, NB_KEY_ESCAPE) != NB_INPUTSTATE_JUST_PRESSED) {
        nb_screen_fill(&ctx, (nb_color){0});
        nb_context_update(&ctx);
    }

exit:
    nb_context_free(&ctx);
    return err;
}
