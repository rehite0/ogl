
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
//#include <stdbool.h>
//#include <math.h>
//#include <string.h>
#include "ogl_ty.h"



void dat_init();
void load_sha();
void load_textures();
void err_callback(int error, const char* desc);
void event_log(const char* desc);
void err_log(int error, const char* desc);
//
int 
main(void)
{
	glfwSetErrorCallback(err_callback);
	if (glfwInit() != GLFW_TRUE) {err_log(1,"glfw failed to intialize.");}

//creating window
	GLFWwindow* win_main = glfwCreateWindow(640  , 480   , "ogl", NULL   , NULL);
                                             //width, height, title, monitor, share
	if (!win_main) {err_log(1,"window creation failed");}
	
	glfwMakeContextCurrent(win_main);

	if (glewInit() !=GLEW_OK){err_log(1,"glewinit failed");}
	
	dat_init();
	load_sha();
	load_textures();
	
	double t,dt;
//event loop
	int j=0,i=0;
	while (!glfwWindowShouldClose(win_main))
    	{
		if (j%60==0){j=0;i=(i+1)%num_vao; }
//gl stuff
		int w,h; glfwGetFramebufferSize(win_main,&w,&h);
		glViewport(0,0,w,h);
		
		glClearColor(1.0,1.0,1.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(ogl.vao[i]);
		glBindTexture(GL_TEXTURE_2D, ogl.tex[1]);
		
		dt=glfwGetTime()-t;t=glfwGetTime();
		glUniform2f(ogl.u_time,t,dt);
		glDrawElements(GL_TRIANGLES, ogl.numvert[i], GL_UNSIGNED_SHORT, 0);
		glfwSwapBuffers(win_main);
		glfwPollEvents();
		j++;
	 }

	//exit code
	glfwDestroyWindow(win_main);
	err_log(0,"application terminated");
}

void
dat_init(){
	GLuint ibo[num_vao], vbo[num_vao];
	glGenVertexArrays(num_vao, ogl.vao);
	glGenBuffers(num_vao, vbo);
	glGenBuffers(num_vao, ibo);

	for (int i=0;i<num_vao;i++){	
		glBindVertexArray(ogl.vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER,varray[i].v_size,varray[i].vertices_buf,GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);//pos
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(vertex),0);
		glEnableVertexAttribArray(1);//colour
		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(vertex),(char*)(sizeof(_position)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(vertex),(char*)(sizeof(_color)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,varray[i].ibo_size,varray[i].ibo_buf,GL_STATIC_DRAW);
		ogl.numvert[i]=varray[i].ibo_size/sizeof(unsigned short);
	}

	glEnable(GL_DEPTH_TEST);
}


void
load_sha(){	
	FILE *vsf, *fsf;
	char *bvs, *bfs;
	int vsl, fsl;

	if (	!(vsf=fopen("sha.vert", "rb")) ||
		!(fsf=fopen("sha.frag", "rb"))	)
		err_log(1,"shader opening failed");
	
	fseek(vsf, 0, SEEK_END);vsl=ftell(vsf);
	bvs=(char*)malloc(vsl+1);
	fseek(vsf, 0, SEEK_SET);
	fread(bvs, vsl, 1, vsf);fclose(vsf);
	bvs[vsl]=0;bvs[12]='\r';

	fseek(fsf, 0, SEEK_END);fsl=ftell(fsf);
	bfs=(char*)malloc(fsl+1);
	fseek(fsf, 0, SEEK_SET);
	fread(bfs, fsl, 1, fsf);fclose(fsf);
	bfs[fsl]=0;bfs[12]='\r';		//hack need improvement

	GLuint vsid=glCreateShader(GL_VERTEX_SHADER);
	GLuint fsid=glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsid, 1, (const GLchar**)&bvs, 0);
	glShaderSource(fsid, 1, (const GLchar**)&bfs, 0);

	glCompileShader(vsid);
	glCompileShader(fsid);

	ogl.pid[0]=glCreateProgram();
	glAttachShader(ogl.pid[0],vsid);
	glAttachShader(ogl.pid[0],fsid);
	//glBindAttribLocation(pid, 0, "position");
	//glBindAttribLocation(pid, 1, "c_rgb");
	
	glLinkProgram(ogl.pid[0]);
//catch error in shader code
	int iscomp,maxlen;
	char *InfoLog;

	glGetShaderiv(fsid, GL_COMPILE_STATUS, &iscomp);
	if(iscomp == 0)
	{
		glGetShaderiv(fsid, GL_INFO_LOG_LENGTH, &maxlen);
		InfoLog = (char *)malloc(maxlen);

		glGetShaderInfoLog(fsid, maxlen, &maxlen, InfoLog);
		printf("shader error:%s",InfoLog);
		free(InfoLog);free(bvs);free(bfs);
		exit(0);
	}

	glGetShaderiv(vsid, GL_COMPILE_STATUS, &iscomp);
	if(iscomp == 0)
	{
		glGetShaderiv(vsid, GL_INFO_LOG_LENGTH, &maxlen);
		InfoLog = (char *)malloc(maxlen);

		glGetShaderInfoLog(fsid, maxlen, &maxlen, InfoLog);
		printf("shader error:%s",InfoLog);
		free(InfoLog);free(bvs);free(bfs);
		exit(0);

	}


	glUseProgram(ogl.pid[0]);
	ogl.u_time=glGetUniformLocation(ogl.pid[0],"time_v");

	free(bvs);free(bfs);
}

void
load_textures(){
	glGenTextures(num_tex,ogl.tex);
	for (int i=0;i<num_tex;i++){
		glBindTexture(GL_TEXTURE_2D, ogl.tex[i]);
// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
		int width, height, nrChannels;
		unsigned char *data = stbi_load(texa[i], &width, &height, &nrChannels, 0);

		if (data)
		{
    			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else	err_log(1,"unable to load texture!");
		stbi_image_free(data);
	}	
}

void 
err_log(int error, const char* desc){
	if (!error)
	{	fprintf(stdout,"exit message:%s\n",desc);}
	else
	{	fprintf(stderr,"error:%s\n",desc);}
	glfwTerminate();
	exit(error);
}

void 
err_callback(int error, const char* desc){
	fprintf(stderr,"error(%i):%s\n",error,desc);
}

void
event_log(const char* desc){
	fprintf(stdout,"event:%s\n",desc);
}
