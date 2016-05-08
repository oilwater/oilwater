#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "kernel.h"

#include <QDebug>

Kernel::Kernel(int argc, char** argv)
{
	map_was_loaded = false;
	/* default config */
	height = DEF_HEIGHT;
	width = DEF_WIDTH;
	fullscreen = false;
	mode = SINGLEPLAY;
	map_name = "default_map";
	load_config();
	models = new std::vector<SModel*>();
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
		sscanf(input, "%s %s", command, server_address); 
		/* ... */
	}
	if (!strcmp(command, "server"))
	{
		mode = SERVER;
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
	SModel* model;
	/* erase all models from vector */
	while(!models->empty())
	{
		model = models->back();
		delete model->position;
		free(model);
		models->pop_back();
	}
	FILE *map_file;
	char map_path[255];
	map_path[0] = '\0';
	strcat(map_path, "res/maps/");
	strcat(map_path, map_name);
	strcat(map_path, ".map");
	printf("Loading map %s\n", map_path);
	map_file = fopen(map_path, "r");
	int id;
	Position* pos;
	if (map_file != NULL)
	{
		while(fscanf(map_file, "%i\n", &id) != EOF)
		{
			printf("Loading object %d\n", id);
			pos = new Position();
			model = (SModel*)malloc(sizeof(SModel));
			model->mesh_number = id;
			model->position = pos;
			model->position->_res_pos.angular_acceleration.v[2] = 0.01;
			double p0, p1, p2, v0, v1, v2, a0, a1, a2, ap0, ap1, ap2, av0, av1, av2, aa0, aa1, aa2;
			if (fscanf(map_file, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", 
						&p0, &p1, &p2, &v0, &v1, &v2, &a0, &a1, &a2, &ap0, &ap1, &ap2, &av0, &av1, &av2, &aa0, &aa1, &aa2)
						== EOF)
			{
				printf("Unexpected end of map file %s\n", map_path);
			}
			else
			{
				model->position->_res_pos.position.init(p0, p1, p2);
				model->position->_res_pos.velocity.init(v0, v1, v2);
				model->position->_res_pos.acceleration.init(a0, a1, a2);
				model->position->_res_pos.angular_position.init(ap0, ap1, ap2);
				model->position->_res_pos.angular_velocity.init(av0, av1, av2);
				model->position->_res_pos.angular_acceleration.init(aa0, aa1, aa2);
				models->push_back(model);
				printf("Added object %d\n", id);
			}
		}
		fclose(map_file);
	}
	else
	{
		printf("Can not open map %s\n", map_path);
	}

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
