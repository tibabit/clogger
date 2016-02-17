/*
 * clogger.h
 *
 *  Created on: 17-Feb-2016
 *      Author: vikash
 */

#ifndef INCLUDE_CLOGGER_H_
#define INCLUDE_CLOGGER_H_

typedef const char * const msg_t;


typedef enum
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
}LogLevel;

typedef enum
{
	GREEN,
	YELLOW,
	RED,
	BLUE,
}LogColor;

typedef void (*generic_log_functon)(LogLevel, msg_t);
typedef void (*log_functon)(msg_t);


typedef struct _clogger
{
	generic_log_functon log;
	log_functon info;
	log_functon warn;
	log_functon error;
	log_functon debug;
}clogger;

extern clogger logger;

void clogger_init(void);

#endif /* INCLUDE_CLOGGER_H_ */
