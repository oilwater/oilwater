#include <iostream>
#include "GLFW/glfw3.h"
#include "terminal.h"

Terminal::Terminal(Kernel *kernel)
{
    _kernel = kernel;
}

void Terminal::set_keymap(int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS && key != GLFW_KEY_GRAVE_ACCENT)
        std::cout << char(key) << std::endl;
    if(action == GLFW_PRESS && key == GLFW_KEY_ENTER)
        _kernel->do_command("test");
}
