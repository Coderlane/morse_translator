
#include <string_manip.h>

/**
 * @brief Trims the left and right hand sides of a string.
 *
 * @param str The string to trim.
 */
void trim(char* str)
{
	assert(str != NULL);
	ltrim(str);
	rtrim(str);
}

/**
 * @brief Trim the left hand side of the string.
 *
 * @param str The string to trim.
 */
void ltrim(char* str)
{
	int i, len;
	assert(str != NULL);
	len = strlen(str);
	for(i = 0; i < len && isspace(str[i]); i++);
	if(i > 0) {
		memmove(str, str + i, len + i - 1);
	}
}

/**
 * @brief Trim the right hand side of the string.
 *
 * @param str The string to trim.
 */
void rtrim(char* str)
{
	int i, len;
	assert(str != NULL);
	len = strlen(str);
	for(i = len ; i > 0 && isspace(str[i - 1]); i--);
	str[i] = '\0';
}
