/*
 * absyn.h
 * Copyright (C) 2018 eric <eric_liu@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ABSYN_H
#define ABSYN_H
#include "sym.h"

typedef struct A_stm_* A_stm;
typedef struct A_stm_list_* A_stm_list;

typedef struct A_exp_* A_exp;
typedef struct A_exp_list_* A_exp_list;

typedef struct A_goal_* A_goal;
typedef struct A_main_* A_main;

typedef struct A_class_* A_class;
typedef struct A_class_list_* A_class_list;

typedef struct A_var_dec_* A_var_dec;
typedef struct A_var_dec_list_* A_var_dec_list;

typedef struct A_method_* A_method;
typedef struct A_method_list_* A_method_list;

typedef struct A_arg_dec_* A_arg_dec;
typedef struct A_arg_dec_list_* A_arg_dec_list;
typedef struct A_type_* A_type;

typedef enum{A_and,A_plus,A_minus,A_times,A_lt} A_op;

struct A_goal_ {
    A_main main;
    A_class_list classes;
    S_table tab;
};

struct A_main_ {
    S_sym id;
    S_sym arg_id;
    A_stm stm;
    S_table tab;
};

struct A_class_ {
    S_sym id;
    S_sym extend; // if no extend, it will be null
    A_var_dec_list vars;
    A_method_list methods;
    S_table tab;
};

struct A_class_list_ {
    A_class val;
    A_class_list next;
};

struct A_var_dec_ {
    A_type type;
    S_sym name;
};

struct A_var_dec_list_{
    A_var_dec val;
    A_var_dec_list next;
};

struct A_method_ {
    A_type type;
    S_sym name;
    A_arg_dec_list args;
    A_stm_list stms;
    A_exp ret;
    S_table tab;
};

struct A_method_list_{
    A_method val;
    A_method_list next;
};

struct A_arg_dec_ {
    A_type type;
    S_sym name;
};

struct A_arg_dec_list_ {
    A_arg_dec val;
    A_arg_dec_list next;
};

struct A_type_{
    enum{A_type_int,A_type_array,A_type_boolean,A_type_string,A_type_sym} kind;
    union{
        struct{S_sym name;} id;
    }u;
};


struct A_stm_ {
    enum {A_stm_stms,A_stm_if_else,A_stm_loop,A_stm_print,A_stm_assign,A_stm_sub,A_stm_var_dec} kind;
    union{
        struct{A_stm_list stms;} stms;
        struct{A_exp cond; A_stm yes; A_stm no;} cond;
        struct{A_exp cond; A_stm stm;} loop;
        struct{A_exp out;} print;
        struct{S_sym name; A_exp val;} assign;
        struct{S_sym name; A_exp sub;A_exp val;} sub;
        struct{A_var_dec var_dec;} var_dec;
    } u;
    S_table tab;
};

struct A_stm_list_{
    A_stm val;
    A_stm_list next;
};

struct A_exp_ {
    enum{A_exp_ops,A_exp_sub,A_exp_length,A_exp_method,A_exp_int,A_exp_bool,A_exp_id,A_exp_this,A_exp_array,A_exp_new_id,A_exp_reverse,A_exp_exp,A_exp_uminus} kind;
    union{
        struct{A_exp a;A_op op; A_exp b;} op;
        struct{A_exp exp;A_exp sub;} sub;
        struct{A_exp exp;} length;
        struct{A_exp exp;S_sym method;A_exp_list args;} method;
        struct{int val;} intval;
        struct{bool val;} boolval;
        struct{S_sym name;} id;
        //struct{} pointer; this
        struct{A_exp size;} array;
        struct{S_sym name;} new_id;
        struct{A_exp exp;} reverse;
        struct{A_exp exp;} exp;
        struct{A_exp exp;} uminus;
    } u;
};
struct A_exp_list_ {
    A_exp val;
    A_exp_list next;
};


A_goal A_goal_init(A_main,A_class_list);
A_main A_main_init(S_sym,S_sym,A_stm);
A_class A_class_init(S_sym,S_sym,A_var_dec_list,A_method_list);
A_var_dec A_var_dec_init(A_type,S_sym);
A_method A_method_init(A_type,S_sym,A_arg_dec_list,A_stm_list,A_exp);
A_arg_dec A_arg_dec_init(A_type,S_sym);

A_type A_type_init_int();
A_type A_type_init_array();
A_type A_type_init_boolean();
A_type A_type_init_string();
A_type A_type_init_sym(S_sym);

A_stm A_stm_init_stmlist(A_stm_list);
A_stm A_stm_init_cond(A_exp,A_stm,A_stm);
A_stm A_stm_init_loop(A_exp,A_stm);
A_stm A_stm_init_print(A_exp);
A_stm A_stm_init_assign(S_sym,A_exp);
A_stm A_stm_init_sub(S_sym,A_exp,A_exp);
A_stm A_stm_init_var(A_var_dec);

A_exp A_exp_init_op(A_exp,A_op,A_exp);
A_exp A_exp_init_sub(A_exp,A_exp);
A_exp A_exp_init_length(A_exp);
A_exp A_exp_init_method(A_exp,S_sym,A_exp_list);
A_exp A_exp_init_intval(int);
A_exp A_exp_init_boolval(bool);
A_exp A_exp_init_id(S_sym);
A_exp A_exp_init_this();
A_exp A_exp_init_array(A_exp);
A_exp A_exp_init_newid(S_sym);
A_exp A_exp_init_reverse(A_exp);
A_exp A_exp_init_exp(A_exp);
A_exp A_exp_init_uminus(A_exp);

A_class_list A_class_list_init_null();
A_class_list A_class_list_init_class(A_class c);
A_class_list A_class_list_init_classes(A_class c,A_class_list next);

A_stm_list A_stm_list_init_null();
A_stm_list A_stm_list_init_stm(A_stm s);
A_stm_list A_stm_list_init_stms(A_stm s,A_stm_list next);

/*TODO: not support int a,b,c; */
A_var_dec_list A_var_dec_list_init_null();
A_var_dec_list A_var_dec_list_init_var(A_var_dec val);
A_var_dec_list A_var_dec_list_init_vars(A_var_dec val,A_var_dec_list next);

A_arg_dec_list A_arg_dec_list_init_null();
A_arg_dec_list A_arg_dec_list_init_arg_dec(A_arg_dec arg);
A_arg_dec_list A_arg_dec_list_init_arg_decs(A_arg_dec arg,A_arg_dec_list next);

A_method_list A_method_list_init_null();
A_method_list A_method_list_init_method(A_method val);
A_method_list A_method_list_init_methods(A_method val,A_method_list next);

A_exp_list A_exp_list_init_null();
A_exp_list A_exp_list_init_exp(A_exp);
A_exp_list A_exp_list_init_exps(A_exp,A_exp_list);

/*
 * arg_dec 参数声明 用在函数eg: begin(int a,int b) arg_dec 表示 int a
 * arg_dec_list arg_dec_list 代表 int a,int b
 *
 * var 变量声明，被vars和stm使用
 * vars 目前仅用在类的全局声明
 * stm 代码块
 * exp 表达式
 *
 * TODO: 
 * new ID() 允许传参
 */

#endif /* !ABSYN_H */
