
#define REAL_MIN=-2
#define REAL_MAX=2
#define IMAG_MIN=-1.5
#define IMAG_MAX=1.5
#define HEIGHT 800
#define WIDTH 800
#define max_iter 800

void render(){
	for (int x=0;x<WIDTH;x++){
		for(int y=0;y<HEIGHT;y++){
			//define complex no
			//complex c={};
			complex z={0,0};
			int iter=0;
			while(sqrt( (z.r*z.r)+(z.i*z.i) ) <=2 && iter <MAX_iter){
				//z=z*z+c
				iter++;
			}
			//img[y*WIDTH+x]=iter;
		}
	}
}
