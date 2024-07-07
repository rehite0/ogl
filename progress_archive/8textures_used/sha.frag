#version 450@

in vec3 color;
in vec2 tex;
out vec4 FragColor;

uniform sampler2D tex1;

uniform vec2 time_v;

void main(void)
{
	FragColor=texture(tex1,tex);
	//FragColor=vec4(color.xy,sin(time_v.x)/2.0+0.5,1.0);
}
