#include "sp_math.hpp"

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
		bool trainable = false;
		u32 id;
		buffer<u32> shape;

	public:
		layer() : connections_from(buffer<layer *>()), connections_to(buffer<layer *>()), id(++layer_generation_id), shape(buffer<u32>())
		{
		}

		virtual void exec(const matrix &imat, matrix &omat)
		{
		}
		virtual matrix update(const matrix &errors, f32 * params)
		{
		}
		virtual matrix calc_error(matrix & err)
		{
			matrix m;
			return m;
		}
		virtual matrix to_matrix()
		{
			matrix m;
			return m;
		}
	};

	class input_layer : public layer
	{
	public:
		u32 size;

	public:
		input_layer(u32 sz) : size(sz)
		{
		}
		matrix to_matrix(f32 *data)
		{
			matrix m(1, size);
			sp_range(size)
					m.data.data[i] = data[i];
			return m;
		}
	};

	class dense_layer : public layer
	{
	public:
		u32 size;
		activation_function activation;
		matrix weights;
		matrix biases;
		matrix values;
		matrix activated_values;
		bool connected = false;

	public:
		dense_layer(u32 n, activation_function af = activation_functions::sigmoid) : size(n), activation(af)
		{
		}

		void exec(const matrix &imat, matrix &omat) override
		{

			omat = imat * weights;
			omat += biases;
			activated_values = omat.map(activation.first);
			values = imat;
			// cout <<"weights\n" << weights << endl;
			// cout <<"biases\n" << biases << endl;
			// cout <<"vals:\n" << values << endl;
			// cout <<"act vals:\n" << activated_values << endl;
		}
		matrix update(const matrix & err, f32 *params) override
		{
			matrix e2 = err * weights.transpose();
			f32 lr = params[0];
			matrix ddx = activated_values.map(activation.second);
			matrix grad = err.multiply_elements(ddx) * lr;
			matrix dw = values.transpose() * grad;
			weights += dw;	
			biases += grad;
			return e2;
		}
		matrix to_matrix() override
		{
			return activated_values;
		}
		void connect(input_layer *ilp)
		{
			if (!connected)
			{
				shape = {1, size};
				ilp->connections_to.push(this);
				connections_from.push(ilp);
				weights = matrix(ilp->size, size);
				biases = matrix(1, ilp->size);
				u32 nw = weights.col * weights.row;
				sp_range(nw)
						weights.data.data[i] = rnd::uniform();
				sp_range(ilp->size)
						biases.data.data[i] = rnd::uniform();
				connected = false;
			}
		}

		void connect(dense_layer *dlp)
		{
			if (!connected)
			{
				dlp->connections_to.push(this);
				connections_from.push(dlp);
				weights = matrix(dlp->size, size);
				biases = matrix(1, dlp->size);
				u32 nw = weights.col * weights.row;
				sp_range(nw)
						weights.data.data[i] = rnd::uniform();
				sp_range(dlp->size)
						biases.data.data[i] = rnd::uniform();
				connected = false;
			}
		}
	};

	enum class optimizer_type
	{
		gradient_descent
	};
	typedef function<matrix(const matrix &, const matrix &)> loss_function;
	namespace loss_functions
	{
		const loss_function mean_square_error = [](const matrix &y, const matrix &t)
		{
			matrix m = t - y;
			m.apply([](const f32 &v)
							{ return (f32)sqrt(v) });
			return m * 0.5f;
		};

		const loss_function mean_absolute_error = [](const matrix &y, const matrix &t)
		{
			matrix m = t - y;
			m.apply([](const f32 &v)
							{ return (f32)abs(v) });
			return m * 0.5f;
		};

	};

	class model
	{
	public:
		buffer<input_layer *> inp_layers;
		buffer<layer *> out_layers;
		optimizer_type optimizer;
		loss_function loss;
		f32 learning_rate = 0.03;

	public:
		model(input_layer *il, layer *ol) : inp_layers({il}), out_layers({ol}), optimizer(optimizer_type::gradient_descent), loss(loss_functions::mean_square_error)
		{
		}

		buffer<matrix> predict(f32 *data, u32 size)
		{
			u32 stride = 0;
			for (auto &il : inp_layers)
				stride += il->size;
			u32 samlpes = size / stride;
			buffer<matrix> outputs;
			sp_range(samples)
			{
				for (auto &il : inp_layers)
				{
					matrix a = il->to_matrix(data);
					data += il->size;
					for (auto &conn : il->connections_to)
						feedforword(conn, a);
				}

				for (auto &ol : out_layers)
				{
					outputs.push(ol->to_matrix());
				}
			}
			return outputs;
		}

		void fit(f32 *data, u32 size, f32 *target)
		{
			u32 stride = 0;
			for (auto &il : inp_layers)
				stride += il->size;
			u32 samples = size / stride;
			f32 *datastart = data;
			buffer<matrix> ts(out_layers.len * samples);
			sp_range(samples)
			{
				for (auto &ol : out_layers)
				{
					ts[i] = matrix(ol->shape[0], ol->shape[1], target);
					target += ol->shape[0] * ol->shape[1];
				}
			}
			if (optimizer == optimizer_type::gradient_descent)
			{
				u32 k = 0;
				sp_range(samples)
				{
					buffer<matrix> ys = predict(data, stride);
					data += stride;
					sp_rng(j, ys.len)
					{
						matrix em = loss(ys[j], ts[k + j]);
						for (auto& ol : out_layers)
						{
							backpropagate(ol, em);
						}
					}
					k += ys.len;
				}
			}




			
		}

	private:
		void feedforword(layer *l, const matrix &a)
		{
			matrix b;
			l->exec(a, b);
			for (auto &conn : l->connections_to)
			{
				feedforword(conn, b);
			}
		}

	void backpropagate(layer *l, matrix e)
	{
		f32 params[] = {learning_rate};
		matrix e2 = conn->update(e2, params);
		for(auto & conn : l->connections_from)
		{
			backpropagate(conn, e2);
		}
	}
	};


};//namespace sp
