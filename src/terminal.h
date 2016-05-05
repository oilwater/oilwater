#ifndef TERMINAL_H
#define TERMINAL_H

#include "kernel.h"

class Terminal
{
public:
    Terminal(Kernel *kernel);

     void set_keymap(int key, int scancode, int action, int mods);

private:
    Kernel *_kernel;
};

#endif // TERMINAL_H
