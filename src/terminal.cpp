#include <iostream>
#include "GLFW/glfw3.h"
#include "terminal.h"

Terminal::Terminal(Kernel *kernel)
{
    _kernel = kernel;
}

void Terminal::set_keymap(int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS && key != GLFW_KEY_ESCAPE)
        std::cout << char(key) << std::endl;
}
