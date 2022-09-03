#include <iostream>
#include "sp_gt.hpp"

using namespace std;

using namespace sp;

int main() {
#if 1
	buffer<f32> a = {1.0f, 3.0f, 23.0f};
	buffer<f32> a_copy = a;
	a_copy[2] = 4.2f;

	cout << "a : " << a << endl;
	cout << "a_copy : " << a_copy << endl;

	buffer<i32> b;
	b.push(1);
	b.push({2,2,5,7,3,5,8});
	cout << b << endl;
	b.pop();
	cout << b << endl;
	b.shift(2);
	std::cout << b << endl;
	buffer<i32> c = b.map([](const i32 & v){return v * v;});
	cout << c << endl;
	c.push(20);
	c.push(13);
	c.shift(1);
	cout << c << endl;

	c = c.filter([](const i32 & v){return v % 2 == 1;});
	cout << c << endl;
	c = c.concat(b);
	cout << c << endl;
	c = c.unique();
	cout << c << endl;
	buffer<i32> d = c + b;
	cout << d << endl;
	b += c;
	cout << b << endl;
	c = c.unique();
	cout << c << endl;
	cout << c.front() << " " << c.back() << endl;
	cout << c.at(1) << " " << c[2] << endl;

	cout << c << endl;
	for(i32 i : c) cout << i << " ";
	cout << endl;
	//c = c.sort([](const i32 & a, const i32& b){return a > b;});
	sort(c.begin(), c.end(), [](const i32 & a, const i32& b){return a > b;});
	c.push_front(57);
	c.push_front(7);
	c.push_front(27);
	c.push_front(34);
	c.push_front({1,2,1,1});
	for(buffer<i32>::itr itr = c.begin(); itr != c.end(); itr++)
		cout << *itr << " ";
	cout << endl;
	buffer<i32> e = c.splice(0, 6);
	cout << e << endl;
	e.push_mid(2,{3,3,4});
	cout << e << endl;
#endif

#if 1
	mat<float> m1 = {
		{2.0f, 2.0f, 0.0f},
		{3.0f, 3.0f, 1.0f},
		{0.0f, 3.0f, 0.0f},
	};
	mat<float> m2 = {
		{2.0f, 2.0f, 3.0f},
		{5.0f, 3.0f, 0.0f},
		{1.0f, 1.0f, 1.0f},
	};
	m1 += m2;
	mat<float> m3 = m1 * m2 ;
	cout << m1 << endl;
	cout << m2 << endl;
	cout << m3 << endl;
	cout << m3.cofactor(0,0) << endl << m3.cofactor(0,1) << endl;
	cout << m3.transpose() << endl;
	cout << m3.determinant() << endl;
	cout << m3.inverse() << endl;
	mat<float> m4 =   (m1 + m2) * 10.0 -m3;
	cout << m4 << endl;
	m4 += 10.0;
	cout << m4 << endl;
	m4 *= 10.0;
	cout << m4 << endl;
	m4 /= 2.0;
	cout << m4 << endl;


	vec<float,3> v1 = {1.0f, 1.0f, 0.0f};
	vec<float,3> v2 = {1.0f, 2.0f, 1.0f};


	cout << v1 << endl;
	cout << v1 * m2 << endl;
	cout << m2 * v1 << endl;
	cout << v1.to_mat() << endl;
	cout << v2 << endl;
	cout << v1 + v2 << endl;
	cout << v1 - v2 << endl;
	cout << v1.dot(v2) << endl;
	cout << v1.cross(v2) << endl;
	cout << v1.reflect(v2) << endl;
	vec2 v = vec2_cast(v1);
	cout << v << endl;
#endif




	buffer<int> vs = {0, 1,2,3, 4, 5, 6, 7};

	buffer<graph<int>::edge> es = {
		{0,1},
		{0,2},
		{2,3},
		{2,4},
		{2,6},
		{4,5},
		{1,7},
		{1,4},
		{0,6},
		{7,5}
	};

	graph<int> g(vs, es);
	cout << g << endl;

	





}
