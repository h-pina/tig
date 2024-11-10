#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

static LogLevel usedLLevel;

static const char* colorCodes[] = {
	"\e[0;34m", //info
	"\e[0;33m", //warning
	"\e[0;35m", //debug
	"\e[0;31m", //error
};

static const char* levelNames[] = {
	"INFO", "WARNING", "DEBUG", "ERROR"
};


//TODO: Change this function for compilation flags
void loggerInit(LogLevel level){
	usedLLevel = level;
}


void loggerLog(LogLevel level, const char *filename, int line, const char *fmt, ...){
	if (level <= usedLLevel){
		va_list ap;
		va_start(ap, fmt);
		fprintf(
			stdout, 
			"%s[%s]\x1b[0;0m \x1b[2;37m%s:%d\e[0;0m ",
			colorCodes[level],
			levelNames[level],
			filename,
			line
		);

		vfprintf(stdout, fmt, ap);
		fprintf(stdout, "\n");
		fflush(stdout);
		va_end(ap);
	}
}
