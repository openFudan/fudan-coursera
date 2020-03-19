/*
 * state.h
 * Copyright (C) 2018 hzshang <hzshang15@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef STATE_H
#define STATE_H

#define MAX_LINE 4096

void state_newline();
void state_reset(char*);
extern int lines[MAX_LINE];
extern int line_num;
extern int last_token_len[2];
extern int last_token_pos[2];
extern int state_pos;
extern int token_pos;
#endif /* !STATE_H */
