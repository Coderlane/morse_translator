

#ifndef STRING_MANIP_H
#define STRING_MANIP_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void trim(char* str);
void ltrim(char* str);
void rtrim(char* str);

int ismorse(const char c);
int ismorsestr(const char* str);

#endif /* STRING_MANIP_H */
