# LOGit: Portable debugger with debug leveled callback mechanism

- User can write your own debugger module and load it to `logit` structure as mentioned below. This will callback your module based on the debug levels
```
logit.info  = user_printinfo_api;
logit.debug = user_printdebug_api;
logit.error = user_printerror_api;
```

**Inbuilt variables:**
- `logit_inbuilt_debugger()` - Sample debugger to print debugs to console
- `logit` - LOGit structure variable to call its member as below
```
    retval = logit(INFO,  "INFO  '%s'", "Hello world");
    retval = logit(DEBUG, "DEBUG '%s'", "Hello world");
    retval = logit(TRACE, "TRACE '%s'", "Hello world");
    retval = logit(WARN,  "WARN  '%s'", "Hello world");
    retval = logit(ERROR, "ERROR '%s'", "Hello world");
    retval = logit(FATAL, "FATAL '%s'", "Hello world");
```
- Refer `usage.c` for the usage
