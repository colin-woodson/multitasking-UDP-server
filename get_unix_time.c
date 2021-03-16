#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>
//#include <time.h> 


int get_unix_time() 
{ 
	struct timeval timevalue;
	int ret = gettimeofday(&timevalue, NULL);
	if (ret != 0) {
		perror("gettimeofday()");
		exit(1);
	}

	//printf("The second is <%ld> from 1970!\n", timevalue.tv_sec);

	return timevalue.tv_sec; 
}
