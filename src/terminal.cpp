#include <iostream>
#include "GLFW/glfw3.h"
#include "terminal.h"

Terminal::Terminal(Kernel *kernel)
{
    _kernel = kernel;
    caps_key = false;
}

void Terminal::set_keymap(int key, int scancode, int action, int mods)
{
    std::string key_input;
    if(key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
    {
        if(action == GLFW_RELEASE)
            caps_key = false                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ;
        if(action == GLFW_PRESS)
            caps_key = true;
    }
    if(action == GLFW_RELEASE || action == GLFW_REPEAT)
        if(caps_key)
        {
            switch (key)
            {
                case GLFW_KEY_1:
                    key_input = "!";
                    break;
                case GLFW_KEY_2:
                    key_input = "@";
                    break;
                case GLFW_KEY_3:
                    key_input = "#";
                    break;
                case GLFW_KEY_4:
                    key_input = "$";
                    break;
                case GLFW_KEY_5:
                    key_input = "%";
                    break;
                case GLFW_KEY_6:
                    key_input = "^";
                    break;
                case GLFW_KEY_7:
                    key_input = "&";
                    break;
                case GLFW_KEY_8:
                    key_input = "*";
                    break;
                case GLFW_KEY_9:
                    key_input = "(";
                    break;
                case GLFW_KEY_0:
                    key_input = ")";
                    break;
                case GLFW_KEY_MINUS:
                    key_input = "_";
                    break;
                case GLFW_KEY_EQUAL:
                    key_input = "+";
                    break;

                case GLFW_KEY_Q:
                    key_input = "Q";
                    break;
                case GLFW_KEY_W:
                    key_input = "W";
                    break;
                case GLFW_KEY_E:
                    key_input = "E";
                    break;
                case GLFW_KEY_R:
                    key_input = "R";
                    break;
                case GLFW_KEY_T:
                    key_input = "T";
                    break;
                case GLFW_KEY_Y:
                    key_input = "Y";
                    break;
                case GLFW_KEY_U:
                    key_input = "U";
                    break;
                case GLFW_KEY_I:
                    key_input = "I";
                    break;
                case GLFW_KEY_O:
                    key_input = "O";
                    break;
                case GLFW_KEY_P:
                    key_input = "P";
                    break;
                case GLFW_KEY_LEFT_BRACKET:
                    key_input = "{";
                    break;
                case GLFW_KEY_RIGHT_BRACKET:
                    key_input = "}";
                    break;
                case GLFW_KEY_BACKSLASH:
                    key_input = '|';
                    break;

                case GLFW_KEY_A:
                    key_input = "A";
                    break;
                case GLFW_KEY_S:
                    key_input = "S";
                    break;
                case GLFW_KEY_D:
                    key_input = "D";
                    break;
                case GLFW_KEY_F:
                    key_input = "F";
                    break;
                case GLFW_KEY_G:
                    key_input = "G";
                    break;
                case GLFW_KEY_H:
                    key_input = "H";
                    break;
                case GLFW_KEY_J:
                    key_input = "J";
                    break;
                case GLFW_KEY_K:
                    key_input = "K";
                    break;
                case GLFW_KEY_L:
                    key_input = "L";
                    break;
                case GLFW_KEY_SEMICOLON:
                    key_input = ":";
                    break;
                case GLFW_KEY_APOSTROPHE:
                    key_input = '"';
                    break;

                case GLFW_KEY_Z:
                    key_input = "Z";
                    break;
                case GLFW_KEY_X:
                    key_input = "X";
                    break;
                case GLFW_KEY_C:
                    key_input = "C";
                    break;
                case GLFW_KEY_V:
                    key_input = "V";
                    break;
                case GLFW_KEY_B:
                    key_input = "B";
                    break;
                case GLFW_KEY_N:
                    key_input = "N";
                    break;
                case GLFW_KEY_M:
                    key_input = "M";
                    break;
                case GLFW_KEY_COMMA:
                    key_input = "<";
                    break;
                case GLFW_KEY_PERIOD:
                    key_input = ">";
                    break;
                case GLFW_KEY_SLASH:
                    key_input = "?";
                    break;

                default:
                    break;
            }
        }
    else if(!caps_key)
        {
            switch (key)
            {
            case GLFW_KEY_1:
                key_input = "1";
                break;
            case GLFW_KEY_2:
                key_input = "2";
                break;
            case GLFW_KEY_3:
                key_input = "3";
                break;
            case GLFW_KEY_4:
                key_input = "4";
                break;
            case GLFW_KEY_5:
                key_input = "5";
                break;
            case GLFW_KEY_6:
                key_input = "6";
                break;
            case GLFW_KEY_7:
                key_input = "7";
                break;
            case GLFW_KEY_8:
                key_input = "8";
                break;
            case GLFW_KEY_9:
                key_input = "9";
                break;
            case GLFW_KEY_0:
                key_input = "0";
                break;
            case GLFW_KEY_MINUS:
                key_input = "-";
                break;
            case GLFW_KEY_EQUAL:
                key_input = "=";
                break;

            case GLFW_KEY_Q:
                key_input = "q";
                break;
            case GLFW_KEY_W:
                key_input = "w";
                break;
            case GLFW_KEY_E:
                key_input = "e";
                break;
            case GLFW_KEY_R:
                key_input = "r";
                break;
            case GLFW_KEY_T:
                key_input = "t";
                break;
            case GLFW_KEY_Y:
                key_input = "y";
                break;
            case GLFW_KEY_U:
                key_input = "u";
                break;
            case GLFW_KEY_I:
                key_input = "i";
                break;
            case GLFW_KEY_O:
                key_input = "o";
                break;
            case GLFW_KEY_P:
                key_input = "p";
                break;
            case GLFW_KEY_LEFT_BRACKET:
                key_input = "[";
                break;
            case GLFW_KEY_RIGHT_BRACKET:
                key_input = "]";
                break;
            case GLFW_KEY_BACKSLASH:
                key_input = '\\';
                break;

            case GLFW_KEY_A:
                key_input = "a";
                break;
            case GLFW_KEY_S:
                key_input = "s";
                break;
            case GLFW_KEY_D:
                key_input = "d";
                break;
            case GLFW_KEY_F:
                key_input = "f";
                break;
            case GLFW_KEY_G:
                key_input = "g";
                break;
            case GLFW_KEY_H:
                key_input = "h";
                break;
            case GLFW_KEY_J:
                key_input = "j";
                break;
            case GLFW_KEY_K:
                key_input = "k";
                break;
            case GLFW_KEY_L:
                key_input = "l";
                break;
            case GLFW_KEY_SEMICOLON:
                key_input = ";";
                break;
            case GLFW_KEY_APOSTROPHE:
                key_input = "'";
                break;

            case GLFW_KEY_Z:
                key_input = "z";
                break;
            case GLFW_KEY_X:
                key_input = "x";
                break;
            case GLFW_KEY_C:
                key_input = "c";
                break;
            case GLFW_KEY_V:
                key_input = "v";
                break;
            case GLFW_KEY_B:
                key_input = "b";
                break;
            case GLFW_KEY_N:
                key_input = "n";
                break;
            case GLFW_KEY_M:
                key_input = "m";
                break;
            case GLFW_KEY_COMMA:
                key_input = ",";
                break;
            case GLFW_KEY_PERIOD:
                key_input = ".";
                break;
            case GLFW_KEY_SLASH:
                key_input = "/";
                break;

            default:
                break;
            }
        }
    if(action == GLFW_RELEASE && key == GLFW_KEY_SPACE)
        key_input = " ";
    if(action == GLFW_RELEASE && key == GLFW_KEY_BACKSPACE)
        comand_buf = comand_buf.substr(0, comand_buf.length() - 1);

    comand_buf += key_input;

    if(action == GLFW_RELEASE)
        if(comand_buf.length() > 0)
            std::cout << "oilwater  \x1b[31m%\x1b[0m: " << comand_buf << std::endl;

    if(action == GLFW_PRESS && key == GLFW_KEY_ENTER)
    {
        _kernel->do_command((char *)comand_buf.c_str());
        comand_buf.clear();
    }
}
