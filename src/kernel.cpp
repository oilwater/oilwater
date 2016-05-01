#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "model.h"
#include "camera.h"
#include "kernel.h"
#include "string.h"

Kernel::Kernel(int argc, char** argv)
{
	/* parse command line arguments */
	static const char *optString = "m:h:w:";
	int opt = 0;
	opt = getopt(argc, argv, optString);
	while(opt != -1) {
		switch(opt) {
			case 'm':
				map_name = optarg;
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 'w':
				width = atoi(optarg);
				break;
		}
		opt = getopt(argc, argv, optString);
	}
	printf("Resolution set to %fx%f\n", width, height);
	printf("Loading map %s\n", map_name);
};
