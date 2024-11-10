#pragma once

typedef enum {
	info,
	warning,
	debug,
	error
} LogLevel;


#define log_info(...) loggerLog(info, __FILE__,__LINE__,__VA_ARGS__)
#define log_war(...) loggerLog(warning, __FILE__,__LINE__,__VA_ARGS__)
#define log_dbg(...) loggerLog(debug, __FILE__,__LINE__,__VA_ARGS__)
#define log_err(...) loggerLog(error, __FILE__,__LINE__,__VA_ARGS__)

void loggerInit(LogLevel level);

void loggerLog(	LogLevel level, 
								const char* filename,
							 	int line,
							 	const char* fmt,
								...);

