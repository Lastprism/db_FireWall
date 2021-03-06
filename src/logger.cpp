#include "logger.h"
#include <string>


void logger::error(string msg)
{
	if(LOG_LEVEL < 10)
	{
		fprintf(stderr,"[error]:%s\n", msg.c_str());
		fflush(stdout);
	}
}

void logger::warning(string msg)
{
	if(LOG_LEVEL < 7)
	{
		printf("[warning]:%s\n", msg.c_str());
		fflush(stdout);
	}
}

void logger::info(string msg)
{
	if(LOG_LEVEL < 5)
	{
		printf("[info]:%s\n", msg.c_str());
		fflush(stdout);
	}
}

void logger::high_debug(string msg)
{
	if(LOG_LEVEL < 3)
	{
		printf("[high debug]:%s\n", msg.c_str());
		fflush(stdout);
	}
}

void logger::debug(string msg)
{
	if(LOG_LEVEL < 1)
	{
		printf("[debug]:%s\n", msg.c_str());
		fflush(stdout);
	}
}

