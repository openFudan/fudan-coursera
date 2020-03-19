/*
 * parse_tree.h
 * Copyright (C) 2018 eric <eric_liu@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PARSE_TREE_H
#define PARSE_TREE_H
#include "sym.h"
#include "absyn.h"
void parse_goal(A_goal root);
void parse_main(A_main main);

void parse_classes(A_class_list list);
void parse_class(A_class cls);

void parse_exps(A_exp_list list);
void parse_exp(A_exp exp);

void parse_stms(A_stm_list list);
void parse_stm(A_stm stm);

void parse_methods(A_method_list list);
void parse_method(A_method m);

void parse_type(A_type type);

void parse_var_dec(A_var_dec var_dec);
void parse_var_decs(A_var_dec_list list);

void parse_arg_dec(A_arg_dec arg_dec);
void parse_arg_decs(A_arg_dec_list list);

void parse_sym(S_sym sym);

static void printf_fmt(string fmt,...);
static inline void parse_exp_op(A_exp a,A_op op,A_exp b);
static inline void parse_exp_uminus(A_exp a);
static inline void parse_exp_sub(A_exp val,A_exp sub);
static inline void parse_exp_length(A_exp exp);
static inline void parse_exp_method(A_exp exp,S_sym name,A_exp_list exps);
static inline void parse_exp_array(A_exp size);
static inline void parse_exp_reverse(A_exp exp);
static inline void parse_exp_new_id(S_sym name);




#endif /* !PARSE_TREE_H */
