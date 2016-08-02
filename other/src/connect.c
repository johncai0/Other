#include "server.h"

void init_conn(void)
{
	for (int i=0; i<MAX_CONN; i++) {
		fds[i] = -1;
	}
}
