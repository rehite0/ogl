
#define REAL_MIN -2
#define REAL_MAX 2
#define IMAG_MIN -1.5
#define IMAG_MAX 1.5
#define HEIGHT 8000
#define WIDTH 8000
#define max_iter 800

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct c{
	float r;
	float i;
}complex;

int* render(){
	int* img=malloc(sizeof(int)*WIDTH*HEIGHT);
	for (int x=0;x<WIDTH;++x){
		for(int y=0;y<HEIGHT;++y){
			complex z={0.0f,0.0f};
			complex c={ REAL_MIN+((float)(REAL_MAX-REAL_MIN))*x/WIDTH
					  , IMAG_MIN+((float)(IMAG_MAX-IMAG_MIN))*y/HEIGHT };
			int iter=0;
			while( (z.r*z.r)+(z.i*z.i) <=4 && iter < max_iter){
				float temp=z.r;
				z.r= z.r* z.r - z.i* z.i;
				z.i= 2* temp* z.i;

				z.r += c.r; z.i += c.i;
				++iter;
			}//while
			img[y*WIDTH+x]=iter;
		}//for y
	}//for x
	return img;
}//fn

void create_ppm(int* img){
	FILE* f=fopen("mb.ppm","w");
	fprintf(f,"P3\n%d %d\n255\n", WIDTH, HEIGHT);
	for (long i=0; i<HEIGHT*WIDTH; ++i){
		int r,g,b;
		r=g=b=0;
		if (img[i]<=max_iter){
			g=(int)( ( ( (float)img[i]) *255)/max_iter);
		}
		else g=0;
		fprintf(f,"%d %d %d \n",r,g,b);	
	}//for
	fclose(f);
}//fn

int main(){
	int* img=render();
	create_ppm(img);
	free(img);
}
