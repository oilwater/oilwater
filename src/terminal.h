#ifndef TERMINAL_H
#define TERMINAL_H

#include "kernel.h"
#include <sstream>
#include <string>
class Terminal
{
public:
    Terminal(Kernel *kernel);

     void set_keymap(int key, int scancode, int action, int mods);

private:
    Kernel *_kernel;
    bool caps_key;
    std::string comand_buf;
};

#endif // TERMINAL_H
