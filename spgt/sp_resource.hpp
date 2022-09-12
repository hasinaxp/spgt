#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "sp_math.hpp"
#include <fstream>
#include <sstream>

#define SP_DEF_PIXEL 0x000000ff
#define SP_DEF_ALPHA 0xff

constexpr char *sp_system_default_font_path = "C:/Windows/Fonts/arial.ttf";

namespace sp
{
	using namespace std;

	inline std::string load_file(std::string filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open())
			return "";
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		return ss.str();
	}

	inline void load_file_bin(std::string filepath, buffer<u8> &b)
	{
		ifstream file(filepath, ios::binary);
		if (!file.is_open())
			return;
		file.seekg(0, ios::end);
		u32 len = file.tellg();
		file.seekg(0, ios::beg);
		b.len = len;
		b.cap = len;
		delete[] b.data;
		b.data = new u8[len];
		file.read((char *)b.data, len);
		file.close();
	}

	class pixel
	{
	public:
		union
		{
			u32 n = SP_DEF_PIXEL;
			struct
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
		};

	public:
		pixel()
		{
		}
		pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = SP_DEF_ALPHA) : r(red), g(green), b(blue), a(alpha)
		{
		}
		pixel(uint32_t p) : n(p)
		{
		}
		bool operator==(const pixel &p) const
		{
			return n == p.n;
		}

		bool operator!=(const pixel &p) const
		{
			return n != p.n;
		}

		pixel operator*(const float i) const
		{
			float fR = min(255.0f, max(0.0f, float(r) * i));
			float fG = min(255.0f, max(0.0f, float(g) * i));
			float fB = min(255.0f, max(0.0f, float(b) * i));
			return pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
		}

		pixel operator/(const float i) const
		{
			float fR = min(255.0f, max(0.0f, float(r) / i));
			float fG = min(255.0f, max(0.0f, float(g) / i));
			float fB = min(255.0f, max(0.0f, float(b) / i));
			return pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
		}

		pixel &operator*=(const float i)
		{
			this->r = uint8_t(min(255.0f, max(0.0f, float(r) * i)));
			this->g = uint8_t(min(255.0f, max(0.0f, float(g) * i)));
			this->b = uint8_t(min(255.0f, max(0.0f, float(b) * i)));
			return *this;
		}

		pixel &operator/=(const float i)
		{
			this->r = uint8_t(min(255.0f, max(0.0f, float(r) / i)));
			this->g = uint8_t(min(255.0f, max(0.0f, float(g) / i)));
			this->b = uint8_t(min(255.0f, max(0.0f, float(b) / i)));
			return *this;
		}

		pixel operator+(const pixel &p) const
		{
			uint8_t nR = uint8_t(min(255, max(0, int(r) + int(p.r))));
			uint8_t nG = uint8_t(min(255, max(0, int(g) + int(p.g))));
			uint8_t nB = uint8_t(min(255, max(0, int(b) + int(p.b))));
			return pixel(nR, nG, nB, a);
		}

		pixel operator-(const pixel &p) const
		{
			uint8_t nR = uint8_t(min(255, max(0, int(r) - int(p.r))));
			uint8_t nG = uint8_t(min(255, max(0, int(g) - int(p.g))));
			uint8_t nB = uint8_t(min(255, max(0, int(b) - int(p.b))));
			return pixel(nR, nG, nB, a);
		}

		pixel &operator+=(const pixel &p)
		{
			this->r = uint8_t(min(255, max(0, int(r) + int(p.r))));
			this->g = uint8_t(min(255, max(0, int(g) + int(p.g))));
			this->b = uint8_t(min(255, max(0, int(b) + int(p.b))));
			return *this;
		}

		pixel &operator-=(const pixel &p) // Thanks Au Lit
		{
			this->r = uint8_t(min(255, max(0, int(r) - int(p.r))));
			this->g = uint8_t(min(255, max(0, int(g) - int(p.g))));
			this->b = uint8_t(min(255, max(0, int(b) - int(p.b))));
			return *this;
		}

		pixel inv() const
		{
			uint8_t nR = uint8_t(min(255, max(0, 255 - int(r))));
			uint8_t nG = uint8_t(min(255, max(0, 255 - int(g))));
			uint8_t nB = uint8_t(min(255, max(0, 255 - int(b))));
			return pixel(nR, nG, nB, a);
		}
		vec4 to_vec4()
		{
			float R = float(r) / 255.0;
			float G = float(g) / 255.0;
			float B = float(b) / 255.0;
			float A = float(a) / 255.0;
			return vec4(R, G, B, A);
		}
	};

	ostream &operator<<(ostream &os, const pixel &p)
	{
		os << hex << p.n;
		return os;
	}

	typedef mat<pixel> image;
	typedef mat<u8> greyscale_image;

	inline image load_image(const string &s)
	{
		int nrChannels;
		int width, height;
		u8 *data = stbi_load(s.c_str(), &width, &height, &nrChannels, 4);
		image img;
		img.row = height;
		img.col = width;
		img.data = buffer<pixel>(img.row * img.col);
		u32 off = 0;
		u32 size = img.row * img.col;
		for (u32 i = 0; i < size; i++)
		{
			img.data[i] = pixel(data[off], data[off + 1], data[off + 2], data[off + 3]);
			off += 4;
		}

		delete[] data;
		return img;
	}

	//----------------------font---------------------
	class fontdata
	{
	public:
		struct FontGlyph
		{
			char charcode;
			float advance;
			signed char xoff;
			signed char yoff;
			uint32_t x = 0, y = 0;
			uint32_t w = 0, h = 0;
			uint8_t *data = nullptr;
		};
		struct FontGlyphInfo
		{
			vec4 crop;
			vec2 offset;
			vec2 size;
			float advance;
		};

	public:
		greyscale_image spritesheet;
		unordered_map<char, FontGlyphInfo> glyphs;
		u32 id = 0;
		float currentheight = 0;
		float scale = 1.0;

	public:
		fontdata()
		{
		}

		void load(string filepath, u32 font_size = 36)
		{
			float ypos;
			stbtt_fontinfo fi;
			buffer<u8> fontfiledata;
			load_file_bin(filepath, fontfiledata);

			stbtt_InitFont(&fi, fontfiledata.data, stbtt_GetFontOffsetForIndex(fontfiledata.data, 0));

			scale = stbtt_ScaleForPixelHeight(&fi, font_size);

			float pixel_dist_scale = 36.0; // trades off precision w/ ability to handle *smaller* sizes
			int onedge_value = 180;
			int padding = 2; // not used in shader
			int mWidth = 0;
			int mHeight = 0;
			string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz"
												"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
												",.+-=*%&;<>?/\\'\"@:()[]{}#!~|^_~";
			std::vector<FontGlyph> fdata;
			for (char ch : alphabet)
			{
				FontGlyph fc;
				int xoff, yoff, w, h, advance;
				w = 0;
				h = 0;
				fc.data = stbtt_GetCodepointSDF(&fi, scale, ch, padding, onedge_value, pixel_dist_scale, &w, &h, &xoff, &yoff);
				fc.xoff = xoff;
				fc.yoff = yoff;
				fc.w = (int)w < 200 ? w : 0;
				fc.h = (int)h < 200 ? h : 0;
				fc.charcode = ch;
				if (fc.w > mWidth)
					mWidth = fc.w;
				if (fc.h > mHeight)
					mHeight = fc.h;
				stbtt_GetCodepointHMetrics(&fi, ch, &advance, NULL);
				fc.advance = advance * scale;
				fdata.push_back(fc);
			}

			currentheight = float(mHeight) * 0.9 / font_size;

			uint32_t bitmapWidth = 512;
			uint32_t bitmapHeight = 256;
			uint8_t *bitmap = (uint8_t *)malloc(bitmapWidth * bitmapHeight * sizeof(uint8_t) * 1);
			memset(bitmap, 0, bitmapWidth * bitmapHeight * sizeof(uint8_t) * 1);

			int nWidth = bitmapWidth / mWidth;
			int nHeight = bitmapHeight / mHeight;

			for (int i = 0; i < fdata.size(); i++)
			{
				uint32_t x, y;
				x = (i % nWidth) * mWidth;
				y = (i / nWidth) * mHeight;
				//cout << fdata[i].charcode << endl;
				WriteCharToBuffer(x, y, fdata[i].w, fdata[i].h, bitmapWidth, fdata[i].data, bitmap);
				fdata[i].x = x;
				fdata[i].y = y;
			}
			stbi_write_png("./atlas.png", bitmapWidth, bitmapHeight, 1, bitmap, 0);
			
			spritesheet = greyscale_image(bitmapHeight, bitmapWidth);
			memcpy(spritesheet.data.data, bitmap, bitmapWidth * bitmapHeight);
			delete[] bitmap;
			for (int i = 0; i < fdata.size(); i++)
			{
				FontGlyphInfo info;
				float x = float(fdata[i].x) / bitmapWidth;
				float y = float(fdata[i].y) / bitmapHeight;
				float w = float(fdata[i].w) / bitmapWidth;
				float h = float(fdata[i].h) / bitmapHeight;

				info.crop = vec4(x, y, w, h);
				info.advance = float(fdata[i].advance) / font_size;
				info.offset = vec2(float(fdata[i].xoff) / font_size, float(fdata[i].h - fdata[i].yoff) / font_size);
				info.size = vec2(float(fdata[i].w) / font_size, float(fdata[i].h) / font_size);

				glyphs[fdata[i].charcode] = info;
				free(fdata[i].data);
				fdata[i].data = nullptr;
			}

			 //for (auto &g : glyphs)
			 	//cout << g.first << " " << g.second.offset << " " << g.second.crop << endl;
		}

		void load_default()
		{

			load(sp_system_default_font_path);
		}

	private:
		inline void WriteCharToBuffer(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t b, uint8_t *src, uint8_t *dest)
		{

			uint32_t srcOffset, destOffset;
			for (uint32_t i = 0; i < h; i++)
			{
				for (uint32_t j = 0; j < w; j++)
				{
					srcOffset = (i * w + j);
					destOffset = ((y + i) * b + x + j);

					dest[destOffset] = src[srcOffset];
				}
				// printf("\n");
			}
		};
	};

}; // namespace sp;
