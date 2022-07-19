#define GL_SILENCE_DEPRECATION
#include "../engine/graphics/window.h"
#include <OpenGL/gl3.h>
#include <stdio.h>

float const vertices[] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
};

char const *vsSource =
    "#version 330 core\n"
    "layout(location = 0) in vec2 position;\n"
    "void main() {\n"
    "   gl_Position = vec4(position, 0.0, 1.0);\n"
    "}";

char const *fsSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(0.0, 1.0, 1.0, 1.0);\n"
    "}";

unsigned createShader(char const *source, int type) {
    unsigned shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, sizeof log, NULL, log);
        printf("%s", log);
        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}

void eventCallback(NbWindow *window, NbEventType type, NbEventData const *data) {
    if (type == NbEventType_KeyDown && data->key.key == 53)
        nbWindowSetClosed(window, true);
}

int main() {
    nbInit();

    NbWindow *window = nbWindowCreate(&(NbWindowDescriptor){.eventHandler = eventCallback});

    unsigned vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof *vertices, (void *)0);

    unsigned program = glCreateProgram();
    glAttachShader(program, createShader(vsSource, GL_VERTEX_SHADER));
    glAttachShader(program, createShader(fsSource, GL_FRAGMENT_SHADER));
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, sizeof log, NULL, log);
        printf("%s", log);
    }

    while (!nbWindowIsClosed(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        nbWindowSwapBuffers(window);
        nbWindowPollEvents();
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    nbWindowDelete(window);
    nbQuit();
}
