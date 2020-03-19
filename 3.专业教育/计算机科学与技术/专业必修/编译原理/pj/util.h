#ifndef UTIL_H
#define UTIL_H
#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#define ERR(...)do{\
    fprintf(stderr,__VA_ARGS__);\
}while(0)

typedef char* string;
typedef unsigned char bool;

void* safe_malloc(int length);
string String(char *s);
string String_init_len(int len);

#endif /* !UTIL_H */
