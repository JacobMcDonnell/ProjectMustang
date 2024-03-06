#ifndef BUILTIN_H
#define BUILTIN_H
#include <stddef.h>

size_t checkbuiltin(const char * const function);
int execbuiltin(size_t index, const size_t n, char * const args[n]);

#endif
