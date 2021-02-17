#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>



// code for time() goes here
time_t time(time_t *tloc) {
	static int count = 1;
	
	if(count == 1) {
		// call own time,
		struct tm ltm = {0};
		char start[] = "2020-01-02";  // next day of start date
		strptime(start, "%Y-%m-%d", &ltm);
		time_t t = mktime(&ltm);
		if(tloc != NULL) {
			*tloc = t;
		}
		
		count = 2;
		return t;
	}
	else {
		time_t (*original_time)(time_t *);
		original_time = dlsym(RTLD_NEXT, "time");
		
		return original_time(tloc);
	}
}
