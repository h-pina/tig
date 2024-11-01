#include <stdlib.h>
#include "cli.h"

int main(int argc, char *argv[]) {
	parseCliCommand(argv, argc);
	return EXIT_SUCCESS;
}
