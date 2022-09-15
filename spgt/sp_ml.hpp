#pragma once
#include "sp_math.hpp"
#include <functional>

namespace sp
{
	using namespace std;
	static u32 layer_generation_id = 0;
	typedef pair<function<f32(const f32 &)>, function<f32(const f32 &)>> activation_function;

	namespace activation_functions
	{
		const activation_function linear =
				{
						[](const f32 &x)
						{ return x; },
						[](const f32 &y)
						{ return 1.0f; }};
		const activation_function sigmoid =
				{
						[](const f32 &x)
						{ return 1.0f / (1 + powf(sym::e, -x)); },
						[](const f32 &y)
						{ return y * (1.0f - y); }};
		const activation_function tanh =
				{
						[](const f32 &x)
						{ return tanhf(x); },
						[](const f32 &y)
						{ return 1.0 - y * y; }};
		const activation_function relu =
				{
						[](const f32 &x)
						{ return x < 0.0f ? 0.0f : x; },
						[](const f32 &y)
						{ return y < 0.0f ? 0.0f : 1.0f; }};

	};

	class layer
	{
	public:
		buffer<layer *> connections_from;
		buffer<layer *> connections_to;
		bool trainable = true;
		int id;

	public:
		layer() : connections_from(buffer<layer *>()), connections_to(buffer<layer *>()), id(++layer_generation_id)
		{
		}
		virtual void exec(const matrix &input, matrix &output) {}
		virtual void update(const matrix &dweights) {}
		virtual void configure() {};
		virtual matrix to_matrix()
		{
			matrix m;
			return m;
		}
	};

	class dense_layer : public layer
	{
	public:
		buffer<matrix> weights;
		buffer<matrix> biases;
		matrix vals;
		u32 size;
		activation_function activaion;

	private:
		dense_layer(const u32 &n) : size(n), activaion(activation_functions::sigmoid)
		{
			vals = matrix(1, n);
		};
		dense_layer(const u32 &n, activation_function af) : size(n), activaion(af)
		{
			vals = matrix(1, n);
		};
		~dense_layer(){};
		void exec(const matrix &input, matrix &output) override
		{
			output = input * weights;
			output += biases;
			output = output.map(activaion.first);
		}
		void update(const matrix &dweights) override
		{
			weights += dweights;
		}
		matrix to_matrix() override
		{
			return vals;
		}
		void connect(dense_layer &d)
		{
			d.connections_from.push(this);
			connections_to.push(&d);
		}
		void configure()
		{

		}
	};

	class input_layer : public layer
	{
	public:
		u32 size;

	public:
		input_layer(u32 s) : size(s)
		{
		}

		matrix to_matrix(float *data)
		{
			matrix m(1, size);
			sp_range(size)
			{
				m.data.data[i] = data[i];
			}
			return matrix();
		}

		void exec(const matrix &input, matrix &output) override
		{
		}

		void connect(dense_layer &d)
		{
			d.connections_from.push(this);
			connections_to.push(&d);
		}
	};

	class model
	{
	public:
		buffer<input_layer *> inlayers;
		layer *outlayer;

	public:
		model(input_layer *il, layer *ol) : inlayers({il}), outlayer(ol)
		{
		}

		bool compile()
		{
			layer *

			return true;
		}
		buffer<matrix> predict(f32 *data, u32 size)
		{
			u32 input_size = 0;

			sp_for(il, inlayers)
			{
				input_size++;
			}

			u32 n = size / input_size;

			buffer<matrix> output(n);

			sp_range(n)
			{
				u32 offset = 0;
				sp_for(il, inlayers)
				{
					matrix a = il->to_matrix(data);
					data += il->size;

					sp_for(l, il->connections_to)
					{
						feed_forword(l, a);
					}
				}
				output[i] = outlayer->to_matrix();
			}
			return output;
		}

	private:
		void feed_forword(layer *l, const matrix &a)
		{
			matrix b;
			l->exec(a, b);
			sp_for(conn, l->connections_to)
					feed_forword(conn, b);
		}
	};

} //namespace sp
