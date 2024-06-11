/* 30/05/2024 -rh v3*/
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
	
	GLfloat verta[]={+0.0f, +0.0f	,1.0f, 0.0f, 0.0f
			,+1.0f, +1.0f	,1.0f, 0.0f, 0.0f
			,-1.0f, +1.0f	,1.0f, 0.0f, 0.0f
			,-1.0f, -1.0f	,1.0f, 0.0f, 0.0f
			,+1.0f, -1.0f	,1.0f, 0.0f, 0.0f };
	GLuint vao;
	glGenBuffers(1,&vao);
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verta),verta,GL_STATIC_DRAW);
//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,0);
//colour
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(char*)(sizeof(float)*2));


	GLushort map[]={0,1,2, 0,3,4};
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(map),map,GL_STATIC_DRAW);



//event loop
	 while (!glfwWindowShouldClose(win_main))
    	 {
//gl stuff
		int w,h; glfwGetFramebufferSize(win_main,&w,&h);
		glViewport(0,0,w,h);

//		glDrawArrays(GL_TRIANGLES,0,6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
//		glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT,0);
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
