#ifndef _STRING_EX_H_
#define _STRING_EX_H_

size_t strxcpy(char *dst, const char *src, size_t size);
size_t strxcat(char *dst, const char *src, size_t size);

char* SplitStr(char*& tszString, char nSep);

#ifdef WIN32
	#define snprintf _snprintf
#endif	// WIN32

#endif  // _STRING_EX_H_