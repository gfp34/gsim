#include <stdlib.h>
#include <stdio.h>

#include "fileReader.h"
#include "simulator.h"


int main(int argc, char* argv[]) {
	if(argc < 2) {
		fprintf(stderr, "Usage: gsim filename [args]\n");
		return EXIT_FAILURE;
	}

	byte* execFile = readFile(argv[1]);
	if(execFile == NULL) {
	    fprintf(stderr, "File \"%s\" does not exist!\n", argv[1]);
        return EXIT_FAILURE;
	}

	sim_init(execFile, argc, argv);
	sim_run();
	sim_exit();

	return EXIT_SUCCESS;
}
