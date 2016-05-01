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
		}
		fclose(config_file);
	}
	else
	{
		printf("Warning: no config file found\n");
	}
	/* parse command line arguments */
	static const char *optString = "m:h:w:";
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
		}
		opt = getopt(argc, argv, optString);
	}
	/* write config to config file */
//	FILE *config_file;
	config_file = fopen(CONFIG_PATH, "w");
	if (config_file != NULL)
	{
		fprintf(config_file, "%s %f\n", "width", width);
		fprintf(config_file, "%s %f\n", "height", height);
		fclose(config_file);
		printf("Config saved\n");
	}
	else
	{
		printf("Warning: can not save config\n");
	}
	printf("Resolution set to %fx%f\n", width, height);
	printf("Loading map %s\n", map_name);
};
