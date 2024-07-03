#pragma once

#include <cglm/cglm.h>

#define num_vao 2
#define num_pro 1
struct __state{
	unsigned short maplen[num_vao];
	unsigned int vao[num_vao];
	unsigned int pid[num_pro];

	unsigned int u_time;
} ogl;

typedef vec3 _position;
typedef vec3 _color;

typedef struct __vrt {
	_position po;
	_color co;
} vertex;
typedef struct __vertStruct{
	vertex* vertices;
	unsigned int size
} vert_struct;


vertex __tri1[]={//
	 { {+0.9f, +0.9f, +0.0},	{0.0f, 0.0f, 1.0f} }
	,{ {+0.0f, -0.9f, -0.5},	{0.0f, 1.0f, 0.0f} }
	,{ {-0.9f, +0.9f, +0.0},	{1.0f, 0.0f, 0.0f} }
	};
vertex __tri2[]={//
	 { {+0.0f, +0.9f, -0.5},	{0.0f, 0.0f, 1.0f} }
	,{ {+0.9f, -0.9f, +0.0},	{0.0f, 1.0f, 0.0f} }
	,{ {-0.9f, -0.9f, +0.0},	{1.0f, 0.0f, 0.0f} } 
	};

vert_struct _varray[num_vao]={
	 {__tri1,sizeof(__tri1)}
	,{__tri2,sizeof(__tri2)}
};

