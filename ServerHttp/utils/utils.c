#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void print_time(void) {
	time_t now = time(NULL);
	char *timestr = ctime(&now);
	timestr[strlen(timestr)-1] = '\0';
	printf("[%s] ", timestr);
}
