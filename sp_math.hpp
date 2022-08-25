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
typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;

constexpr f32 pi = 3.14159;
constexpr f32 rad = pi / 180.0;
constexpr f32 deg = 180.0 / pi;

template<class>
class buffer_iterator;

template<class T>
class buffer
{
public:
	u32 len;
	u32 off;
	u32 cap;
	T * data;

	using value_type = T;
	using itr = buffer_iterator<buffer<T>>;
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
		for(u32 i = 0; i < len; i++) data[i] = b.data[index(i)];
		off = 0;
	};
	buffer<T>& operator =(const buffer& b)
    {
        len = b.len;
        off = b.off;
        cap = b.cap;
        if(data) delete[] data;
        data = new T[cap];
				for(u32 i = 0; i < len; i++) data[i] = b.data[index(i)];
				off = 0;
        return *this;
    }
    buffer(initializer_list<T> il)
    {
    	len = cap = il.size();
    	off = 0;
    	data = new T[cap];
    	u32 i = 0;
    	for(auto it = il.begin();it != il.end(); it++) data[index(i++)] = T(*it);
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

		itr begin()
		{
			return itr(this, 0);
		}
		itr end()
		{
			return itr(this, len);
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
    void push(initializer_list<T> il)
    {
    	u32 i = len;
    	check(len + il.size());
    	len += il.size();
    	for(auto it = il.begin();it != il.end(); it++) data[index(i++)] = T(*it);
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
	void reserve(u32 n)
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
		for(u32 i = 0; i < len; i++) if(func(at(i))) b.data[x++] = data[index(i)];
		b.len = x;
		b.check(b.len);
		return b;
	}

	buffer<T> sort(bool (*func)(const T & t1,const T & t2))
	{
		buffer<T> sb = *this;
		std::sort(sb.data, sb.data + sb.len, func);
		return sb;
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
		for(u32 i = 0; i < b.len; i++) b1.data[x++] = b.data[(i + b.off) % b.cap];

		return b1;
	}



	buffer<T> unique()
	{

		buffer b(len);
		set<T> s;
		u32 x = 0;
		for(u32 i = 0; i < len; i++)
		{
			T & v = at(i);
			if(s.count(v) == 0)
				b.data[x++] = v;
			s.insert(v);
		}
		b.len = x;
		b.check(b.len);
		return b;
	}
	buffer<T> common(const buffer<T> &b)
	{
		set<T> s1;
		for(u32 i = 0; i < len; i++) s1.insert(at(i));
		set<T> s2;
		for(u32 i = 0; i < b.len; i++) s2.insert(b.data[(i + b.off) % b.cap]);
		u32 x = 0;
		buffer b1(len);
		for(T t : s1) if(s2.count(t) == 1) b1[x++] = t;
		b.len = x;
		b1.check(b1.len);
		return b1;
	}

	buffer<T> operator+(const buffer<T> &b)
	{
		return concat(b);
	}
	buffer<T>& operator+=(const buffer<T> &b)
	{
		check(len + b.len);
		u32 x = len;
		for(u32 i = 0; i < b.len; i++) data[index(x++)] = b.data[(i + b.off) % b.cap];
		len += b.len;
		return *this;
	}


private:
	int check(u32 n)
	{

		if(n >= cap)
		{
			if(cap == 0) cap = 2;
			u32 cap2 = cap;
			while(n >= cap2)
				cap2 *= 2;
			T * data2 = new T[cap2];
			for(u32 i = 0; i < len; i++) data2[i] = data[index(i)];
			delete[] data;
			data = data2;
			off = 0;
			cap = cap2;
		}
		else if (len < cap / 2 && len != 0)
		{
			T * data2 = new T[len];
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


template<typename buffer>
class buffer_iterator
{
public:
	using value_type = typename buffer::value_type;
	using difference_type = value_type;
  	using pointer = value_type *;
  	using reference = value_type &;
 	using iterator_category = std::random_access_iterator_tag;
	using ptr_type = value_type *;
	using ref_type = value_type &;

	buffer * buff;
	u32 ind;
public:
	buffer_iterator(buffer* t, u32 i) : buff(t), ind(i)
	{
	}
	~buffer_iterator()
	{
		buff = nullptr;
		ind = 0;
	}
	buffer_iterator& operator++()
	{
		ind++;
		return *this;
	}
	buffer_iterator operator++(int)
	{
		buffer_iterator b(buff, ind);
		++(*this);
		return b;
	}
	buffer_iterator& operator--()
	{
		ind--;
		return *this;
	}
	buffer_iterator operator--(int)
	{
		buffer_iterator b = *this;
		--(*this);
		return b;
	}

	ref_type operator[](u32 i)
	{
		return buff->data[(buff->off + i) % buff->cap];
	}
	ptr_type operator->()
	{
		return buff->data[(buff->off + ind) % buff->cap];
	}
	ref_type operator*()
	{
		return buff->data[(buff->off + ind) % buff->cap];

	}

	buffer_iterator& operator=(const value_type & v) 
	{
	    *this = v;
	    return *this;
	}
	operator const value_type&() const { return buff->data[(buff->off + ind) % buff->cap]; }
	bool operator==(const buffer_iterator& bi) const
	{
		return buff == bi.buff && ind == bi.ind;
	}
	bool operator!=(const buffer_iterator& bi) const
	{
		return !(*this == bi);
	}


		friend value_type operator- (const buffer_iterator& lhs, const buffer_iterator& rhs)
	{
	    return lhs.ind - rhs.ind;
	}

  	friend buffer_iterator operator-(buffer_iterator const& lhs, value_type rhs)
	{
	  return buffer_iterator(lhs.buff,lhs.ind - rhs);
	}

	friend buffer_iterator operator+(buffer_iterator const& lhs, value_type rhs)
	{
	  return buffer_iterator(lhs.buff, lhs.ind + rhs);
	}

	friend buffer_iterator operator+(value_type lhs, buffer_iterator const& rhs)
	{
	  return buffer_iterator(lhs + rhs.ind);
	}

	friend buffer_iterator& operator+= (buffer_iterator& lhs, const buffer_iterator& rhs)
	{
	  lhs.ind += rhs.ind;
	  return lhs;
	}

	friend buffer_iterator& operator-= (buffer_iterator& lhs, const buffer_iterator& rhs)
	{
		lhs.ind -= rhs.ind;
	 	return lhs;
	}
	 friend bool operator<= (const buffer_iterator& lhs, const buffer_iterator& rhs)
    {
        
        return lhs.ind <= rhs.ind;
        
    }

    friend bool operator>= (const buffer_iterator& lhs, const buffer_iterator& rhs)
    {
        
		return lhs.ind >= rhs.ind;
    }

    friend bool operator< (const buffer_iterator& lhs, const buffer_iterator& rhs)
    {
    	return lhs.ind < rhs.ind;
    }
    friend bool operator> (const buffer_iterator& lhs, const buffer_iterator& rhs)
    {
    	return lhs.ind > rhs.ind;
    }



};





template<typename T>
ostream& operator<<(ostream& os, buffer<T> &b)
{
	if(b.len)
	{
		os << "[ ";
		for(u32 i = 0; i < b.len - 1; i++)
		{
			os << b.at(i) << ", ";
		}
		os << b.at(b.len - 1) <<  " ]";
	}
	else
	{
			os << "[ ]";
	}

	return os;
}






typedef buffer<u8> u8buf;
typedef buffer<u32> u32buf;
typedef buffer<u64> u64buf;

typedef buffer<i8> i8buf;
typedef buffer<i32> i32buf;
typedef buffer<i64> i64buf;

typedef buffer<f32> f32buf;
typedef buffer<f64> f64buf;





}; //namespace sp
