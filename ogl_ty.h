#pragma once

#include <cglm/cglm.h>

typedef vec3 __position;
typedef vec3 __color;

typedef struct vrt {
	__position po;
	__color co;
} vertex;

struct __state{
	int maplen;	
} ogl;
