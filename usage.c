
#include <stdio.h>
#include <string.h>

#include "logit.h"

int init_logit(void)
{
	logit_tracelevel = 0; /* Debug levels: 0, 1, 2, 3 */

	/* user can load your own plugins here */
	logit.info = logit.debug = logit.trace = logit.warn = logit.error = logit.fatal = logit_inbuilt_debugger;

	/* open logfile to print debugs into the logfile */
	/*
	logitfp = fopen(__user_logfile__, "w+");
	if (logitfp == NULL) {
		perror("Unable to log the session !!!");
		return -1;
	}
	*/

	return 0;
}

int main()
{
	int retval = -1;

	init_logit();

	retval = logit(INFO,  "INFO  '%s' '%d'", "Hello world", 123);
	retval = logit(DEBUG, "DEBUG '%s' '%d'", "Hello world", 123);
	retval = logit(TRACE, "TRACE '%s' '%d'", "Hello world", 123);
	retval = logit(WARN,  "WARN  '%s' '%d'", "Hello world", 123);
	retval = logit(ERROR, "ERROR '%s' '%d'", "Hello world", 123);
	retval = logit(FATAL, "FATAL '%s' '%d'", "Hello world", 123);

	fprintf(stderr, "%s: retval: %d\n", __func__, retval);

	//close_logit(logitfp); /* call this for file logging */

	return 0;
}




