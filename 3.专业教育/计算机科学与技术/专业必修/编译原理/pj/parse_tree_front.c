#include "stand.h"
#include "parse_tree.h"
#define FOUT stdout

#define STEP 2
#define RSHIFT do{\
    xlen+=STEP;\
}while(0)

#define LSHIFT do{\
    xlen-=STEP;\
}while(0)

#define HEADER(x) do{\
    printf_fmt("\n"x"(");\
    RSHIFT;\
}while(0)

#define FOOT do{\
    LSHIFT;\
    printf_fmt("\n)");\
}while(0)

static int xlen = 0;
static void printf_fmt(string fmt,...){
    va_list ap;
    if(fmt[0]=='\n'){
        fprintf(FOUT,"\n%*c",xlen,' ');
        va_start(ap,&fmt[1]);
        vfprintf(FOUT,&fmt[1],ap);
        va_end(ap);
    }else{
        va_start(ap,fmt);
        vfprintf(FOUT,fmt,ap);
        va_end(ap);
    }
}

void parse_goal(A_goal root){
    HEADER("Goal");
    parse_main(root->main);
    printf_fmt(",");
    parse_classes(root->classes);
    FOOT;
}

void parse_main(A_main main){
    HEADER("MainClass");
    parse_sym(main->id);
    printf_fmt(",");
    parse_sym(main->arg_id);
    printf_fmt(",");
    parse_stm(main->stm);
    FOOT;
}
static inline void parse_class_extends(S_sym ext){
    HEADER("Extends");
    if(!ext)
        printf_fmt("\nNULL");
    else
        parse_sym(ext);
    FOOT;
}
void parse_class(A_class cls){
    HEADER("Class");
    parse_sym(cls->id);
    printf_fmt(",");
    parse_class_extends(cls->extend);
    printf_fmt(",");
    parse_var_decs(cls->vars);
    printf_fmt(",");
    parse_methods(cls->methods);
    FOOT;
}


static inline void parse_exp_op(A_exp a,A_op op,A_exp b){
    HEADER("ExpOp");
    switch(op){
        case A_and:
            printf_fmt("\n&&");
            break;
        case A_plus:
            printf_fmt("\n+");
            break;
        case A_minus:
            printf_fmt("\n-");
            break;
        case A_times:
            printf_fmt("\n*");
            break;
        case A_lt:
            printf_fmt("\n<");
            break;
        default:
            assert(false);
            break;
    }
    printf_fmt(",");
    parse_exp(a);
    printf_fmt(",");
    parse_exp(b);
    FOOT;
}
static inline void parse_exp_uminus(A_exp a){
    HEADER("ExpUminus");
    parse_exp(a);
    FOOT;
}
static inline void parse_exp_sub(A_exp val,A_exp sub){
    HEADER("ExpSub");
    parse_exp(val);
    printf(",");
    parse_exp(sub);
    FOOT;
}
static inline void parse_exp_length(A_exp exp){
    HEADER("ExpLength");
    parse_exp(exp);
    FOOT;
}
static inline void parse_exp_method(A_exp exp,S_sym name,A_exp_list exps){
    HEADER("ExpMethod");
    parse_exp(exp);
    printf_fmt(",");
    parse_sym(name);
    printf_fmt(",");
    parse_exps(exps);
    FOOT;
}
static inline void parse_exp_array(A_exp size){
    HEADER("ExpIntArray");
    parse_exp(size);
    FOOT;
}
static inline void parse_exp_reverse(A_exp exp){
    HEADER("ExpReverse");
    parse_exp(exp);
    FOOT;
}
static inline void parse_exp_new_id(S_sym name){
    HEADER("ExpNew");
    parse_sym(name);
    FOOT;
}
void parse_exp(A_exp exp){
    HEADER("Exp");
    switch(exp->kind){
        case A_exp_ops:
            parse_exp_op(exp->u.op.a,exp->u.op.op,exp->u.op.b);
            break;
        case A_exp_sub:
            parse_exp_sub(exp->u.sub.exp,exp->u.sub.sub);
            break;
        case A_exp_length:
            parse_exp_length(exp->u.length.exp);
            break;
        case A_exp_method:
            parse_exp_method(exp->u.method.exp,exp->u.method.method,exp->u.method.args);
            break;
        case A_exp_id:
            parse_sym(exp->u.id.name);
            break;
        case A_exp_array:
            parse_exp_array(exp->u.array.size);
            break;
        case A_exp_new_id:
            parse_exp_new_id(exp->u.new_id.name);
            break;
        case A_exp_reverse:
            parse_exp_reverse(exp->u.reverse.exp);
            break;
        case A_exp_exp:
            parse_exp(exp->u.exp.exp);
            break;
        case A_exp_uminus:
            parse_exp_uminus(exp->u.uminus.exp);
            break;
        /* code don't have fmt bellow*/
        case A_exp_int:
            printf_fmt("\n%d",exp->u.intval.val);
            break;
        case A_exp_bool:
            printf_fmt("\n%s",exp->u.boolval.val?"true":"false");
            break;
        case A_exp_this:
            RSHIFT;
            printf_fmt("\nthis");
            LSHIFT;
            break;
        default:
            assert(false);
            break;
    }
    FOOT;
}
static inline void parse_stm_if_else(A_exp cond,A_stm yes,A_stm no){
    HEADER("StmIfElse");
    parse_exp(cond);
    printf_fmt(",");
    parse_stm(yes);
    printf_fmt(",");
    parse_stm(no);
    FOOT;
}
static inline void parse_stm_while(A_exp cond,A_stm stm){
    HEADER("StmWhile");
    parse_exp(cond);
    printf_fmt(",");
    parse_stm(stm);
    FOOT;
}
static inline void parse_stm_print(A_exp out){
    HEADER("StmPrint");
    parse_exp(out);
    FOOT;
}
static inline void parse_stm_assign(S_sym name,A_exp exp){
    HEADER("StmAssign");
    parse_sym(name);
    printf_fmt(",");
    parse_exp(exp);
    FOOT;
}
static inline void parse_stm_sub(S_sym name,A_exp idx,A_exp val){
    HEADER("StmSubAssign");
    parse_sym(name);
    printf_fmt(",");
    parse_exp(idx);
    printf_fmt(",");
    parse_exp(val);
    FOOT;
}
void parse_stm(A_stm stm){
    HEADER("Statement");
    switch(stm->kind){
        case A_stm_stms:
            parse_stms(stm->u.stms.stms);
            break;
        case A_stm_if_else:
            parse_stm_if_else(stm->u.cond.cond,stm->u.cond.yes,stm->u.cond.no);
            break;
        case A_stm_loop:
            parse_stm_while(stm->u.loop.cond,stm->u.loop.stm);
            break;
        case A_stm_print:
            parse_stm_print(stm->u.print.out);
            break;
        case A_stm_assign:
            parse_stm_assign(stm->u.assign.name,stm->u.assign.val);
            break;
        case A_stm_sub:
            parse_stm_sub(stm->u.sub.name,stm->u.sub.sub,stm->u.sub.val);
            break;
        case A_stm_var_dec:
            parse_var_dec(stm->u.var_dec.var_dec);
            break;
        default:
            assert(false);
            break;
    }
    FOOT;
}

void parse_method(A_method m){
    HEADER("Method");
    parse_type(m->type);
    printf_fmt(",");
    parse_sym(m->name);
    printf_fmt(",");
    parse_arg_decs(m->args);
    printf_fmt(",");
    parse_stms(m->stms);
    printf_fmt(",");
    parse_exp(m->ret);
    FOOT;
}
void parse_type(A_type type){
    printf_fmt("\n");
    RSHIFT;
    switch (type->kind){
        case A_type_int:
            printf_fmt("Int");
            break;
        case A_type_array:
            printf_fmt("Array");
            break;
        case A_type_boolean:
            printf_fmt("Bool");
            break;
        case A_type_string:
            printf_fmt("String");
            break;
        case A_type_sym:
            parse_sym(type->u.id.name);
            break;
        default:
            assert(false);
            break;
    }
    LSHIFT;
}

void parse_var_dec(A_var_dec var_dec){
    HEADER("VarDeclaration");
    parse_type(var_dec->type);
    printf_fmt(",");
    parse_sym(var_dec->name);
    FOOT;
}

void parse_arg_dec(A_arg_dec arg_dec){
    HEADER("ArgDeclaration");
    parse_type(arg_dec->type);
    printf_fmt(",");
    parse_sym(arg_dec->name);
    FOOT;
}

void parse_sym(S_sym sym){
    printf_fmt("\n%s",sym->name);
}

void parse_arg_decs(A_arg_dec_list list){
    HEADER("ArgDeclarationList");
    A_arg_dec_list tmp = list;
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_arg_dec(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}


void parse_var_decs(A_var_dec_list list){
    HEADER("VarDeclarationList");
    A_var_dec_list tmp = list;
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_var_dec(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}

void parse_methods(A_method_list list){
    HEADER("MethodList");
    A_method_list tmp = list;
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_method(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}
void parse_stms(A_stm_list list){
    A_stm_list tmp = list;
    HEADER("StatementList");
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_stm(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}
void parse_exps(A_exp_list list){
    HEADER("ExpList");
    A_exp_list tmp = list;
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_exp(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}
void parse_classes(A_class_list list){
    HEADER("ClassList");
    A_class_list tmp = list;
    if(!tmp){
        printf_fmt("\nNULL");
    }else{
        while(tmp){
            parse_class(tmp->val);
            if(tmp->next)
                printf_fmt(",");
            tmp = tmp->next;
        }
    }
    FOOT;
}
void parse_op_reverse(A_exp a){
    HEADER("Reverse");
    parse_exp(a);
    FOOT;
}
void parse_op_uminus(A_exp a){
    HEADER("Uminus");
    parse_exp(a);
    FOOT;
}



