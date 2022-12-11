/* Do not modify this file */
#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>  // read(), write()
#include <string.h>  // strlen()

/* Make a copy of a string into another (newly-created) string. */
char *string_copy(const char *str);

/* Make a deep copy of variable argv. */
char **clone_argv(char *argv[]);

/* Free all of the strings stored in the input argv. */
void free_argv_str(char *argv[]);

/* Free all of the strings stored in argv, as well as argv itself. */
void free_argv(char **argv);

#endif /*UTIL_H*/
