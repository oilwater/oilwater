#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "model.h"
#include "camera.h"
#include "kernel.h"
#include "string.h"

Kernel::Kernel(int argc, char** argv)
{
	/* default config */
	height = DEF_HEIGHT;
	width = DEF_WIDTH;
	fullscreen = false;
	load_config();
	/* parse command line arguments */
	static const char *optString = "m:h:w:f:";
	int opt = 0;
	opt = getopt(argc, argv, optString);
	while(opt != -1)
	{
		switch(opt) {
			case 'm':
				map_name = optarg;
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
	printf("Loading map %s\n", map_name);
};

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
