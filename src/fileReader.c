
#include <stdlib.h>
#include <stdio.h>

#include "fileReader.h"


byte* readFile(char* fileName) {
	FILE* file = fopen(fileName, "rb");

	if(file == NULL) {
	    return NULL;
	}
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	byte* contents = malloc(sizeof(byte) * fileSize);
	fread(contents, sizeof(byte), fileSize, file); 

	fclose(file); 

	return contents; 
}
