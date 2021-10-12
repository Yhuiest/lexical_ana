#include "common.h"
#include "token.h"
#include "token_buf.h"
#include <cmath>
#include <vector>
#include <climits>
#include <fstream>
#include <time.h>

enum STATE {
	INITIALSTAT,//初始状态
	IDENTIFIER, //标识符,end
	NUM, //数字,end
	ZERO_NUM, //第一个数字是0
	BIN_NUM, //二进制数
	OCT_NUM, //八进制数
	HEX_NUM, //十六进制数
	STRING, //字符串,end
	ESCAPE, //转义字符
	FLOAT, //浮点数,end
	CHAR //单个字符
	};
enum RE_STATE
{
	INI,
	EXE,
	SIG_EXE,
	MUL_EXE,
	MUL_EXE_END
};
static char key_word[32][20] = {
	"auto","break","case","char","const","continue","default",
	"do","double","else","enum","extern","float","for","goto",
	"if","int","long","register","return","short","signed","sizeof",
	"static","struct","switch","typedef","union","unsigned","void",
	"volatile","while" };

static char max_ull[25] = { "18446744073709551615" };
int num_char;
int num_stat;
int num_word;
int num_line = 1;
char buf[2 * MAX_BUF];

void read_buf(ifstream &f, char * buf, char ** p)
{
	int num;
	f.read(buf, MAX_BUF - 1);
	num = f.gcount(); //获取读入字符数
	if (num < MAX_BUF - 1)  //读到文件末尾，为最后一个字符后加EOF，更新字符数
	{
		*(buf + num) = EOF;
		num_char += MAX_BUF - 1;
	}
	else
	{
		num_char += num;
	}
	//将结尾置为EOF
	*(buf + MAX_BUF - 1) = EOF;
	*p = buf;
}
bool update_buf(ifstream &f, char * buf, char ** p)
{
	int num;
	//读到前一半的末尾
	if (*p - buf == MAX_BUF - 1)
	{
		//覆盖后一半
		read_buf(f, buf + MAX_BUF, p);
		return true;
	}
	//读到后一半的结尾
	else if (*p - buf == 2 * MAX_BUF - 1)
	{
		//覆盖前一半
		read_buf(f, buf , p);
		return true;
	}
	return false;
}

char get_c(ifstream &f, char * buf, char ** p)
{
	char* tmp = *p;
	bool sin_line = false;  //单行注释
	bool mul_line = false;	//多行注释
	bool flag = false;

	if (flag)  //遇到/但不是注释，由于buf已经更新，需返回/
	{
		return '/';
	}
	while (1)
	{
		if (**p == EOF)  //读到buf结尾更新
		{
			if (!update_buf(f,buf,p))
			{
				return **p;
			}
		}
		else if (sin_line)  //单行注释，读到换行
		{
			if (*((*p)++) == '\n')
			{
				sin_line = false;
				num_line++;
			}
		}
		else if (mul_line)	//多行注释
		{
			if (**p == '\n')
			{
				num_line++;
			}
			if (**p == '*' && *((*p) + 1) == '/')
			{
				mul_line = false;
			}
			(*p)++;
		}
		//如果可能是注释
		else if (**p == '/')
		{
			char * pre = (*p) + 1;
			if (*(*p + 1) == EOF)
			{
				if (update_buf(f, buf, &pre))
				{
					*p = pre;
				}
			}
			//单行注释
			if (*pre == '/')
			{
				//直到读到换行
				sin_line = true;
			}
			//多行注释
			else if (*pre == '*')
			{
				mul_line = true;
			}
			else
			{
				flag = true;
				return **p;
			}
		}
		else
		{
			return **p;
		}
	}
}

void print_out()
{
	int num_id = 0;		//
	int num_key = 0;	//
	int num_bo = 0;		//各类单词数量
	int num_op = 0;		//
	int num_con = 0;	//
	ofstream of;
	of.open("result.txt");
	if (!of.is_open())
	{
		cout << "Open output file failed..." << endl;
	}
	of << "Num of characters:" << num_char << endl;
	of << "Num of lines:" << num_line << endl;
	for (int i = 0; i < token_buf_num; i++)
	{
		code *tmp = ((token<char> *)token_buf[i])->c;
		string s1 = tmp->name;
		switch (tmp->num)
		{
		case 0:			//标识符
			num_id++;
			of << "<" << s1 << "," << *(((token<string *> *)token_buf[i])->value) << ">" << endl;
			break;
		case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9://关键字
		case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:
		case 20:case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:
		case 30:case 31:case 32:	
			num_key++;
			of << "<" << s1 << ", " << ">" << endl;
			break;
		case 33:case 34:case 35:case 36:case 37:case 38: //界符
			num_bo++;
			of << "<" << s1 << ", " << ">" << endl;
			break;
		case 78:case 80://字符或字符串
			num_con++;
			of << "<" << s1 << "," << *(((token<string *> *)token_buf[i])->value) << ">" << endl;
			break;
		case 81:
			num_con++;
			of << "<" << s1 << "," << ((token<int> *)token_buf[i])->value << ">" << endl;
			break;
		case 82:
			num_con++;
			of << "<" << s1 << "," << ((token<double> *)token_buf[i])->value << ">" << endl;
			break;
		case 83:
			num_con++;
			of << "<" << s1 << "," << ((token<unsigned int> *)token_buf[i])->value << ">" << endl;
			break;
		case 84:
			num_con++;
			of << "<" << s1 << "," << ((token<unsigned long> *)token_buf[i])->value << ">" << endl;
			break;
		case 85:
			num_con++;
			of << "<" << s1 << "," << ((token<unsigned long long> *)token_buf[i])->value << ">" << endl;
			break;
		case 86:
			of << "<" << s1 << "," << ((token<long> *)token_buf[i])->value << ">" << endl;
			break;
		case 87:
			num_con++;
			of << "<" << s1 << "," << ((token<long long> *)token_buf[i])->value << ">" << endl;
			break;
		case 88:
			num_con++;
			of << "<" << s1 << "," << ((token<float> *)token_buf[i])->value << ">" << endl;
			break;
		default:  //其他都是操作符
			num_op++;
			of << "<" << s1 << ", " << ">" << endl;
		}
	}
	of << "Num of word" << endl;
	of << "\tIdentifier:" << num_id << endl;
	of << "\tKey:" << num_key << endl;
	of << "\tBound:" << num_bo << endl;
	of << "\tOperater:" << num_op << endl;
	of << "\tConstant:" << num_con << endl;
}

//输出错误信息 begin错误行开始指针，error_loc错误位置，msg错误信息
//输出形式
//char c = 'hello';
//              ^
void print_error(char * begin, char * error_loc, const char * msg)
{
	cout << "There is an error on line " << num_line << "." << endl;
	cout << msg << endl;
	char * loc = begin;
	//输出错误行
	while (!(*loc == '\n'))
	{
		//buf边界恰好将错误位置隔开
		if (*loc == EOF)
		{
			if (loc - buf == MAX_BUF - 1)
			{
				loc = buf + MAX_BUF;
			}
			else if(loc - buf == 2 * MAX_BUF - 1)
			{
				loc = buf;
			}
			else
			{
				break;
			}
		}
		cout << *loc;
		loc++;
	}
	cout << endl;						
	//输出错误位置指示信息
	for (loc = begin; loc < error_loc - 1; loc++)
	{		
		if (*loc == '\t')
		{
			cout << '\t';
		}
		else
		{
			cout << ' ';
		}
	}
	cout << '^';
	cout << endl;
}

//处理常数后缀，用强制装换形式存储
//l权重为1，u权重为4，f权重8，所有的后缀组合权值不相同，实现所有后缀一次处理
template <typename T>
void set_suffix(T num, int suffix_flag)
{
	switch (suffix_flag)
	{
	case 1:
	{
		token<long> * t1 = new token<long>(&l_num, num);
		add_token((char *)t1);
		break;
	}
	case 2:
	{
		token<long long> * t2 = new token<long long>(&ll_num, num);
		add_token((char *)t2);
		break;
	}
	case 4:
	{
		token<unsigned> * t3 = new token<unsigned>(&u_num, num);
		add_token((char *)t3);
		break;
	}
	case 5:
	{
		token<unsigned long> * t4 = new token<unsigned long>(&ul_num, num);
		add_token((char *)t4);
		break;
	}
	case 6:
	{
		token<unsigned long long> * t5 = new token<unsigned long long>(&ull_num, num);
		add_token((char *)t5);
		break;
	}
	case 8:
		token<float> * t6 = new token<float>(&f_num, num);
		add_token((char *)t6);
		break;
	}
}

//处理正整数
//3级大小依次为int32_t,int64_t,uint_64t
//低级无法容纳，交给更高级，最高级溢出输出错误信息
template <typename T>
int pars_num(string s, int radix, T * value)
{
	if (radix == 10 && (s.length() > 20 || (s.length() == 20 && s.compare(max_ull) > 0)))
	{
		return 0;
	}
	if ((*value = strtol(s.c_str(), NULL, radix)) != INT_MAX)
	{
		return 1;
	}
	else if ((*value = strtoll(s.c_str(), NULL, radix)) != LLONG_MAX)
	{
		return 2;
	}
	else
	{
		*value = strtoull(s.c_str(), NULL, radix);
		return 6;
	}
}

//处理关键字
bool deal_key_word(int start,int n, char **p)
{
	int len;
	char *tmp = *p;
	for (int i = 0; i < n; i++)
	{
		len = string(key_word[start + i]).length();
		if (strncmp(tmp, key_word[start + i], len) == 0 && !(isalnum(*(tmp + len)) || *(tmp + len) == '_'))
		{
			(*p) += len;
			token<string *> *t = NULL;
			switch (start + i)
			{
			case 0:
				t = new token<string *>(&k_auto);
				break;
			case 1:
				t = new token<string *>(&k_break);
				break;
			case 2:
				t = new token<string *>(&k_case);
				break;
			case 3:
				t = new token<string *>(&k_char);
				break;
			case 4:
				t = new token<string *>(&k_const);
				break;
			case 5:
				t = new token<string *>(&k_continue);
				break;
			case 6:
				t = new token<string *>(&k_default);
				break;
			case 7:
				t = new token<string *>(&k_do);
				break;
			case 8:
				t = new token<string *>(&k_double);
				break;
			case 9:
				t = new token<string *>(&k_else);
				break;
			case 10:
				t = new token<string *>(&k_enum);
				break;
			case 11:
				t = new token<string *>(&k_extern);
				break;
			case 12:
				t = new token<string *>(&k_float);
				break;
			case 13:
				t = new token<string *>(&k_for);
				break;
			case 14:
				t = new token<string *>(&k_goto);
				break;
			case 15:
				t = new token<string *>(&k_if);
				break;
			case 16:
				t = new token<string *>(&k_int);
				break;
			case 17:
				t = new token<string *>(&k_long);
				break;
			case 18:
				t = new token<string *>(&k_register);
				break;
			case 19:
				t = new token<string *>(&k_return);
				break;
			case 20:
				t = new token<string *>(&k_short);
				break;
			case 21:
				t = new token<string *>(&k_signed);
				break;
			case 22:
				t = new token<string *>(&k_sizeof);
				break;
			case 23:
				t = new token<string *>(&k_static);
				break;
			case 24:
				t = new token<string *>(&k_struct);
				break;
			case 25:
				t = new token<string *>(&k_switch);
				break;
			case 26:
				t = new token<string *>(&k_typedef);
				break;
			case 27:
				t = new token<string *>(&k_union);
				break;
			case 28:
				t = new token<string *>(&k_unsigned);
				break;
			case 29:
				t = new token<string *>(&k_void);
				break;
			case 30:
				t = new token<string *>(&k_volatile);
				break;
			case 31:
				t = new token<string *>(&k_while);
				break;
			}
			add_token((char*)t);
			return true;
		}
	}
	return false;
}

//初始化，打开文件，初始化buf
void init(ifstream& File)
{
	string path;
	cout << "Please input the path of file that you want to analyse:";
	cin >> path;
	//path = "C:\\Users\\lmzop\\source\\repos\\lexical_ana\\lexical_ana\\test.cpp";
	File.open(path);
	if (!File.is_open())
	{
		cout << "File open failed" << endl;
	}
	char * p_line = buf;
	File.read(buf, 1023);
	int num_read = File.gcount(); 
	if (num_read < 1023)
	{
		*(buf + num_read) = EOF;
	}
	buf[1023] = EOF;
}

int main()
{
	STATE state = INITIALSTAT;  //状态变量
	char *pre = NULL, *p = NULL;  //前进指针
	char c[2] = {'\0','\0'};    //读入的字符
	unsigned long long num = 0;	//常数临时存储
	bool e_flag = false;    //用于数字处理中是否读到了e
	char next_c;          //字符临时存储
	bool char_flag = false; //转义字符回跳标记
	ifstream f;				//文件输入流
	init(f);
	string lex_buf;			//单词缓冲区
	char * p_line = buf;	//每行开始指针
	p = buf;				
	int suffix_flag = 0;	//后缀权值
	double f_value = 0;		//浮点数

	clock_t start = clock();
	while ((c[0] = get_c(f, buf, &p)) != EOF)
	{
		switch (state)
		{
			//初始状态
		case INITIALSTAT:
			switch (c[0])
			{
				//不可能是标识符的字母
			case 'h': case 'j': case 'k': case 'm': case 'n': case 'o': case 'p':
			case 'q': case 'x': case 'y': case 'z': case 'A': case 'B': case 'C':
			case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
			case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q':
			case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
			case 'Y': case 'Z': case '_':
				p++;
				lex_buf.append(c);
				state = IDENTIFIER;
				break;
				//可能是标识符的字母
			case 'a':
				if (!deal_key_word(0, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'b':
				if (!deal_key_word(1, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'c':
				if (!deal_key_word(2, 4, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'd':
				if (!deal_key_word(6, 3, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'e':
				if (!deal_key_word(9, 3, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'f':
				if (!deal_key_word(12, 2, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'g':
				if (!deal_key_word(14, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'i':
				if (!deal_key_word(15, 2, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'l':
				if (!deal_key_word(17, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'r':
				if (!deal_key_word(18, 2, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 's':
				if (!deal_key_word(20, 6, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 't':
				if (!deal_key_word(26, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'u':
				if (!deal_key_word(27, 2, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'v':
				if (!deal_key_word(29, 2, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
			case 'w':
				if (!deal_key_word(31, 1, &p))
				{
					p++;
					state = IDENTIFIER;
					lex_buf.append(c);
				}
				else
				{
					state = INITIALSTAT;
				}
				break;
				//0开头数字
			case '0':
				state = ZERO_NUM;
				break;
				//数字
			case '1': case '2': case '3': case '4': case '5': case '6':
			case '7': case '8': case '9':
					state = NUM;
				break;
				//运算符
			case '!':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> * t = new token<void *>(&o_rel_not_eq);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_log_not);
					add_token((char *)t);
					p++;
				}
				break;
			case '%':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_mod);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_ari_mod);
					add_token((char *)t);
					p++;
				}
				break;
			case '&':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> * t = new token<void *>(&o_as_bit_and);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '&')
				{
					token<void *> *t = new token<void *>(&o_log_and);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_bit_and);
					add_token((char *)t);
					p++;
				}
				break;
			case '*':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_mul);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_ari_mul);
					add_token((char *)t);
					p++;
				}
				break;
			case '-':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_min);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '-')
				{
					token<void *> *t = new token<void *>(&o_ari_decre);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '>')
				{
					token<void *> *t = new token<void *>(&o_arrow);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_ari_minus);
					add_token((char *)t);
					p++;
				}
				break;
			case '|':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_bit_or);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '|')
				{
					token<void *> *t = new token<void *>(&o_log_or);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_bit_or);
					add_token((char *)t);
					p++;
				}
				break;
			case '+':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_plus);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '+')
				{
					token<void *> *t = new token<void *>(&o_ari_incre);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_ari_plus);
					add_token((char *)t);
					p++;
				}
				break;
			case '=':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_rel_eq);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_as_de);
					add_token((char *)t);
					p++;
				}
				break;
			case '<':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_rel_s_or_eq);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '<')
				{
					char * tmp = pre;
					pre++;
					next_c = get_c(f, buf, &pre);
					if (next_c == '=')
					{
						token<void *> *t = new token<void *>(&o_as_l_mov);
						add_token((char *)t);
						p = pre + 1;
					}
					else
					{
						token<void *> *t = new token<void *>(&o_bit_l);
						add_token((char *)t);
						p = tmp + 1;
					}
				}
				else
				{
					token<void *> *t = new token<void *>(&o_rel_smaller);
					add_token((char *)t);
					p++;
				}
				break;
			case '>':
				pre = p + 1;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_rel_g_or_eq);
					add_token((char *)t);
					p = pre + 1;
				}
				else if (next_c == '>')
				{
					char * tmp = pre;
					pre++;
					next_c = get_c(f, buf, &pre);
					if (next_c == '=')
					{
						token<void *> *t = new token<void *>(&o_as_r_mov);
						add_token((char *)t);
						p = pre + 1;
					}
					else
					{
						token<void *> *t = new token<void *>(&o_bit_r);
						add_token((char *)t);
						p = tmp + 1;
					}
				}
				else
				{
					token<void *> *t = new token<void *>(&o_rel_greater);
					add_token((char *)t);
					p++;
				}
				break;
			case '/':
				pre = p;
				next_c = get_c(f, buf, &pre);
				if (next_c == '=')
				{
					token<void *> *t = new token<void *>(&o_as_div);
					add_token((char *)t);
					p = pre + 1;
				}
				else
				{
					token<void *> *t = new token<void *>(&o_ari_div);
					add_token((char *)t);
					p++;
				}
				break;
				//字符常量
			case '\'':
				p++;
				state = CHAR;
				break;
				//转义字符
			case '\\':
				p++;
				state = ESCAPE;
				break;
				//字符串常量
			case '\"':
				p++;
				state = STRING;
				break;
				//其他一个字符长度符号
			case '{': case '}': case '[': case ']': case '(': case ')':
			case '~': case ',': case '.':case ':': case '?':
			{
				token<void *> *t = new token<void *>;
				switch (c[0])
				{
				case '(':
					t->c = &l_paranthese;
					break;
				case ')':
					t->c = &r_paranthese;
					break;
				case '[':
					t->c = &l_sq_bracket;
					break;
				case ']':
					t->c = &r_sq_bracket;
					break;
				case '{':
					t->c = &l_brace;
					break;
				case '}':
					t->c = &r_brace;
					break;
				case '~':
					t->c = &o_bit_oppo;
					break;
				case ',':
					t->c = &o_comma;
					break;
				case '.':
					t->c = &o_dot;
					break;
				case ':':
					t->c = &colon;
					break;
				case '?':
					t->c = &o_tri;
					break;
				}
				add_token((char *)t);
				p++;
				break;
			}
			case ';':
				p++;
				num_stat++;
				break;
			case '\n':
				num_line++;
				p_line = p + 1;
				p++;
				break;
			case '\t': case ' ':
				p++;
				break;
			}
			break;
			//标识符状态
		case IDENTIFIER:
			if (isalnum(c[0]) || c[0] == '_')
			{
				lex_buf.append(c);
				p++;
			}
			else
			{
				token<string *> *t = new token<string *>(&id, new string(lex_buf));
				add_token((char *)t);
				lex_buf.clear();
				state = INITIALSTAT;
			}
			break;
			//字符串
		case STRING:
			switch (c[0])
			{
			case '\\':
				state = ESCAPE;
				char_flag = false;
				p++;
				break;
			case '\"':
			{
				p++;
				token<string *> *t = new token<string *>(&str, new string(lex_buf));
				add_token((char *)t);
				lex_buf.clear();
				state = INITIALSTAT;
				break;
			}
			default:
				lex_buf.append(c);
				p++;
				break;
			}
			break;
			//转义字符
		case ESCAPE:
			switch (c[0])
			{
			case '0':
				lex_buf.append(c, 1);
				p++;
				break;
			case 'n':
				lex_buf.append("\n");
				p++;
				break;
			case 'r':
				lex_buf.append("\r");
				p++;
				break;
			case 't':
				lex_buf.append("\t");
				p++;
				break;
			case 'v':
				lex_buf.append("\v");
				p++;
				break;
			case 'a':
				lex_buf.append("\a");
				p++;
				break;
			case 'b':
				lex_buf.append("\b");
				p++;
				break;
			case 'f':
				lex_buf.append("\f");
				p++;
				break;
			case '\'':
				lex_buf.append("\'");
				p++;
				break;
			case '\"':
				lex_buf.append("\"");
				p++;
				break;
			case '\\':
				lex_buf.append("\\");
				p++;
				break;
				//16进制
			case 'x':
			{
				int n = 0;
				p++;
				pre = p;
				for (int i = 0; i < 3 && isalnum(next_c = get_c(f, buf, &pre)); i++)
				{
					pre++;
					n *= 16;
					if (next_c >= '0' && next_c <= '9')
					{
						n += next_c - '0';
					}
					else
					{
						n += next_c - 'a' + 10;
					}
				}
				p = pre;
				lex_buf.append(1, n);
			}
				break;
				//八进制
			case '1':case '2':case '3':case '4':case '5':
			case '6':case '7':
			{
				int n = 0;
				n += c[0] - '0';
				p++;
				pre = p;
				for (int i = 0; i < 3 && isdigit(next_c = get_c(f, buf, &pre)); i++)
				{
					pre++;
					n *= 8;
					n += next_c - '0';
				}
				p = pre;
				lex_buf.append(1, n);
				break;
			}
			default:
				lex_buf.append(c);
			}
			if (char_flag)
			{
				state = CHAR;
			}
			else
			{
				state = STRING;
			}
			break;
			//字符常量
		case CHAR:
			if (c[0] == '\'')
			{
				token<string *> *t = new token<string *>(&ch, new string(lex_buf));
				add_token((char *)t);
				lex_buf.clear();
				p++;
				state = INITIALSTAT;
			}
			else
			{
				if (lex_buf.length() < 4)
				{
					if (c[0] == '\\')
					{
						state = ESCAPE;
						char_flag = true;
					}
					else
					{
						lex_buf.append(c);
					}
					p++;
				}
				else if (lex_buf.length() == 4)
				{
					print_error(p_line, p, "Can't recognize");
					while (!(*p == '\'' || *p == EOF))
						p++;
					p++;
					state = INITIALSTAT;
					lex_buf.clear();
				}
			}
			break;
			//数字
		case NUM:
			pre = p;
			while ((next_c = get_c(f, buf, &pre)) != EOF)
			{
				pre++;
				if (next_c == '.' || next_c == 'e' || next_c == 'E')
				{
					if (next_c == 'e' || next_c == 'E')
					{
						e_flag = true;
					}
					lex_buf.push_back(next_c);
					state = FLOAT;
					p = pre;
					break;
				}
				else if (next_c >= '0' && next_c <= '9')
				{
					lex_buf.push_back(next_c);
					p = pre;
				}
				else if (next_c == 'u' || next_c == 'U' || next_c == 'l' || next_c == 'L' 
					|| next_c == 'f' || next_c == 'F')
				{
					do
					{
						next_c = tolower(next_c);
						if (next_c == 'u' || next_c == 'U')
						{
							if (suffix_flag < 4)
							{
								suffix_flag += 4;
							}
							else
							{
								//error
								p = pre;
								print_error(p_line, p, "Can't recognize");
								while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
									p++;
								state = INITIALSTAT;
								break;
							}
						}
						else if (next_c == 'l' || next_c == 'L')
						{
							if (suffix_flag % 4 < 2)
							{
								suffix_flag++;
							}
							else
							{
								//error
								p = pre;
								print_error(p_line, p, "Can't recognize");
								while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
									p++;
								state = INITIALSTAT;
								break;
							}
						}
						else if (next_c == 'f' || next_c == 'F')
						{
							if (suffix_flag == 0)
							{
								suffix_flag += 8;
							}
							else
							{
								//error
								p = pre;
								print_error(p_line, p, "Can't recognize");
								while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
									p++;
								state = INITIALSTAT;
								break;
							}
						}
						next_c = get_c(f, buf, &pre);
						pre++;
					} while (next_c == 'u' || next_c == 'U' || next_c == 'l' || next_c == 'L'
						|| next_c == 'f' || next_c == 'F');
					p = pre - 1;
					if (pars_num(lex_buf, 10, &num))
					{
						set_suffix(num, suffix_flag);
						suffix_flag = 0;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large Integer");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					lex_buf.clear();
					state = INITIALSTAT;
					break;
				}
				else if (isalpha(next_c))
				{
					//error
					p = pre;
					print_error(p_line, p, "Can't recognize");
					while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
						p++;
					state = INITIALSTAT;
					break;
				}
				else
				{
					if (suffix_flag = pars_num(lex_buf, 10, &num))
					{
						set_suffix(num, suffix_flag);
						suffix_flag = 0;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large Integer");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					state = INITIALSTAT;
					lex_buf.clear();
					break;
				}
			}
			p = pre;
			break;
			//浮点数
		case FLOAT:
			pre = p;
			while ((next_c = get_c(f, buf, &pre)) != EOF)
			{
				if ((next_c >= '0' && next_c <= '9') || next_c == '+' || next_c == '-')
				{
					lex_buf.push_back(next_c);
					p = pre;
					pre++;
				}
				else if (next_c == 'e' || next_c == 'E')
				{
					if (e_flag == false)
					{
						lex_buf.push_back(next_c);
						p = pre;
						pre++;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Can't recognize");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
				}
				else if (next_c == 'f' || next_c == 'F')
				{
					f_value = strtod(lex_buf.c_str(), NULL);
					if (f_value == INFINITY)
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large float");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					else
					{
						suffix_flag = 8;
						set_suffix(f_value, suffix_flag);
						suffix_flag = 0;
					}
					state = INITIALSTAT;
					p = pre + 1;
					pre++;
					lex_buf.clear();
					break;
				}
				else if (isalpha(next_c) || next_c == '.')
				{
					//error
					p = pre;
					print_error(p_line, p, "Can't recognize");
					while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
						p++;
					state = INITIALSTAT;
					break;
				}
				else
				{
					p = pre;
					f_value = strtod(lex_buf.c_str(), NULL);
					if (f_value == INFINITY)
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large float");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					else
					{
						token<double> * t = new token<double>(&double_num, f_value);
						add_token((char *)t);
					}
					state = INITIALSTAT;
					lex_buf.clear();
					break;
				}
			}
			p = pre;
			break;
			//0开头
		case ZERO_NUM:
			pre = p + 1;
			next_c = get_c(f, buf, &pre);
			//16进制
			if (next_c == 'x' || next_c == 'X')
			{
				state = HEX_NUM;
				p = pre + 1;
			}
			//2进制
			else if (next_c == 'b' || next_c == 'B')
			{
				state = BIN_NUM;
				p = pre + 1;
			}
			//8进制
			else if(next_c >= '0' && next_c <= '7')
			{
				state = OCT_NUM;
				p = pre;
			}
			//浮点数
			else if (next_c == '.')
			{
				lex_buf.push_back('0');
				lex_buf.push_back(next_c);
				p = pre + 1;
				state = FLOAT;
			}
			//错误
			else if (isalpha(next_c))
			{
				//error
				p = pre;
				print_error(p_line, p, "Can't recognize");
				while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
					p++;
				state = INITIALSTAT;
				break;
			}
			//终态
			else
			{
				token<int> * t = new token<int>(&int_num, 0);
				add_token((char *)t);
				p = pre;
				state = INITIALSTAT;
			}
			break;
			//16进制
		case HEX_NUM:
			pre = p;
			while ((next_c = get_c(f, buf, &pre)) != EOF)
			{
				if ((next_c >= 'a' && next_c <= 'f') || (next_c >= 'A' && next_c <= 'F') || (next_c >= '0' && next_c <= '9'))
				{
					lex_buf.push_back(next_c);
					pre++;
				}
				else
				{
					if (suffix_flag = pars_num(lex_buf, 16, &num))
					{
						set_suffix(num, suffix_flag);
						suffix_flag = 0;
						p = pre;
						lex_buf.clear();
						state = INITIALSTAT;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large Integer");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					break;
				}
			}
			p = pre;
			break;
			//8进制
		case OCT_NUM:
			pre = p;
			while ((next_c = get_c(f, buf, &pre)) != EOF)
			{
				
				if (next_c >= '0' && next_c <= '7')
				{
					lex_buf.push_back(next_c);
					pre++;
				}
				else
				{
					if (suffix_flag = pars_num(lex_buf, 8, &num))
					{
						set_suffix(num, suffix_flag);
						suffix_flag = 0;
						p = pre;
						lex_buf.clear();
						state = INITIALSTAT;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large Integer");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					break;
				}
			}
			p = pre;
			break;
			//2进制
		case BIN_NUM:
			pre = p;
			while ((next_c = get_c(f, buf, &pre)) != EOF)
			{

				if (next_c == '0' || next_c == '1')
				{
					lex_buf.push_back(next_c);
					pre++;
				}
				else
				{
					if (suffix_flag = pars_num(lex_buf, 2, &num))
					{
						set_suffix(num, suffix_flag);
						suffix_flag = 0;
						p = pre;
						lex_buf.clear();
						state = INITIALSTAT;
					}
					else
					{
						//error
						p = pre;
						print_error(p_line, p, "Too large Integer");
						while (!(*p == ' ' || *p == '\t' || *p == '\n' || *p == EOF))
							p++;
						state = INITIALSTAT;
						break;
					}
					break;
				}
			}
			p = pre;
			break;
		}
	}
	clock_t end = clock();
	cout << "Program finshed in " << end - start << "ms" << endl;
	print_out();
}