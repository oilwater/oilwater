#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "kernel.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <sstream>

Kernel::Kernel(int argc, char** argv)
{
	/* default config */
	server_port = DEF_PORT;
	local_port = DEF_PORT;
	height = DEF_HEIGHT;
	width = DEF_WIDTH;
	fullscreen = false;
	mode = SINGLEPLAY;
	map_name = (char*)malloc(255);
	strcpy(map_name, "default_map");
    load_config();
	/* parse command line arguments */
	static const char *optString = "m:h:w:f:c:s";
	int opt = 0;
	opt = getopt(argc, argv, optString);
	while(opt != -1)
	{
		switch(opt) {
			case 'm':
				map_name = (char*)malloc(sizeof(optarg));
				strcpy(map_name, optarg);
				break;
			case 'h':
				height = atof(optarg);
				break;
			case 'w':
				width = atof(optarg);
				break;
			case 'f':
				fullscreen = atoi(optarg);
				break;
			case 'c':
				if (mode == SERVER)
				{
					printf("Warning: options -c and -s should not be used at one time\n");
				}
				mode = CLIENT;
				server_address = (char*)malloc(sizeof(optarg));
				strcpy(server_address, optarg);
				break;
			case 's':
				if (mode == CLIENT)
				{
					printf("Warning: options -c and -s should not be used at one time\n");
				}
				mode = SERVER;
				break;
		}
		opt = getopt(argc, argv, optString);
	}
	save_config();
	printf("Resolution set to %fx%f\n", width, height);
	if (fullscreen)
	{
		printf("Mode fullscreen\n");
	}
	else
	{
		printf("Mode windowed\n");
	}
	switch (mode)
	{
		case SINGLEPLAY:
			printf("Mode singleplay\n");
			break;
		case CLIENT:
			printf("Mode client, server address is %s\n", server_address);
			break;
		case SERVER:
			printf("Mode server\n");
			break;
	}
    fpc_info.fpc = 0;
    fpc_info.fpc_max = 0;
    fpc_info.fpc_min = 0;
    fpc_info.fpc_min -=1;
}

void Kernel::load_config()
{
	/* open and read config file */
	char option[255];
	char value[255];
	FILE *config_file;
	config_file = fopen(CONFIG_PATH, "r");
	if (config_file != NULL)
	{
		while(fscanf(config_file, "%s %s", option, value) != EOF)
		{
			if (!strcmp(option, "height"))
			{
				height = atof(value);
			}
			if (!strcmp(option, "width"))
			{
				width = atof(value);
			}
			if (!strcmp(option, "fullscreen"))
			{
				fullscreen = atoi(value);
			}
		}
		fclose(config_file);
	}
	else
	{
		printf("Warning: no config file found\n");
	}
}

void Kernel::save_config()
{
	/* write config to config file */
	FILE *config_file;
	config_file = fopen(CONFIG_PATH, "w");
	if (config_file != NULL)
	{
		fprintf(config_file, "%s %f\n", "width", width);
		fprintf(config_file, "%s %f\n", "height", height);
		fprintf(config_file, "%s %i\n", "fullscreen", fullscreen);
		fclose(config_file);
		printf("Config saved\n");
	}
	else
	{
		printf("Warning: can not save config\n");
	}
}

/* was not tested yet */
void Kernel::do_command(char* input)
{
    printf("kernel \x1b[31mDEBUG\x1b[0m input comand '%s'\n", input);
	char command[255];
	sscanf(input, "%s", command);
	if (!strcmp(command, "connect"))
	{
		mode = CLIENT;
		sscanf(input, "%s %s:%d", command, server_address, &server_port);
		/* ... */
	}
	if (!strcmp(command, "server"))
	{
		mode = SERVER;
		sscanf(input, "%s %d", command, &local_port);
		/* ... */
	}
	if (!strcmp(command, "fullscreen"))
	{
		fullscreen = false;
		/* ... */
		save_config();
	}
	if (!strcmp(command, "windowed"))
	{
		fullscreen = true;
		/* ... */
		save_config();
	}
    if (!strcmp(command, "fpc"))
    {
        print_fpc();
    }
  if (!strcmp(command, "loadmap"))
  {
		sscanf(input, "%s %s", command, map_name);
		load_map();
	}
}

void Kernel::load_map()
{
    printf("Loading map %s\n", map_name);
	SModel* model;
    /* erase all models from vector */
    printf("Erasing objects\n");
    while(!models.empty())
	{
        model = models.back();
        free(model);
        models.pop_back();
	}
    ifstream map_file;
    char map_path[255];
	map_path[0] = '\0';
	strcat(map_path, "res/maps/");
	strcat(map_path, map_name);
    strcat(map_path, ".map");
    map_file.open((char*)map_path);
    for(string str; getline(map_file, str); )
    {
        model = new SModel;
        istringstream str_stream(str);
        str_stream >> model->mesh_number;

        str_stream >> model->position.position.v[0];
        str_stream >> model->position.position.v[1];
        str_stream >> model->position.position.v[2];

        str_stream >> model->position.velocity.v[0];
        str_stream >> model->position.velocity.v[1];
        str_stream >> model->position.velocity.v[2];

        str_stream >> model->position.acceleration.v[0];
        str_stream >> model->position.acceleration.v[1];
        str_stream >> model->position.acceleration.v[2];

        str_stream >> model->position.angular_position.v[0];
        str_stream >> model->position.angular_position.v[1];
        str_stream >> model->position.angular_position.v[2];

        str_stream >> model->position.angular_velocity.v[0];
        str_stream >> model->position.angular_velocity.v[1];
        str_stream >> model->position.angular_velocity.v[2];

        str_stream >> model->position.angular_acceleration.v[0];
        str_stream >> model->position.angular_acceleration.v[1];
        str_stream >> model->position.angular_acceleration.v[2];

        models.push_back(model);
	}
	map_file.close();

}

void Kernel::get_cashing_models_names(char* path)
{
    ifstream list_file;
    list_file.open(path);
    if(!list_file.is_open())
        cout << "errrorrrr!!" << endl;
    for(string str; getline(list_file, str); )
    {
        others.push_back(str);
        cout << str << "\t" << others.at(others.size() - 1)  << endl;
    }
    list_file.close();


}

void Kernel::print_fpc()
{
    qDebug() << "fpc now: " << fpc_info.fpc;
    qDebug() << "fpc max: " << fpc_info.fpc_max;
    qDebug() << "fpc min: " << fpc_info.fpc_min;
}

void Kernel::get_network(Network* _network)
{
	network = _network;
}
