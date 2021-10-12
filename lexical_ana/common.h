#pragma once

#include <iostream>
#include <string>
#include <map>
#define MAX_BUF 1024
#define TOKEN_BUF_SIZE 1000
#define TOKEN_OFFSET 100

using namespace std;

typedef struct CODE
{
	int num;
	char name[20];
}code;
extern code id;
extern code k_auto;
extern code k_break;
extern code k_case;
extern code k_char;
extern code k_const;
extern code k_continue;
extern code k_default;
extern code k_do;
extern code k_double;
extern code k_else;
extern code k_enum;
extern code k_extern;
extern code k_float;
extern code k_for;
extern code k_goto;
extern code k_if;
extern code k_int;
extern code k_long;
extern code k_register;
extern code k_return;
extern code k_short;
extern code k_signed;
extern code k_sizeof;
extern code k_static;
extern code k_struct;
extern code k_switch;
extern code k_typedef;
extern code k_union;
extern code k_unsigned;
extern code k_void;
extern code k_volatile;
extern code k_while;
extern code l_paranthese;
extern code r_paranthese;
extern code l_sq_bracket;
extern code r_sq_bracket;
extern code l_brace;
extern code r_brace;
extern code o_ari_plus;
extern code o_ari_minus;
extern code o_ari_mul;
extern code o_ari_div;
extern code o_ari_incre;
extern code o_ari_decre;
extern code o_ari_mod;
extern code o_rel_eq;
extern code o_rel_not_eq;
extern code o_rel_greater;
extern code o_rel_smaller;
extern code o_rel_g_or_eq;
extern code o_rel_s_or_eq;
extern code o_log_not;
extern code o_log_and;
extern code o_log_or;
extern code o_as_de;
extern code o_as_plus;
extern code o_as_min;
extern code o_as_mul;
extern code o_as_div;
extern code o_as_mod;
extern code o_as_l_mov ;
extern code o_as_r_mov;
extern code o_as_bit_and;
extern code o_as_bit_or;
extern code o_as_bit_xor;
extern code o_bit_and;
extern code o_bit_or;
extern code o_bit_oppo;
extern code o_bit_xor;
extern code o_bit_l;
extern code o_bit_r;
extern code o_tri;
extern code o_dot;
extern code o_arrow;
extern code o_comma;
extern code semicolon;
extern code colon;
extern code str;
extern code escape;
extern code ch;
extern code int_num;
extern code double_num;
extern code u_num;
extern code ul_num;
extern code ull_num;
extern code l_num;
extern code ll_num;
extern code f_num;
