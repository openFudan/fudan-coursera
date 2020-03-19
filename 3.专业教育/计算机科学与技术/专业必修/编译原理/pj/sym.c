#include "stand.h"
#include "sym.h"


S_sym S_symbol(string name){
    /*
    S_sym tmp = S_sym_lookup(t,name);
    if(!tmp){
        tmp = S_sym_init(name);
        S_table_add(t,tmp);
    }
    return tmp;
    */
    S_sym tmp = S_sym_init(name);
    return tmp;
}
S_sym S_sym_init(string name){
    S_sym r = safe_malloc(sizeof(*r));
    string tmp_name = safe_malloc(strlen(name)+1);
    strcpy(tmp_name,name);
    r->next = NULL;
    r->name = tmp_name;
}

S_sym S_sym_lookup(S_table t,string name){
    S_table tmp = t;
    while(tmp){
        S_sym p = tmp->chain;
        while(p){
            if(!strcmp(p->name,name))
                return p;
            p = p->next;
        }
        tmp = tmp->parent;
    }
    return NULL;
}

S_table S_table_init(S_table parent){
    S_table t = safe_malloc(sizeof(*t));
    t->chain = NULL;
    t->parent = parent;
}

void S_table_add(S_table t, S_sym s){
    s->next = t->chain;
    t->chain = s;
}
