#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include "position.h"
#include "network.h"

#define DEF_HEIGHT 640.0
#define DEF_WIDTH 800.0
#define CONFIG_PATH "res/.config"

#define SINGLEPLAY 0
#define CLIENT 1
#define SERVER 2

struct Fpc_info
{
    unsigned int fpc;
    unsigned int fpc_min;
    unsigned int fpc_max;
};

struct SModel
{
    unsigned int mesh_number;
    Position* position;
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

    std::vector <SModel*> *models;
	char* map_name;

    Fpc_info fpc_info;
		Network *network;
		void get_network(Network* network);
private:
		bool map_was_loaded;
    void print_fpc();

	void load_config();
	void save_config();
};

#endif KERNEL_H
