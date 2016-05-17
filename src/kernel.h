#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "position.h"
#include "network.h"

#define DEF_HEIGHT 640.0
#define DEF_WIDTH 800.0
#define CONFIG_PATH "res/.config"


#define SINGLEPLAY 0
#define CLIENT 1
#define SERVER 2

using namespace std;


struct Fpc_info
{
    unsigned int fpc;
    unsigned int fpc_min;
    unsigned int fpc_max;
};

struct SModel
{
    unsigned int mesh_number;
    res_pos position;
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
	int server_port;
	int local_port;
    void do_command(char* input);

    void load_map();

    vector<string> others;
    void get_cashing_models_names(char *path);

    vector <SModel*> models;
    char *map_name;

    Fpc_info fpc_info;
    Network *network;
    void get_network(Network* network);
private:
		bool map_was_loaded;
    void print_fpc();

	void load_config();
	void save_config();
};

#endif // KERNEL_H
