#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include "position.h"

#define DEF_HEIGHT 640.0
#define DEF_WIDTH 800.0
#define CONFIG_PATH "res/.config"

#define SINGLEPLAY 0
#define CLIENT 1
#define SERVER 2

struct Fpc_info
{
    int fpc;
    int fpc_min;
    int fpc_max;
};

struct Models
{
    unsigned int mesh_number;
    Position position;
};

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

    void load_map();

    std::vector <Models*> *models;

    Fpc_info fpc_info;

private:
	char* map_name;

    void print_fpc();

	void load_config();
	void save_config();
};

#endif KERNEL_H
