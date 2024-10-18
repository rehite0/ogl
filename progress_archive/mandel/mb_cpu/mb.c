
#define REAL_MIN -2
#define REAL_MAX 1
#define IMAG_MIN -1.5
#define IMAG_MAX 1.5
#define HEIGHT 1080
#define WIDTH 1080
#define max_iter 20

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct c{
	double r;
	double i;
}complex;

int* render(){
	int* img=malloc(sizeof(int)*WIDTH*HEIGHT);
	for (int x=0;x<WIDTH;++x){
		for(int y=0;y<HEIGHT;++y){
			complex z={0.0f,0.0f};
			complex c={ REAL_MIN+((double)(REAL_MAX-REAL_MIN))*x/WIDTH
					  , IMAG_MIN+((double)(IMAG_MAX-IMAG_MIN))*y/HEIGHT };
			int iter=0;
			while( (z.r*z.r)+(z.i*z.i) <=4 && iter < max_iter){
				double temp=z.r;
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
		if (img[i]<max_iter){
			g=(int)( ( ((double)img[i]) /max_iter)*255);
		}
		else g=0;
		fprintf(f,"%d %d %d \n",r,g,b);	
	}//for
	fclose(f);
}//fn

void create_ppm2(int* img){
	FILE* f=fopen("mb.ppm","w");
	fprintf(f,"P3\n%d %d\n255\n", WIDTH, HEIGHT);
	for (long i=0; i<HEIGHT*WIDTH; ++i){
		int r,g,b;
		r=g=b=0;
		if (img[i]<max_iter){
			unsigned char c=(int)( (double)img[i]/max_iter*155)+100;
			r=c;
			b=c;
			g=c;
		}
		else g=0;
		fprintf(f,"%d %d %d \n",r,g,b);	
	}//for
	fclose(f);
}//fn

int main(){
	int* img=render();
	create_ppm2(img);
	free(img);
}
