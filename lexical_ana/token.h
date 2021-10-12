#pragma once
#include "common.h"
template<class T>
class token
{
public :
	code * c;
	T value;
	token(code * c, T v);
	token();
	token(code * c);
};
template <class T>
token<T>::token()
{

}
template <class T>
token<T>::token(code * c)
{
	this->c = c;
	this->value = NULL;
}
template <class T>
token<T>::token(code * c, T v)
{
	this->c = c;
	this->value = v;
}

