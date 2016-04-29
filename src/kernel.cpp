#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "model.h"
#include "camera.h"
#include "kernel.h"

Kernel::Kernel(int argc, char** argv)
{
	/* parse command line arguments */
	int opt = 0;
	opt = getopt( argc, argv, optString );
		while( opt != -1 ) {
			switch( opt ) {
				case 'm':
					map_name = optarg;
					break;
			}
		opt = getopt( argc, argv, optString );
	}
	printf("Loading map %s\n", map_name);
};
