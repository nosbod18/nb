# nb
A simple game library focused on prototyping

```c
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
```

# License

Copyright 2023 Evan Dobson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
