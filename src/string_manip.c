
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

/**
 * @brief Checks to see if a string is a morse string.
 *
 * @param str The string to check.
 *
 * @return 1 if it is a morse string, else 0.
 */
int
ismorsestr(const char* str) 
{
	while(*str != '\0') {
		if(!ismorse(*str))
			return 0;	
		str++;
	}
	return 1;
}

/**
 * @brief Checks to see if a character is a morse character.
 *
 * @param c The character to check.
 *
 * @return 1 if it is a morse character, else 0.
 */
int
ismorse(const char c)
{
	switch(c) {
		case '-':
		case '.':
			return 1;
		default:
			return 0;
	}
}
