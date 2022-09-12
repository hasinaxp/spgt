#pragma once
#include "sp_resource.hpp"

namespace sp {

	constexpr const char * sprite_renderer_vertex_shader = R"(
	#version 410
	layout (location = 0) in vec2 position;
	layout (location = 1) in vec2 uv;

	layout (location = 2) in vec4 rect;
	layout (location = 3) in vec4 cropRect;
	layout (location = 4) in vec4 color;
	layout (location = 5) in vec4 tzrs;
	layout (location = 6) in vec4 extra;
	layout (location = 7) in vec4 extra2;

	uniform float u_time;
	uniform float u_aspect;
	
	uniform mat4 u_projectionMatrix;
	uniform mat4 u_viewMatrix;

	const float pi = 3.14159;

	vec2 rotate(vec2 v, float a) 
	{
		float s = sin(a);
		float c = cos(a);
		mat2 m = mat2(c, s, -s, c);
		return m * v;

	}

	out vec2 texcord;
	out vec4 fgcol;
	out vec4 data1;
	out vec4 data2;
	out float tid;

	void main()
	{
		vec4 pos = vec4(position, 0.0, 1.0);
		pos.x /= u_aspect;
		
		pos[0] = pos[0] * rect[2] ;
		pos[1] = pos[1] * rect[3] ;
		if(int(extra[0]) != 2)
		{
			pos.xy = rotate(pos.xy, tzrs.z);
			pos.xy += rect.xy;		
		}
		else
		{
			
			pos.xy = rotate(pos.xy, tzrs.z);
			pos.xy += rect.xy;

		}
		
		gl_Position = u_projectionMatrix *  pos;

	 	texcord.x = cropRect.x + uv.x * cropRect.z;
		texcord.y = cropRect.y + uv.y * cropRect.w;
		fgcol = color;
		data1 = extra;
		data2 = extra2;
		tid = tzrs[0];
	}
	)";

	constexpr const char* sprite_renderer_fragment_shader = R"(
	#version 410

	in vec2 texcord;
	in vec4 fgcol;
	in vec4 data1;
	in vec4 data2;
	in float tid;

	uniform float u_width;
	uniform float u_aspect;
	uniform sampler2D textures[16];

	const float pi = 3.14159;



	out vec4 output;


	float polygon( vec2 uv, float n, float s = 1.0)
	{	
		float angle = atan(uv.x, uv.y);
		float slice = pi * 2.0 / n;
		float b = data1[1] / 10;
		b = min(0.65, b) * s;
		return 1.0 - step(b, cos(floor(0.5 + angle/ slice) * slice -angle) * length(uv));
	}

	void main()
	{

		output = fgcol;
		int mode = int(data1[0]);
		if(mode == 0)
		{
			output = fgcol;
		}
		else if( mode == 1)
		{
			float x = texcord.x;
			float y = texcord.y;

			float f1 = 1.0 - step(data1[1], x) + step(1.0 - data1[1], x);
			float f2 = 1.0 - step(data1[2], y) + step(1.0 - data1[2], y);
			output = output * (f1 + f2);
		}
		else if(mode == 2)
		{
			output = fgcol;
		}
		else if(mode == 3)
		{
			vec2 uv = (texcord - 0.5) * 2.0;
			float l = sqrt(uv.x * uv.x + uv.y * uv.y);
			float f = (1.0 - smoothstep(0.995, 1.0, l));
			output = output * f;
		}
		else if(mode == 4)
		{
			vec2 uv = (texcord - 0.5) * 2.0;
			float l = sqrt(uv.x * uv.x + uv.y * uv.y);
			float f = (1.0 - smoothstep(0.995, 1.0, l)) -(1.0 - smoothstep(0.995 - data1[1], 1.0 - data1[1], l));
			output = output * f;
		}
		else if(mode == 5)
		{
			vec2 uv = (texcord - 0.5) * 2.0;
			float f = polygon(uv, data1[1]);
			output = output * f;
		}
		else if(mode == 6)
		{
			vec2 uv = (texcord - 0.5) * 2.0;
			float f = polygon(uv, data1[1]) - polygon(uv, data1[1], 1.0 - data1[2]);
			output = output * f;
		}
		else if(mode == 7)
		{
			vec4 color = texture(textures[int(tid)], texcord);
			output = output * color;
		}
		else if(mode == 8)
		{
			float f = texture(textures[int(tid)], texcord).r ;
			float fsize = data1[2];
			float width = .2 + 0.05 * step(11.0, fsize);
			float edge =  20.66/(fsize * fsize) + 0.12 * step(11.0, fsize) + 0.04* step(1.0, 30.0 - fsize);
			float d = 1.0 - f;

			f = 1.0 - smoothstep(width, width+edge, d);
			output = output * f;

		}
	}
	)";

}; //namespace sp