
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>

#include "logit.h"

bool debug_logit = false;
#define DEBUG_LOGIT(x) ((debug_logit == true) ? (x) : (0))

int logit_tracelevel = 0; /* default user trace level */

int logit_inbuilt_debugger(const char *caller, const char *file, const int lineno, const char *fmt, va_list ap)
{
	int retval = -1;
	time_t curtime;
	char tmbuff[64] = {0};
	struct tm *loc_time = NULL;

	do {
		if ((caller == NULL) || (file == NULL) || (lineno < 0) || (fmt == NULL)) {
			fprintf(stderr, "%s: invalid arguments !!!\n", __func__);
			retval = -1;
			break;
		}

		/* get UTC time */
		curtime = time (NULL);

		/* Convert UTC to local time */
		loc_time = localtime (&curtime);
		strftime(tmbuff, sizeof tmbuff, "%H:%M:%S", loc_time);

		/* prefix PID, Time, File, Line and Debugee function */
		fprintf(stdout, "\33[2K\r%5d %s%20s:%-4d %-10s : ", getpid(), tmbuff, file, lineno, caller);

		/* print debugee message */
		vfprintf(stdout, fmt, ap);
		fprintf(stdout, "\n");
		fflush(stdout);

		/* close varg list */
		va_end(ap);

		retval = 0;
	} while(0);

	DEBUG_LOGIT(fprintf(stderr, "%s: retval: %d\n", __func__, retval));

	return retval;
}

int logit_worker(const int level, const char *caller, const char *file, const int line, const char *fmt, ...)
{
	va_list ap;
	int retval = -1;

	do {
		DEBUG_LOGIT(fprintf(stderr, "%s: called\n", __func__));

		if (level == NONE) {
			fprintf(stderr, "%s: debug not enabled !!!\n", __func__);
			retval = -1;
			break;
		}

		if (logit_tracelevel < 0) {
			/* added this check to avoid user missing the warning and error logs */
			fprintf(stderr, "%s: invalid trace level '%d' (value must be greater than 0)\n", __func__, logit_tracelevel);
			retval = -1;
			break;
		}

		if (level > logit_tracelevel) {
			retval = 0;
			break;
		}

		va_start(ap, fmt);

		switch (level) {
			case INFO:
				if (logit.info == NULL) {
					fprintf(stderr, "%s: logit.info is NULL !!!\n", __func__);
				} else {
					retval = logit.info(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			case DEBUG:
				if (logit.debug == NULL) {
					fprintf(stderr, "%s: logit.debug callback is NULL !!!\n", __func__);
				} else {
					retval = logit.debug(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			case TRACE:
				if (logit.trace == NULL) {
					fprintf(stderr, "%s: logit.trace callback is NULL !!!\n", __func__);
				} else {
					retval = logit.trace(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			case WARN:
				if (logit.warn == NULL) {
					fprintf(stderr, "%s: logit.warn callback is NULL !!!\n", __func__);
				} else {
					retval = logit.warn(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			case ERROR:
				if (logit.error == NULL) {
					fprintf(stderr, "%s: logit.error callback is NULL !!!\n", __func__);
				} else {
					retval = logit.error(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			case FATAL:
				if (logit.fatal == NULL) {
					fprintf(stderr, "%s: logit.fatal callback is NULL !!!\n", __func__);
				} else {
					retval = logit.fatal(__func__, __FILE__, __LINE__, fmt, ap);
				}
				break;

			default:
				fprintf(stderr, "%s: unclassified debug level: %d message: '%s'\n", __func__, level, fmt);
				retval = -1;
				break;
		};

		va_end(ap);
	} while(0);

	DEBUG_LOGIT(fprintf(stderr, "%s: retval: %d\n", __func__, retval));

	return retval;
}

/* EOF */
