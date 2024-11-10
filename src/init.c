#include <sys/stat.h>
#include "logger.h"

void init(){
	mkdir("./.tig", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	mkdir("./.tig/objects", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
