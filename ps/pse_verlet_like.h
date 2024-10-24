//0-x && 1-y
#define abs2(a) o[0]*o[0] + o[1]*o[1]
#define mod(x)  (x>0)? x:-1*x

//fn prototype
void fgravity(BALL* a);
void fconstrain(BALL* a);
void coll_dect(BALL* ball_buff);
void iter_phy();
void update_model();
void genclick(GLFWwindow *win, double x, double y);///ic
void genstream(int x,int y, float velx,float vely, float inc_rate);///ic
void genblast(int x,int y, float velx, float vely, int num);///ic ///fix shader uv

//colldect use a.,b.
//wall constrain does not consider for wall

double t,dt;
int BALL_COUNT=0;

typedef struct _BALL{
	float pos[2];
	float vel[2];
	float acc[2];
	float rad;

}BALL;

BALL** ball_buff;

#define num_forces 2
void (*force_buffer[num_forces])(BALL*)={fgravity,fconstrain};

/*collision physics
 * <   n'+
 *  *  __+
 *   *|  +
 *    *  +
 *  m'( * *
 * ++++* a +/+
 *      * +/+ *
 *       +/+ b *++++
 *          * * )m'
 *           + *
 *           +  *
 *           +__|*
 *           + n' >
 *
 *1 aofcol(axis of collision) is vec b->a
 *  m,n is angle made by aofcol and -ve x_axis,+ve y_axis
 *2 cos m is |b/h| and cos n is |p/h|
 *  velocity after collision
 */
void coll_dect(BALL* ball_buff){
	int i,j;
	for (i=0;i<BALL_COUNT;i++){
		for (j=0,j<BALL_COUNT,j++){
			BALL a,b;
			a=*ball_buff[i];
			b=*ball_buff[j];

			double aofcol[2]={a.pos[0]-b.pos[0] , a.pos[1]-b.pos[1]};	//*1

			if ( abs2(aofcol)<(a.rad+b.rad)*(a.rad+b.rad) && i!=j ){
				double p=aofcol[0],b=aofcol[1],h=sqrt(abs2(aofcol));
				a.vel[0]=a.vel[0]-2*(sqrt(abs2(a.vel))*mod(p/h));		//*2
				b.vel[0]=b.vel[0]-2*(sqrt(abs2(b.vel))*mod(b/h));
				a.vel[1]=a.vel[1]-2*(sqrt(abs2(a.vel))*mod(b/h));
				b.vel[1]=b.vel[1]-2*(sqrt(abs2(b.vel))*mod(p/h));
			}//if
		}//for j
	}//for i
}//fn

void iter_phy(){
	int i;
	for (i=0;i<BALL_COUNT;i++){
		ball_buff[i]
		ball_buff[i]->acc[0]=0.0;
		ball_buff[i]->acc[1]=0.0;
		for (int j=0;j<force_num;j++)
			(*force_buff[j])(ball_buff[i]);
		ball_buff[i]->vel[0]+=ball_buff[i]->acc[0]*dt*0.5;
		ball_buff[i]->vel[1]+=ball_buff[i]->acc[1]*dt*0.5;
		ball_buff[i]->pos[0]+=ball_buff[i]->vel[0]*dt;
		ball_buff[i]->pos[1]+=ball_buff[i]->vel[1]*dt;
		
	}//for i
}//fn

void fgravity(BALL* a){
	a->acc[1]-=9.8;
}//fn

void fconstrain(BALL* a){
	if (a->pos[0] >1){
		a->pos[0]=1;
		a->vel[0]=0;
	}
	if (a->pos[0] <-1){
		a->pos[0]=-1;
		a->vel[0]=0;
	}
	if (a->pos[1] >1){
		a->pos[1]=1;
		a->vel[1]=0;
	}
	if (a->pos[1] <-1){
		a->pos[1]=-1;
		a->vel[1]=0;
	}
}//fn

void update_model(){
	iter_phy()	;
	coll_dect() ;
}//fn
