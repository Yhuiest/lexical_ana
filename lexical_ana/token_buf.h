#pragma once
#include "common.h"
#include "token.h"


char ** token_buf = new char *[TOKEN_BUF_SIZE];
int token_buf_num = 0;
int token_buf_size = TOKEN_BUF_SIZE;
void add_token(char * a)
{
	while (token_buf_num >= token_buf_size)
	{
		char ** tmp = token_buf;
		token_buf = new char*[token_buf_size + TOKEN_OFFSET];
		copy(tmp, tmp + token_buf_size, token_buf);
		token_buf_size += TOKEN_OFFSET;
		delete[] tmp;
	}
	token_buf[token_buf_num] = a;
	token_buf_num++;
}

