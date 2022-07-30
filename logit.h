
#ifndef __LOGIT_CALLBACKS_H__
#define __LOGIT_CALLBACKS_H__

#include <stdio.h>
#include <stdarg.h>

#define logit(level, dbgmsg...) (logit_worker(level, __FUNCTION__, __FILE__, __LINE__, dbgmsg))
#define __LOGIT_VARGS__ (const char *caller, const char *file, const int lineno, const char *fmt, va_list ap)

enum {
    FATAL = -3,
    ERROR = -2,
    WARN  = -1,
    NONE  =  0,
    INFO  =  1,
    DEBUG =  2,
    TRACE =  3,
};

struct {
    int (*info)  __LOGIT_VARGS__ ;
    int (*debug) __LOGIT_VARGS__ ;
    int (*trace) __LOGIT_VARGS__ ;
    int (*warn)  __LOGIT_VARGS__ ;
    int (*error) __LOGIT_VARGS__ ;
    int (*fatal) __LOGIT_VARGS__ ;
} logit;

extern int logit_tracelevel;
extern int logit_worker(const int level, const char *caller, const char *file, const int line, const char *fmt, ...);
extern int logit_inbuilt_debugger(const char *caller, const char *file, const int lineno, const char *fmt, va_list ap);

#endif

