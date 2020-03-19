#include "stand.h"
#include "util.h"
#include "error.h"
#include "state.h"

E_error err;
FILE* copy;

static string str_dup_line(string p){
    string it = p;
    while(*it && *it!='\n')
        it++;
    int len = it-p;
    string r = safe_malloc(len+1);
    memcpy(r,p,len);
    r[len] = '\x00';
    return r;
}

void record_error(int pos,int len){
    size_t alloc_size;
    string line = NULL;
    E_pos_locate(err->pos,pos);
    fseek(copy,lines[err->pos->row],SEEK_SET);
    getline(&line,&alloc_size,copy);
    int length = strlen(line);
    if(line[length-1]=='\n')
        line[length-1]='\x00';
    err->line = line;
    // given char
    fseek(copy,pos,SEEK_SET);
    err->given = String_init_len(len);
    err->given[fread(err->given,len,sizeof(char),copy)] = '\x00';
    err->kind = E_no_return;
}

void show_error(char const * msg,...){
    va_list ap;
    ERR("Error: %d:%d: ",err->pos->row,err->pos->column);
    va_start(ap,msg);
    vfprintf(stderr,msg,ap);
    va_end(ap);
    ERR("\n> %s\n",err->line);
    ERR("%*c%s\n",err->pos->column+2,' ',GREEN("^"));
}

E_error E_error_init(){
    E_error e = safe_malloc(sizeof(*e));
    memset(e,0,sizeof(*e));
    e->kind = E_none;
    e->pos = E_pos_init();
    return e;
}

E_pos E_pos_init(){
    E_pos p = safe_malloc(sizeof(*p));
    memset(p,0,sizeof(*p));
    return p;
}

void E_pos_locate(E_pos e,int len){
    int num = line_num;
    while(lines[num] > len)
        num--;
    e->row = num;
    e->column = len - lines[num];
}

