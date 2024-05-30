/* 28/05/2024 -rh v1*/
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

//opengl setup
	

//event loop
	 while (!glfwWindowShouldClose(win_main))
    	 {
//gl stuff
		glClearColor(1,0,0,1);			//red colour
		glClear(GL_COLOR_BUFFER_BIT);


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
