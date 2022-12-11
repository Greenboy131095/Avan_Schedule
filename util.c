/* Do Not Modify This File */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>

#include "util.h"

#define READ_SIZE 1000
#define MAX_READ_SIZE 100000

/* Allocate and copy the contents of a string, 
 * or return NULL if the input is NULL. */
char *string_copy(const char *str) {
    if (!str) { return NULL; } // ignore NULL strings

    size_t size = strlen(str) + 1;
    char *copy = malloc(size); // allocate space for the new string
    if (!copy) { return NULL; }  // error check

    snprintf(copy, size, "%s", str); // copy the string
    return copy;
}

/* Creates a perfect copy of argv, which will require that all associated memory needs
   to eventually be freed. */
char **clone_argv(char *argv[]) {
    size_t n = 0;
    while (argv[n]) {
        n++;
    }
    char **new_argv = calloc(n+1, sizeof(char*));
    
    if (!new_argv) return NULL;
    new_argv[n] = NULL;
    for (size_t i = 0;  i < n;  i++) {
        new_argv[i] = string_copy(argv[i]);
        if (!new_argv[i]) { break; }
    }
    return new_argv;
}

void free_argv(char **argv) {
    if (!argv) { return; }
    free_argv_str(argv);
    free(argv);
}

void free_argv_str(char *argv[]) {
    for (size_t i = 0; argv[i]; i++) {
        free(argv[i]);
        argv[i] = NULL;
    }
}
