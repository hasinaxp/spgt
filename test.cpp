#include <iostream>
#include "sp_gt.hpp"

using namespace std;

using namespace sp;

int main() {

	buffer<f32> a = {1.0f, 3.0f, 23.0f};
	buffer<f32> a_copy = a;
	a_copy[2] = 4.2f;

	cout << "a : " << a << endl;
	cout << "a_copy : " << a_copy << endl;

	buffer<i32> b = buffer<i32>();
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
	sort(c.begin(), c.end(),[](const i32 & a, const i32& b){return a > b;});
	for(buffer<i32>::itr itr = c.begin(); itr != c.end(); itr++)
		cout << *itr << " ";
	cout << endl;

}
