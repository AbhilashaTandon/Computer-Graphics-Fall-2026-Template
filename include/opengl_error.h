#pragma once
#include "gl_lib.h"
#include <iostream>
#include <signal.h>

// evil usage of preprocessor
#define ASSERT(x)                                                              \
        if (!(x)) {                                                            \
                raise(SIGTRAP);                                                \
        }
#define GLCheckError(x)                                                        \
        GLClearError();                                                        \
        x;                                                                     \
        ASSERT(!GLLogError(#x, __FILE__, __LINE__))

void GLClearError();

std::string GLErrorCodeToName(unsigned int error_code);

bool GLLogError(const char *function, const char *file, unsigned int line);
