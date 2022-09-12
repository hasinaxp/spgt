#pragma once
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <set>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <string>
#include <memory>

namespace sp
{

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

	template <class>
	class buffer_iterator;

	// storage class , acts as vector and queue
	template <class T>
	class buffer
	{
	public:
		u32 len;
		u32 off;
		u32 cap;
		T *data;

		using value_type = T;
		using itr = buffer_iterator<buffer<T>>;

	public:
		buffer() : len(0), off(0), cap(0), data(nullptr){};

		~buffer()
		{
			len = off = cap = 0;
			if (data)
				delete[] data;
		}
		buffer(u32 n) : len(n), off(0), cap(n), data(nullptr)
		{
			data = new T[cap];
		};
		buffer(const buffer &b) : len(b.len), off(b.off), cap(b.cap), data(nullptr)
		{
			data = new T[cap];
			for (u32 i = 0; i < len; i++)
				data[i] = b.data[index(i)];
			off = 0;
		};
		buffer<T> &operator=(const buffer &b)
		{
			len = b.len;
			off = b.off;
			cap = b.cap;
			if (data)
				delete[] data;
			data = new T[cap];
			for (u32 i = 0; i < len; i++)
				data[i] = b.data[index(i)];
			off = 0;
			return *this;
		}
		buffer(initializer_list<T> il)
		{
			len = cap = il.size();
			off = 0;
			data = new T[cap];
			u32 i = 0;
			for (auto it = il.begin(); it != il.end(); it++)
				data[index(i++)] = *it;
		}
		buffer(const vector<T> &v)
		{
			len = cap = v.size();
			off = 0;
			data = new T[cap];
			for (u32 i = 0; i < len; i++)
				data[i] = v[i];
		}
		buffer<T> &operator=(const vector<T> &v) const
		{
			len = cap = v.size();
			off = 0;
			data = new T[cap];
			for (u32 i = 0; i < len; i++)
				data[i] = v[i];
			return *this;
		}
		T &operator[](u32 i) const
		{
			return data[index(i)];
		}
		T &front() const
		{
			return data[index(0)];
		}
		T &back() const
		{
			return data[index(len - 1)];
		}
		T &at(u32 i) const
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

		T *array(u32 &n)
		{
			T *arr = new T[len];
			for (u32 i = 0; i < len; i++)
				arr[i] = data[index(i)];
			return arr;
		}

		void push(const T &t)
		{
			check(len + 1);
			len++;
			data[index(len - 1)] = t;
		}
		void push(initializer_list<T> il)
		{
			u32 i = len;
			check(len + il.size());
			len += il.size();
			for (auto it = il.begin(); it != il.end(); it++)
				data[index(i++)] = T(*it);
		}
		void push_front(T t)
		{
			check(len + 1);
			len++;
			if (off == 0)
				off = cap;
			off--;
			data[off] = t;
		}
		void push_front(initializer_list<T> il)
		{
			u32 n = il.size();
			check(len + n);
			u32 i = (int)off - n;

			off = cap + i;
			i = 0;
			len += n;
			for (auto it = il.begin(); it != il.end(); it++)
				data[index(i++)] = T(*it);
		}
		void push_mid(const u32 &p, initializer_list<T> il)
		{
			u32 n = il.size();
			check(len + n);

			for (u32 i = len - 1; i >= p; i--)
				data[index(i + p + 1)] = data[index(i)];
			len += n;
			u32 i = p;
			for (auto it = il.begin(); it != il.end(); it++)
				data[index(i++)] = T(*it);
		}
		T pop()
		{
			if (len == 0)
				return T();
			check(len);
			len--;
			return data[index(len)];
		}
		void shift(u32 n = 1)
		{
			if (n >= len)
				return;
			off += n;
			len -= n;
			check(len);
		}
		void reserve(u32 n)
		{
			check(n);
		}
		void resize(u32 n, const T &t = T())
		{
			check(n);

			if (len < n)
			{
				for (u32 i = len; i <= n - len; i++)
					data[index(len + i)] = t;
			}
			len = n;
		}
		void del(const u32 &i)
		{
			data[index(i)] = data[index(len - 1)];
			len--;
			check(len);
		}
		void fill(const T &t)
		{
			for (u32 i = 0; i < len; i++)
				data[index(i)] = t;
		}
		buffer<T> splice(u32 b, u32 e)
		{
			if (b >= e)
				return buffer<T>();
			buffer<T> bf(e - b);
			u32 x = 0;
			for (u32 i = b; i < e; i++)
				bf.data[x++] = data[index(i)];
			return bf;
		}
		buffer<T> map(T (*func)(const T &t))
		{
			buffer b(len);
			for (u32 i = 0; i < len; i++)
				b.data[i] = func(at(i));
			return b;
		}
		buffer<T> filter(bool (*func)(const T &t))
		{
			buffer b(len);
			u32 x = 0;
			for (u32 i = 0; i < len; i++)
				if (func(at(i)))
					b.data[x++] = data[index(i)];
			b.len = x;
			b.check(b.len);
			return b;
		}

		buffer<T> sort(bool (*func)(const T &t1, const T &t2))
		{
			buffer<T> sb = *this;
			std::sort(sb.data, sb.data + sb.len, func);
			return sb;
		}

		i32 indexOf(const T &t)
		{
			for (u32 i = 0; i < len; i++)
				if (t == at(i))
					return i;
			return -1;
		}

		buffer<T> concat(const buffer<T> &b) const
		{
			buffer<T> b1(len + b.len);
			u32 x = 0;
			for (u32 i = 0; i < len; i++)
				b1.data[x++] = at(i);
			for (u32 i = 0; i < b.len; i++)
				b1.data[x++] = b.data[(i + b.off) % b.cap];

			return b1;
		}

		buffer<T> unique()
		{

			buffer b(len);
			set<T> s;
			u32 x = 0;
			for (u32 i = 0; i < len; i++)
			{
				T &v = at(i);
				if (s.count(v) == 0)
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
			for (u32 i = 0; i < len; i++)
				s1.insert(at(i));
			set<T> s2;
			for (u32 i = 0; i < b.len; i++)
				s2.insert(b.data[(i + b.off) % b.cap]);
			u32 x = 0;
			buffer b1(len);
			for (T t : s1)
				if (s2.count(t) == 1)
					b1[x++] = t;
			b.len = x;
			b1.check(b1.len);
			return b1;
		}

		buffer<T> operator+(const buffer<T> &b) const
		{
			return concat(b);
		}
		buffer<T> &operator+=(const buffer<T> &b)
		{
			check(len + b.len);
			u32 x = len;
			for (u32 i = 0; i < b.len; i++)
				data[index(x++)] = b.data[(i + b.off) % b.cap];
			len += b.len;
			return *this;
		}

	private:
		int check(u32 n)
		{

			if (n >= cap)
			{
				if (cap == 0)
					cap = 2;
				u32 cap2 = cap;
				while (n >= cap2)
					cap2 *= 2;
				T *data2 = new T[cap2];
				for (u32 i = 0; i < len; i++)
					data2[i] = data[index(i)];
				delete[] data;
				data = data2;
				off = 0;
				cap = cap2;
			}
			else if (len < cap / 2 && len != 0)
			{
				T *data2 = new T[len];
				for (u32 i = 0; i < len; i++)
					data2[i] = data[index(i)];
				delete[] data;
				data = data2;
				off = 0;
				cap = len;
			}

			return (off + len - 1) % cap;
		}

		int index(int i) const
		{
			return (i + off) % cap;
		}

	}; // buffer

	template <typename buffer>
	class buffer_iterator
	{
	public:
		using value_type = typename buffer::value_type;
		using difference_type = i32;
		using pointer = value_type *;
		using reference = value_type &;
		using iterator_category = std::random_access_iterator_tag;
		using ptr_type = value_type *;
		using ref_type = value_type &;

		buffer *buff;
		u32 ind;

	public:
		buffer_iterator(buffer *t, u32 i) : buff(t), ind(i)
		{
		}
		~buffer_iterator()
		{
			buff = nullptr;
			ind = 0;
		}
		buffer_iterator &operator++()
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
		buffer_iterator &operator--()
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

		buffer_iterator &operator=(const value_type &v)
		{
			*this = v;
			return *this;
		}
		operator const value_type &() const { return buff->data[(buff->off + ind) % buff->cap]; }
		bool operator==(const buffer_iterator &bi) const
		{
			return buff == bi.buff && ind == bi.ind;
		}
		bool operator!=(const buffer_iterator &bi) const
		{
			return !(*this == bi);
		}

		friend value_type operator-(const buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			return lhs.ind - rhs.ind;
		}

		friend buffer_iterator operator-(buffer_iterator const &lhs, difference_type rhs)
		{
			return buffer_iterator(lhs.buff, lhs.ind - rhs);
		}

		friend buffer_iterator operator+(buffer_iterator const &lhs, difference_type rhs)
		{
			return buffer_iterator(lhs.buff, lhs.ind + rhs);
		}

		friend buffer_iterator operator+(value_type lhs, buffer_iterator const &rhs)
		{
			return buffer_iterator(lhs + rhs.ind);
		}

		friend buffer_iterator &operator+=(buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			lhs.ind += rhs.ind;
			return lhs;
		}

		friend buffer_iterator &operator+=(buffer_iterator &lhs, const difference_type &rhs)
		{
			lhs.ind += rhs;
			return lhs;
		}

		friend buffer_iterator &operator-=(buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			lhs.ind -= rhs;
			return lhs;
		}
		friend bool operator<=(const buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			return lhs.ind <= rhs.ind;
		}

		friend bool operator>=(const buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			return lhs.ind >= rhs.ind;
		}

		friend bool operator<(const buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			return lhs.ind < rhs.ind;
		}
		friend bool operator>(const buffer_iterator &lhs, const buffer_iterator &rhs)
		{
			return lhs.ind > rhs.ind;
		}

	}; // buffer_iterator

	template <typename T>
	ostream &operator<<(ostream &os, const buffer<T> &b)
	{
		if (b.len)
		{
			os << "[ ";
			for (u32 i = 0; i < b.len - 1; i++)
			{
				os << b.at(i) << ", ";
			}
			os << b.at(b.len - 1) << " ]";
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

	template <class, u32>
	class vec;

	template <class T>
	class mat
	{
	public:
		buffer<T> data;
		u32 row;
		u32 col;

	public:
		mat() : data(buffer<T>()), row(0), col(0)
		{
		}
		mat(u32 R, u32 C, bool identity = true) : data(buffer<T>(R * C)), row(R), col(C)
		{
			u32 off = 0;
			if (identity && R == C)
			{
				for (u32 r = 0; r < R; r++)
				{
					for (u32 c = 0; c < C; c++)
					{
						data[off + c] = (r == c ? T(1) : T(0));
					}
					off += col;
				}
			}
			else
			{
				for (u32 i = 0; i < R * C; i++)
				{
					data[i] = T(0);
				}
			}
		}
		mat(mat &m) : data(m.data), row(m.row), col(m.col)
		{
		}
		mat &operator=(const mat &m)
		{
			data = m.data;
			row = m.row;
			col = m.col;
			return *this;
		}
		mat(initializer_list<initializer_list<T>> il)
		{
			u32 i = 0;
			row = il.size();
			col = il.begin()->size();
			data = buffer<T>(row * col);
			for (auto it = il.begin(); it != il.end(); it++)
			{
				if (col != it->size())
				{
					data = buffer<T>();
					row = 0;
					col = 0;
					return;
				}
				for (auto it2 = it->begin(); it2 != it->end(); it2++)
					data[i++] = T(*it2);
			}
		}

		T *operator[](u32 i) const
		{
			return &data[i * col];
		}
		T *at(u32 i) const
		{
			return &data[i * col];
		}
		T &at(u32 i, u32 j) const
		{
			return data[i * col + j];
		}
		mat operator+(const mat &m) const
		{
			if (!(m.row == row && m.col == col))
				return mat();
			mat o(row, col);
			u32 off = 0;

			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					o.data[off + c] = m.data[off + c] + data[off + c];
				}
				off += row;
			}
			return o;
		}
		mat operator-(const mat &m) const
		{
			if (!(m.row == row && m.col == col))
				return mat();
			mat o(row, col);
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					o.data[off + c] = data[off + c] - m.data[off + c];
				}
				off += col;
			}
			return o;
		}
		mat operator*(const mat &m) const
		{

			if (!(col == m.row))
				return mat();
			mat o(row, m.col);

			for (u32 y = 0; y < o.row; y++)
				for (u32 x = 0; x < o.col; x++)
				{
					T result = T();
					for (u32 k = 0; k < col; k++)
						result += data[y * col + k] * m.data[m.col * k + x];
					o.data[y * o.col + x] = result;
				}
			return o;
		}

		mat &operator+=(const mat &m)
		{
			if (!(m.row == row && m.col == col))
				return *this;
			u32 off = 0;

			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] += m.data[off + c];
				}
				off += row;
			}
			return *this;
		}
		mat &operator-=(const mat &m)
		{
			if (!(m.row == row && m.col == col))
				return *this;
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] -= m.data[off + c];
				}
				off += col;
			}
			return *this;
		}
		mat &operator*=(const mat &m)
		{

			if (!(col == m.row))
				return *this;
			mat o(row, m.col);

			for (u32 y = 0; y < o.row; y++)
				for (u32 x = 0; x < o.col; x++)
				{
					T result = T();
					for (u32 k = 0; k < col; k++)
						result += data[y * col + k] * m.data[m.col * k + x];
					o.data[y * o.col + x] = result;
				}
			data = o.data;
			return *this;
		}

		mat operator+(const T &t) const
		{
			mat o(row, col);
			u32 off = 0;

			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					o.data[off + c] = t + data[off + c];
				}
				off += row;
			}
			return o;
		}
		mat operator-(const T &t) const
		{
			mat o(row, col);
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					o.data[off + c] = data[off + c] - t;
				}
				off += col;
			}
			return o;
		}
		mat operator*(const T &t) const
		{

			mat o(row, row);

			for (u32 y = 0; y < o.row; y++)
				for (u32 x = 0; x < o.col; x++)
				{
					o.data[y * col + x] = data[y * col + x] * t;
				}
			return o;
		}
		mat operator/(const T &t) const
		{
			if (t == T(0))
				return mat();
			mat o(row, col);

			for (u32 y = 0; y < o.row; y++)
				for (u32 x = 0; x < o.col; x++)
				{
					o.data[y * col + x] = data[y * col + x] / t;
				}
			return o;
		}

		mat &operator+=(const T &t)
		{
			u32 off = 0;

			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] += t;
				}
				off += row;
			}
			return *this;
		}
		mat &operator-=(const T &t)
		{
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] -= t;
				}
				off += col;
			}
			return *this;
		}
		mat &operator*=(const T &t)
		{
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] *= t;
				}
				off += col;
			}
			return *this;
		}
		mat &operator/=(const T &t)
		{
			if (t == T(0))
				return *this;
			u32 off = 0;
			for (u32 r = 0; r < row; r++)
			{
				for (u32 c = 0; c < col; c++)
				{
					data[off + c] /= t;
				}
				off += col;
			}
			return *this;
		}

		mat map(T (*func)(const T &t))
		{
			mat o(row, col);
			for (u32 i = 0; i < row * col; i++)
			{
				o.data[i] = func(data[i]);
			}
			return o;
		}

		mat transpose() const
		{
			mat o(col, row);
			for (u32 y = 0; y < row; y++)
				for (u32 x = 0; x < col; x++)
				{
					o.data[x * row + y] = data[y * col + x];
				}
			return o;
		}
		mat cofactor(u32 r, u32 c) const
		{
			mat o(col - 1, row - 1);
			u32 i = 0;
			for (u32 y = 0; y < row; y++)
				for (u32 x = 0; x < col; x++)
				{
					if (x == c || y == r)
						continue;
					o.data[i++] = data[y * col + x];
				}

			return o;
		}
		T determinant() const
		{
			if (row != col)
				return T(0);
			T o = T();
			if (row == 1)
			{
				return data[0];
			}
			else
			{
				i32 sign = 1;
				for (u32 x = 0; x < col; x++)
				{
					o += sign * data[x] * cofactor(0, x).determinant();
					sign *= -1;
				}
			}

			return o;
		}
		mat adjoint() const
		{
			if (row == col)
				return mat();
			mat o(col, row);
			i32 sign = 1;
			for (u32 y = 0; y < row; y++)
				for (u32 x = 0; x < col; x++)
				{
					o.data[y * col + x] = sign * cofactor(y, x).determinant();
					sign *= -1;
				}
			o = o.transpose();

			return o;
		}

		mat inverse() const
		{
			mat adj = adjoint();
			T d = determinant();
			if (d == T(0))
				return mat();
			for (u32 y = 0; y < adj.col; y++)
				for (u32 x = 0; x < adj.row; x++)
				{
					adj.data[y * adj.col + x] = adj.data[y * adj.col + x] / d;
				}
			return adj;
		}
		
	};

	inline mat<float> mat4_identity()
	{
		return mat<float>(4, 4);
	}
	inline mat<float> mat3_identity()
	{
		return mat<float>(3, 3);
	}
	inline mat<float> mat2_identity()
	{
		return mat<float>(2, 2);
	}

	typedef mat<float> matrix;

	template <class T>
	ostream &operator<<(ostream &os, const mat<T> &m)
	{
		u32 off = 0;
		for (u32 r = 0; r < m.row; r++)
		{
			for (u32 c = 0; c < m.col; c++)
			{
				os << m.data[off + c] << " ";
			}
			off += m.col;
			os << "\n";
		}
		return os;
	}

	template <class T, u32 N>
	class vec
	{
	public:
		T data[N];

	public:
		vec()
		{
			for (u32 i = 0; i < N; i++)
				data[i] = T(0);
		}
		vec(vec &v)
		{
			for (u32 i = 0; i < N; i++)
				data[i] = v.data[i];
		}
		vec(const T &x, const T &y)
		{
			if (N < 2)
				return;
			data[0] = x;
			data[1] = y;
		}
		vec(const T &x, const T &y, const T &z)
		{
			if (N < 3)
				return;
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}
		vec(const T &x, const T &y, const T &z, const T &w)
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}
		vec(const T &t)
		{
			for (u32 i = 0; i < N; i++)
				data[i] = t;
		}
		vec &operator=(const vec<T, N> &v)
		{
			for (u32 i = 0; i < N; i++)
				data[i] = v.data[i];
			return *this;
		}

		vec(initializer_list<T> il)
		{
			u32 i = 0;
			for (auto it = il.begin(); it != il.end(); it++)
				data[i++] = *it;
		}

		T &at(u32 i) const
		{
			return data[i];
		}

		T &operator[](const u32 &i)
		{
			return data[i];
		}
		T operator[](const u32 &i) const
		{
			return data[i];
		}

		bool operator==(const vec<T, N> &v) const
		{
			for (u32 i = 0; i != N; i++)
				if (data[i] != v.data[i])
					return false;
			return true;
		}
		bool operator!=(const vec<T, N> &v) const
		{
			return !(*this == v);
		}

		vec operator+(const vec<T, N> &v)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = v.data[i] + data[i];
			return o;
		}
		vec operator-(const vec<T, N> &v)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = data[i] - v.data[i];
			return o;
		}

		vec operator-()
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = -data[i];
			return o;
		}
		vec operator*(const vec<T, N> &v)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = v.data[i] * data[i];
			return o;
		}

		vec &operator+=(const vec<T, N> &v)
		{
			for (u32 i = 0; i < N; i++)
				data[i] += v.data[i];
			return *this;
		}
		vec &operator-=(const vec<T, N> &v)
		{
			for (u32 i = 0; i < N; i++)
				data[i] -= v.data[i];
			return *this;
		}
		vec &operator*=(const vec<T, N> &v)
		{
			for (u32 i = 0; i < N; i++)
				data[i] *= v.data[i];
			return *this;
		}

		vec operator+(const T &t)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = t + data[i];
			return o;
		}
		vec operator-(const T &t)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = data[i] - t;
			return o;
		}
		vec operator*(const T &t)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = t * data[i];
			return o;
		}

		vec operator/(const T &t)
		{
			vec o;
			for (u32 i = 0; i < N; i++)
				o.data[i] = data[i] / t;
			return o;
		}

		vec &operator+=(const T &t)
		{
			for (u32 i = 0; i < N; i++)
				data[i] += t;
			return *this;
		}
		vec &operator-=(const T &t)
		{
			for (u32 i = 0; i < N; i++)
				data[i] -= t;
			return *this;
		}
		vec &operator*=(const T &t)
		{
			for (u32 i = 0; i < N; i++)
				data[i] *= t;
			return *this;
		}
		vec &operator/=(const T &t)
		{
			if (t == T(0))
				return vec();
			for (u32 i = 0; i < N; i++)
				data[i] /= t;
			return *this;
		}

		T len()
		{
			T m(0);
			for (u32 i = 0; i < N; i++)
				m += data[i] * data[i];
			return sqrt(m);
		}
		void norm()
		{
			T l = len();
			if (l)
				for (u32 i = 0; i < N; i++)
					data[i] /= l;
		}
		T dot(const vec &v) const
		{
			T x(0);
			for (u32 i = 0; i < N; i++)
				x += data[i] * v.data[i];
			return x;
		}
		vec cross(const vec &v)
		{
			if (N != 3)
				return vec(T(0));
			vec o;
			o.data[0] = data[1] * v.data[2] - data[2] * v.data[1];
			o.data[1] = data[2] * v.data[0] - data[0] * v.data[2];
			o.data[2] = data[0] * v.data[1] - data[1] * v.data[0];

			return o;
		}
		vec reflect(const vec &v)
		{
			vec o;
			T d = dot(v) * T(2);
			for (u32 i = 0; i < N; i++)
				o.data[i] = data[i] - d * v.data[i];
			return o;
		}
		mat<T> to_mat() const
		{
			mat<T> m(N, 1);
			for (u32 i = 0; i < N; i++)
				m.data[i] = data[i];
			return m;
		}
	};

	typedef vec<float, 2> vec2;
	typedef vec<float, 3> vec3;
	typedef vec<float, 4> vec4;

	inline vec2 vec2_cast(vec3 &v)
	{
		vec2 o = {v.data[0], v.data[1]};
		return o;
	}
	inline vec2 vec2_cast(vec4 &v)
	{
		vec2 o = {v.data[0], v.data[1]};
		return o;
	}
	inline vec3 vec3_cast(vec2 &v)
	{
		vec3 o = {v.data[0], v.data[1], 0.0f};
		return o;
	}
	inline vec3 vec3_cast(vec4 &v)
	{
		vec3 o = {v.data[0], v.data[1], v.data[1]};
		return o;
	}
	inline vec4 vec4_cast(vec3 &v)
	{
		vec4 o = {v.data[0], v.data[1], v.data[1]};
		return o;
	}
	inline vec4 vec4_cast(vec2 &v)
	{
		vec4 o = {v.data[0], v.data[1], 0.0f, 0.0f};
		return o;
	}

	template <class T, u32 N>
	ostream &operator<<(ostream &os, const vec<T, N> &v)
	{
		os << "( ";
		for (u32 i = 0; i < N - 1; i++)
			os << v.data[i] << ", ";
		os << v.data[N - 1] << " )";
		return os;
	}

	// function to find the inverse square root
	inline f32 inverse_sqrt(f32 number)
	{
		const f32 threehalfs = 1.5F;

		f32 x2 = number * 0.5F;
		f32 y = number;
		long i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(f32 *)&i;
		y = y * (threehalfs - (x2 * y * y));

		// 2nd iteration, this can be removed
		// y = y * ( threehalfs - ( x2 * y * y ) );

		return y;
	}

	template <class T, u32 N>
	vec<T, N> operator*(const vec<T, N> &v, const mat<T> &m)
	{
		mat<T> m1 = v.to_mat();
		m1 = m1.transpose() * m;
		if (m1.row == 0 && m1.col == 0)
			return vec<T, N>();
		vec<T, N> o;
		for (u32 i = 0; i < N; i++)
			o.data[i] = m1.data[i];
		return o;
	}

	template <class T, u32 N>
	vec<T, N> operator*(const mat<T> &m, const vec<T, N> &v)
	{
		mat<T> m1 = v.to_mat();
		m1 = m * m1;
		if (m1.row == 0 && m1.col == 0)
			return vec<T, N>();
		vec<T, N> o;
		for (u32 i = 0; i < N; i++)
			o.data[i] = m1.data[i];
		return o;
	}

	template <class>
	class dfs_iterator;

	template <class>
	class bfs_iterator;

	template <class T>
	class graph
	{
	public:
		using value_type = T;
		using edge = vec<u32, 2>;
		using path = buffer<u32>;
		using dfs_itr = dfs_iterator<graph<T>>;
		using bfs_itr = bfs_iterator<graph<T>>;
		buffer<T> verts;
		buffer<edge> edges;
		buffer<f32> costs;
		bool directed = false;

	public:
		graph() : verts(buffer<T>()), edges(buffer<edge>()), costs(buffer<f32>())
		{
		}

		graph(const buffer<T> &vs, const buffer<edge> &es, const buffer<f32> &cs = buffer<f32>())
		{
			verts = vs;
			edges = es;
			costs = cs;
			costs.resize(edges.len, 1.0f);
		}

		graph(const graph &g) : verts(g.verts), edges(g.edges), costs(g.costs)
		{
		}

		graph &operator=(const graph &g)
		{
			verts = g.verts;
			edges = g.edges;
			costs = g.costs;

			return *this;
		}

		void add_vert(const T &v)
		{
			verts.push(v);
		}

		void add_edge(const edge &e, f32 cost = 1.0f)
		{
			edges.push(e);
			costs.push(cost);
		}

		void del_edge(const edge &e)
		{
			i32 i = edges.indexOf(e);
			if (i != -1)
			{
				edges.del((u32)i);
				costs.del((u32)i);
			}
		}

		buffer<u32> adj_verts(u32 r)
		{
			buffer<u32> vs;
			for (const edge &e : edges)
			{
				if (e[0] == r)
					vs.push(e[1]);
				if (e[1] == r)
					vs.push(e[0]);
			}
			return vs.unique();
		}

		mat<f32> adj_mat() const
		{
			mat<f32> m(verts.len, verts.len, false);

			for (u32 i = 0; i < edges.len; i++)
			{
				edge &e = edges[i];
				f32 &c = costs[i];
				m[e[0]][e[1]] = c;
			}
			if (!directed)
			{
				for (u32 i = 0; i < edges.len; i++)
				{
					edge &e = edges[i];
					f32 &c = costs[i];
					m[e[1]][e[0]] = c;
				}
			}

			return m;
		}
	};

	template <typename graph>
	class dfs_iterator
	{
	public:
		using value_type = typename graph::value_type;
		using difference_type = i32;
		using pointer = value_type *;
		using reference = value_type &;
		using iterator_category = std::forward_iterator_tag;
		using ptr_type = value_type *;
		using ref_type = value_type &;

		graph *gp;
		u32 root;
		buffer<u32> verts_to_visit;
		buffer<u32> current_path;
		set<u32> verts_visited;

	public:
		dfs_iterator() : gp(nullptr), root(0), verts_to_visit(buffer<u32>()), current_path(buffer<u32>()), verts_visited({})
		{
		}
		dfs_iterator(graph *g, u32 r) : gp(g), root(r), verts_to_visit(buffer<u32>()), current_path(buffer<u32>()), verts_visited({})
		{
		}
		dfs_iterator(const dfs_iterator &d)
		{
			gp = d.gp;
			root = d.root;
			verts_to_visit = d.verts_to_visit;
			verts_visited = d.verts_visited;
		}
		~dfs_iterator()
		{
			gp = nullptr;
			root = 0;
		}
		dfs_iterator &operator++()
		{
			if (verts_visited.size() == gp->verts.len)
				return *this;
			verts_visited.insert(root);
			current_path.push(root);
			buffer<u32> vs0 = gp->adj_verts(root);
			if (vs0.len == 0)
				current_path.pop();

			u32 n = root;
			bool b = true;
			if (verts_to_visit.len == 0)
			{
				b = false;
				verts_to_visit = vs0;
			}
			while (verts_visited.count(n) && verts_to_visit.len)
			{
				n = verts_to_visit.pop();
			}
			if (b)
			{
				for (const u32 &v : vs0)
					verts_to_visit.push(v);
			}
			buffer<u32> vs = gp->adj_verts(n);
			for (const u32 &v : vs)
				verts_to_visit.push(v);
			root = n;

			return *this;
		}
		dfs_iterator operator++(int)
		{
			dfs_iterator d(*this);
			++(*this);
			return d;
		}
		ptr_type operator->()
		{
			return &gp->verts[root];
		}
		ref_type operator*()
		{
			return gp->verts[root];
		}

		dfs_iterator &operator=(const value_type &v)
		{
			*this = v;
			return *this;
		}
		operator const value_type &() const { return gp->verts[root]; }
		bool operator==(const dfs_iterator &bi) const
		{
			return gp == bi.gp && root == bi.root;
		}
		bool operator!=(const dfs_iterator &bi) const
		{
			return !(*this == bi);
		}

	}; // buffer_iterator

	template <typename graph>
	class bfs_iterator
	{
	public:
		using value_type = typename graph::value_type;
		using difference_type = i32;
		using pointer = value_type *;
		using reference = value_type &;
		using iterator_category = std::forward_iterator_tag;
		using ptr_type = value_type *;
		using ref_type = value_type &;

		graph *gp;
		u32 root;
		buffer<u32> verts_to_visit;
		set<u32> verts_visited;

	public:
		bfs_iterator() : gp(nullptr), root(0), verts_to_visit(buffer<u32>()), verts_visited({})
		{
		}
		bfs_iterator(graph *g, u32 r) : gp(g), root(r), verts_to_visit(buffer<u32>()), verts_visited({})
		{
		}
		bfs_iterator(const bfs_iterator &d)
		{
			gp = d.gp;
			root = d.root;
			verts_to_visit = d.verts_to_visit;
			verts_visited = d.verts_visited;
		}
		~bfs_iterator()
		{
			gp = nullptr;
			root = 0;
		}
		bfs_iterator &operator++()
		{
			if (verts_visited.size() == gp->verts.len)
				return *this;

			verts_visited.insert(root);
			buffer<u32> vs0 = gp->adj_verts(root);

			for (const u32 &v : vs0)
				if (verts_visited.count(v) == 0 && verts_to_visit.indexOf(v) == -1)
					verts_to_visit.push(v);
			if (verts_to_visit.len)
			{

				root = verts_to_visit.front();
				verts_to_visit.shift(1);
			}

			return *this;
		}
		bfs_iterator operator++(int)
		{
			bfs_iterator d(*this);
			++(*this);
			return d;
		}
		ptr_type operator->()
		{
			return &gp->verts[root];
		}
		ref_type operator*()
		{
			return gp->verts[root];
		}

		bfs_iterator &operator=(const value_type &v)
		{
			*this = v;
			return *this;
		}
		operator const value_type &() const { return gp->verts[root]; }
		bool operator==(const bfs_iterator &bi) const
		{
			return gp == bi.gp && root == bi.root;
		}
		bool operator!=(const bfs_iterator &bi) const
		{
			return !(*this == bi);
		}

	}; // buffer_iterator

	template <typename T>
	ostream &operator<<(ostream &os, const graph<T> &g)
	{

		os << g.adj_mat();

		return os;
	}

	inline matrix translation_matrix(f32 x, f32 y, f32 z)
		{
			mat<float> m = {
					{1, 0, 0, x},
					{0, 1, 0, y},
					{0, 0, 1, z},
					{0, 0, 0, 1}};
			return m;
		}
		inline matrix scale_matrix(f32 x, f32 y, f32 z)
		{
			mat<float> m = {
					{x, 0, 0, 0},
					{0, y, 0, 0},
					{0, 0, z, 0},
					{0, 0, 0, 1}};
			return m;
		}
		inline matrix rotation_matrix(f32 x, f32 y, f32 z, f32 angle)
		{
			f32 l = sqrt(x * x + y * y + z * z);
			x /= l;
			y /= l;
			z /= l;
			f32 s = sin(angle);
			f32 c = cos(angle);

			mat<float> m = {
					{(c + x * x * (1 - c)), (x * y * (1 - c) - z * s), (x * z * (1 - c) + y * s), 0},
					{(y * x * (1 - c) + z * s), (c + y * y * (1 - c)), (y * z * (1 - c) - x * s), 0},
					{(z * x * (1 - x) - y * s), (z * y * (1 - c) + x * s), (c + z * z * (1 - c)), 0},
					{0, 0, 0, 1}};
			return m;
		}

	inline matrix perspective_projection_matrix(f32 fov, f32 width, f32 height, f32 near = 0.1f, f32 far = 100.0f)
	{
		f32 aspect = width / height;
		f32 f1 = tan(pi * 0.5 - 0.5 * fov);
		f32 rangeInv = (1.0f / (near - far));

		matrix m = {
				{f1 / aspect, 0, 0, 0},
				{0, f1, 0, 0},
				{0, 0, (near + far) * rangeInv, near * far * rangeInv * 2},
				{0, 0, -1, 0}};
		return m;
	}
	inline matrix orthogonal_projection_matrix(f32 left, f32 top, f32 right, f32 bottom, f32 near = 0.1f, f32 far = 10.0f)
	{
		matrix m = {
				{2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left)},
				{0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom)},
				{0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near)},
				{0.0f, 0.0f, 0.0f, 1.0f}};
		return m;
	}

	inline matrix look_at_matrix(vec3 pos, vec3 target_pos,  vec3 up)
	{

		vec3 zaxis = pos - target_pos;
		zaxis.norm();
		vec3 xaxis = up.cross(zaxis);
		xaxis.norm();
		vec3 yaxis = zaxis.cross(xaxis);
		yaxis.norm();

		matrix m = {
				{xaxis[0], yaxis[0], zaxis[0], pos[0]},
				{xaxis[1], yaxis[1], zaxis[1], pos[1]},
				{xaxis[1], yaxis[1], zaxis[1], pos[1]},
				{0, 0, 0, 1}};

		return m;
	}

}; // namespace sp
