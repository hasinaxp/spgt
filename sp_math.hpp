#pragma once
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <initializer_list>
#include <algorithm>

namespace sp {

using namespace std;

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t i32;
typedef int64_t i64;

template<class T>
class buffer 
{
public:
	u32 len;
	u32 off;
	u32 cap;
	T * data;
public:
	buffer() :  len(0), off(0), cap(0), data(nullptr) {};

	~buffer()
	{
		len = off = cap = 0;
		if(data) delete[] data;
	}
	buffer(u32 n) :  len(n), off(0), cap(n), data(nullptr) 
	{
		data = new T[cap];
	};
	buffer(const buffer & b) : len(b.len), off(b.off), cap(b.cap), data(nullptr)
	{
		data = new T[cap];
		for(u32 i = 0; i < len; i++) data[index(i)] = b.data[index(i)];
	};
	buffer<T>& operator =(const buffer& b)
    {
        len = b.len;
        off = b.off;
        cap = b.cap;
        if(data) delete[] data;
        data = new T[cap];
		for(u32 i = 0; i < len; i++) data[index(i)] = b.data[index(i)];
        return *this;
    }
    buffer(initializer_list il)
    {
    	len = cap = il.size();
    	off = 0;
    	data = new T[cap];
    	u32 i = 0;
    	for(auto it = il.begin();it != il.end(); it++) data[index(i++)] = *it;
    }
	buffer(const vector<T> &v)
	{
		len = cap = v.size();
    	off = 0;
    	data = new T[cap];
		for(u32 i = 0; i < len; i++) data[i] = v[i];
	}
	buffer<T>& operator =(const vector<T> &v)
    {
        len = cap = v.size();
    	off = 0;
    	data = new T[cap];
		for(u32 i = 0 ; i < len; i++) data[i] = v[i];
        return *this;
    }
    T& operator[](u32 i) 
    {
    	return data[index(i)];
    }
    T& front()
    {
    	return data[index(off)];
    }
    T& back()
    {
    	return data[index(len - 1)];
    }
    T& at(u32 i)
    {
    	return data[index(i)];
    }
    T* array(u32 & n)
    {
    	T * arr = new T[len];
		for(u32 i = 0 ; i < len; i++) arr[i] = data[index(i)];
		return arr;
    }

    void push(T t) 
    {
    	check(len + 1);
    	len++;
    	data[len -1] = t;
    }
    void push(initializer_list il)
    {
    	u32 i = len;
    	check(len + il.size());
    	len += il.size();
    	for(auto it = il.begin();it != il.end(); it++) data[index(i++)] = *it;
    }
	T pop()
	{
		if(len == 0) return T();
		check(len);
		len--;
		return data[index(len)];
	}
	void shift(u32 n = 1)
	{
		if(n >= len) return;
		off += n;
		len -= n;
		check(len);		
	}
	void resize(u32 n)
	{
		check(n);
	}
	void fill(T t)
	{
		for(u32 i = 0; i < len; i++) data[index(i)] = t;
	}
	buffer<T> map(T (*func)(const T & t))
	{
		buffer b(len);
		for(u32 i = 0; i < len; i++) b.data[i] = func(at(i));
		return b;
	}
	buffer<T> filter(bool (*func)(const T & t))
	{
		buffer b(len);
		u32 x = 0;
		for(u32 i = 0; i < len; i++) if(func(at(i))) b.data[x++] = t;
		b.check(b.len);
		return b;
	}

	i32 indexOf(const T & t) {
		for(u32 i = 0; i < len; i++)
			if(t == at(i))
				return i;
		return -1;
	}

	buffer<T> concat(const buffer<T> &b)
	{
		buffer<T> b1(len + b.len);
		u32 x = 0;
		for(u32 i = 0; i < len; i++) b1.data[x++] = at(i);
		for(u32 i = 0; i < b.len; i++) b1.data[x++] = b.at(i);
		return b1;
	}
	buffer<T> unique()
	{

		buffer b(len);
		set<T> s;
		for(u32 i = 0; i < len; i++) s.insert(at(i));
		u32 x = 0;
		for(T t : s) b.data[x++] = t;
		b.check(b.len);
		return b;
	}
	buffer<T> common(const buffer<T> &b)
	{
		set<T> s1;
		for(u32 i = 0; i < len; i++) s1.insert(at(i));
		set<T> s2;
		for(u32 i = 0; i < b.len; i++) s2.insert(b.at(i));
		u32 x = 0;
		buffer b1(len);
		for(T t : s1) if(s2.count(t) == 1) b1[x++] = t;
		b1.check(b1.len);
		return b1;
	}
	bool is_permutation(const buffer<T> &b)
	{
		int c1 = 0;
		for(u32 i = 0; i < len; i++) if(b.indexOf(at(i)) != -1) c1++;
		int c2 = 0;
		for(u32 i = 0; i < b.len; i++) if(indexOf(b2.at(i)) != -1) c2++;
		return s1.size() == s2.size();
	}

	buffer<T> operator+(const buffer<T> &b)
	{
		return concat(b);
	}
	buffer<T>& operator+=(const buffer<T> &b)
	{
		check(len + b.len);
		u32 x = len;
		for(u32 i = 0; i < b.len; i++) data[index(x++)] = b.at(i);
		return *this;
	}
	

private:
	int check(u32 n)
	{
		off %= cap;
		if(n >= cap) 
		{
			u32 cap2 = cap;
			while(n >= cap2)
				cap2 *= 2;
			T * data2 = T[cap2];
			for(u32 i = 0; i < len; i++) data2[i] = data[index(i)];
			delete[] data;
			data = data2;
			off = 0;
			cap = cap2;
		}
		else if (len < cap / 2 ) 
		{
			T * data2 = T[len];
			for(u32 i = 0; i < len; i++) data2[i] = data[index(i)];
			delete[] data;
			data = data2;
			off = 0;
			cap = len;
		}

		return (off + len - 1) % cap;
	}

	int index(int i) {
		return (i + off) % cap;
	}

};





}; //namespace sp