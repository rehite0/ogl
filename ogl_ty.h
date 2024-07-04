#pragma once

#include <cglm/cglm.h>

#define num_vao 2
#define num_pro 1
#define num_tex 1
struct __state{
	unsigned short numvert[num_vao];
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


vertex __tri1[]={//
	 { {+0.9f, +0.9f, +0.0},	{0.0f, 0.0f, 1.0f} }
	,{ {+0.0f, -0.9f, -0.5},	{0.0f, 1.0f, 0.0f} }
	,{ {-0.9f, +0.9f, +0.0},	{1.0f, 0.0f, 0.0f} }
	};
unsigned short __tri1_ibo[]={0,1,2};
vertex __tri2[]={//
	 { {+0.0f, +0.9f, -0.5},	{0.0f, 0.0f, 1.0f} }
	,{ {+0.9f, -0.9f, +0.0},	{0.0f, 1.0f, 0.0f} }
	,{ {-0.9f, -0.9f, +0.0},	{1.0f, 0.0f, 0.0f} } 
	};
unsigned short __tri2_ibo[]={0,1,2};


typedef struct __vertStruct{
	vertex* vertices_buf;
	unsigned int v_size;
	unsigned short *ibo_buf;
	unsigned short ibo_size;
		} vert_struct;
vert_struct varray[num_vao]={
	 {__tri1,sizeof(__tri1),__tri1_ibo,sizeof(__tri1_ibo)}
	,{__tri2,sizeof(__tri2),__tri2_ibo,sizeof(__tri2_ibo)}
};

char* texa[num_tex]={};
