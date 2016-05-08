#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include "model.h"

#define DEF_HEIGHT 640.0
#define DEF_WIDTH 800.0
#define CONFIG_PATH "res/.config"

#define SINGLEPLAY 0
#define CLIENT 1
#define SERVER 2

class Kernel
{
public:
	Kernel(int argc, char **argv);
    float width;
    float height;
    bool fullscreen;
    int mode;
	char* server_address;
    void do_command(char* input);
    void get_models(vector <Model*> *_models);
    void load_map();
private:
	char* map_name;
	vector <Model*> *models;
	void load_config();
	void save_config();
};

#endif KERNEL_H
