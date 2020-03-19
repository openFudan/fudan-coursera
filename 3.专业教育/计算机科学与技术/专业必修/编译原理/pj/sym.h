/*
 * sym.h
 * Copyright (C) 2018 eric <eric_liu@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SYM_H
#define SYM_H
#include "util.h"
typedef struct S_sym_* S_sym;
typedef struct S_table_* S_table;

struct S_sym_ {
    string name;
    S_sym next;
};

struct S_table_ {
    S_sym chain;
    S_table parent;
};

S_sym S_symbol(string name);
//S_sym S_symbol(S_table,string name);
S_sym S_sym_init(string name);
S_sym S_sym_lookup(S_table,string);

S_table S_table_init(S_table parent);
void S_table_add(S_table,S_sym);




#endif /* !SYM_H */
