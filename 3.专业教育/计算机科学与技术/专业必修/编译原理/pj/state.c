#include "stand.h"
#include "util.h"
#include "error.h"
#include "state.h"

int line_num;
int lines[MAX_LINE];

int state_pos;
int token_pos;
int last_token_pos[2];
int last_token_len[2];

extern FILE* yyin;

void state_newline(){
    line_num ++;
    lines[line_num] = state_pos;
}

void state_reset(string file){
    line_num = 1;
    yyin = fopen(file,"r");
    if(!yyin){
        ERR("open %s failed\n",file);
        exit(1);
    }
    copy = fdopen(yyin->_fileno,"r");
    if(!copy){
        ERR("open copy mode fail\n");
    }
    err = E_error_init();
}
