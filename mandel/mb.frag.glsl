#version 450@
in vec4 gl_FragCoord;
out vec4 out_color;

uniform vec4 cmpx_plane;
	//0: REAL_MIN -2
	//1: REAL_MAX 2
	//2: IMAG_MIN -1.5
	//3: IMAG_MAX 1.5

uniform int max_iter;

int iter(){
    float real = (gl_FragCoord.x / 1080.0 - 0.5) * 4.0;
    float imag = (gl_FragCoord.y / 1080.0 - 0.7) * 4.0;
 
    int iterations = 0;
    float const_real = real;
    float const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 iter_to_color0()
//default green gradient boundry with black bg
{
	int iter=iter();
	if (iter == max_iter){
		gl_FragDept=0.0f;
		return vec4(0.0f,0.0f,0.0f,1.0f);
	}
	float iter_prcnt=float(iter)/max_iter;
	return vec4(0.0f,iter_prcnt,0.f,0.1f);
}

void main(){
	out_color=iter_to_color();
}
