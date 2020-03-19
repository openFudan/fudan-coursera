#include "stand.h"
#include "util.h"

void *safe_malloc(int length){
    void *p = malloc(length);
    assert(p!=NULL);
    return p;
}

string String(char* p){
    string r = safe_malloc(strlen(p)+1);
    strcpy(r,p);
    return r;
}

string String_init_len(int len){
    string r = safe_malloc(len+1);
    memset(r,0,len);
    return r;
}
