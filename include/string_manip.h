/**
 * @file string_manip.h
 * @brief 
 * @author Travis Lane
 * @version 1.0
 * @date 2014-12-08
 */


#ifndef STRING_MANIP_H
#define STRING_MANIP_H

void trim(char* str);
void ltrim(char* str);
void rtrim(char* str);

int ismorse(const char c);
int ismorsestr(const char* str);

#endif /* STRING_MANIP_H */
