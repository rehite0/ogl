#version 450@
//precision highp float;

in vec3 color;
out vec4 FragColor;

uniform vec2 time_v;

void main(void)
{
	FragColor=vec4(color.xy,sin(time_v.x)/2.0+0.5,1.0);
}
