#ifndef PLATFORM_H
#define PLATFORM_H

// TODO: Figure out where to get these values for real, or how to 
// get them into/out of Kconfig

#undef ESP32
#define FREERTOS


#include "os.h"

#ifdef FREERTOS
//#include "esp_timer.h"
typedef struct RtosConnType RtosConnType;
typedef RtosConnType* ConnTypePtr;

#define ICACHE_FLASH_ATTR

#if ESP32
#define httpd_printf(fmt, ...) os_printf(fmt, ##__VA_ARGS__)
#else // ESP32
#define httpd_printf(fmt, ...) do {	\
	static const char flash_str[] ICACHE_RODATA_ATTR = fmt;	\
	printf(flash_str, ##__VA_ARGS__);	\
	} while(0)
#endif // ESP32
#else // not FREERTOS
#define printf(...) os_printf(__VA_ARGS__)
#define sprintf(str, ...) os_sprintf(str, __VA_ARGS__)
#define strcpy(a, b) os_strcpy(a, b)
#define strncpy(a, b, c) os_strncpy(a, b, c)
#define strcmp(a, b) os_strcmp(a, b)
#define strncmp(a, b, c) os_strncmp(a, b, c)
#define malloc(x) os_malloc(x)
#define free(x) os_free(x)
#define memset(x, a, b) os_memset(x, a, b)
#define memcpy(x, a, b) os_memcpy(x, a, b)
#define strcat(a, b) os_strcat(a, b)
#define strstr(a, b) os_strstr(a, b)
#define strlen(a) os_strlen(a)
#define memcmp(a, b, c) os_memcmp(a, b, c)
typedef struct espconn* ConnTypePtr;
#define httpd_printf(format, ...) os_printf(format, ##__VA_ARGS__)
#endif // FREERTOS


#endif // PLATFORM_H
