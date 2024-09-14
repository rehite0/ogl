#version 450@
precision highp float;

in vec4 gl_FragCoord;
out vec4 out_color;

uniform vec4 cmpx_plane;
	//0: REAL_MIN
	//1: REAL_MAX
	//2: IMAG_MIN
	//3: IMAG_MAX
uniform vec2 time_v;
uniform int max_iter;
uniform ivec2 hw;

int iter(){
    float real = (cmpx_plane.x)+(float(gl_FragCoord.x) / hw.x ) * (cmpx_plane.y-cmpx_plane.x);
	float imag = (cmpx_plane.z)+(float(gl_FragCoord.y) / hw.y ) * (cmpx_plane.w-cmpx_plane.z);
 
    int iters = 0;
    float c_real = real;
    float c_imag = imag;
 
    while (iters < max_iter)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + c_real;
        imag = (2.0 * tmp_real * imag) + c_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iters;
    }
    return iters;
}

vec4 color()
//default green gradient boundry with black bg
{
	int iter=iter();
	if (iter == max_iter){
		gl_FragDepth = 0.0f;
		return vec4(0.0f,0.0f,0.0f,1.0f);
	}
	float iter_prcnt=float(iter)/max_iter;
	return vec4(0.0f,iter_prcnt,0.f,1.0f);
}

void main(){
	out_color=color();
}
