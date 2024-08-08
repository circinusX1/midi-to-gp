#ifndef TGSTRING_H
#define TGSTRING_H

#include <stddef.h>
#include <vector>

template<class T>
void v_insert(std::vector<T>& vec, const size_t pos, const T& arg)
{
    if(vec.size() <= pos) vec.resize(pos);
    vec.insert(vec.begin() + pos, arg);
}

struct TGString {
	TGString(){}
	TGString(int n, int v):number(n),value(v){
	};
	int number=0;
	int value=0;
};

#endif // TGSTRING_H
