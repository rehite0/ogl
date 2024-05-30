/* 29/05/2024 -rh v3*/
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <stdio.h>
//#include <stdbool.h>
#include <stdlib.h>
//#include <math.h>
//#include <string.h>

void err_callback(int error, const char* desc);
void event_log(const char* desc);
void err_log(int error, const char* desc);

int 
main(int argc, char** argv)
{
	glfwSetErrorCallback(err_callback);
	if (glfwInit() != GLFW_TRUE) {err_log(1,"glfw failed to intialize.");}

//creating window
	GLFWwindow* win_main = glfwCreateWindow(640  , 480   , "ogl", NULL   , NULL);
                                             //width, height, title, monitor, share
	if (!win_main) {err_log(1,"window creation failed");}
	
	glfwMakeContextCurrent(win_main);

	if (glewInit() !=GLEW_OK){err_log(1,"glewinit failed");}
	
	GLfloat verta[]={+0.0f,+0.0f
			,+1.0f,+1.0f
			,-1.0f,+1.0f

			,-1.0f,-1.0f
			,+1.0f,-1.0f};
	GLuint vertaid;
	glGenBuffers(1,&vertaid);
	glBindBuffer(GL_ARRAY_BUFFER, vertaid);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verta),verta,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);

	GLuint map[]={0,1,2, 0,3,4};

//event loop
	 while (!glfwWindowShouldClose(win_main))
    	 {
//gl stuff
		int w,h; glfwGetFramebufferSize(win_main,&w,&h);
		glViewport(0,0,w,h);

		glDrawArrays(GL_TRIANGLES,0,6);

//
		glfwSwapBuffers(win_main);
		glfwPollEvents();
	 }

	//exit code
	glfwDestroyWindow(win_main);
	err_log(0,"application terminated");
}



void 
err_log(int error, const char* desc)
{
	if (!error)
	{	fprintf(stdout,"exit message:%s\n",desc);}
	else
	{	fprintf(stderr,"error:%s\n",desc);}
	glfwTerminate();
	exit(error);
}

void 
err_callback(int error, const char* desc)
{
	fprintf(stderr,"error:%s\n",desc);
}

void
event_log(const char* desc)
{
	fprintf(stdout,"event:%s\n",desc);
}
