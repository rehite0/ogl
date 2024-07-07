#version 450@

layout(location=0) in vec3 position;
layout(location=1) in vec3 c_rgb;
layout(location=2) in vec2 tex_st;

out vec3 color;
out vec2 tex;

void main()
{
	gl_Position=vec4(position,1.0);
	color=c_rgb;
	tex=tex_st;
}
