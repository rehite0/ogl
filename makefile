
CFLAGS=-Wall -Wextra `pkg-config --libs --cflags glfw3 glew`

all: refresh_tags a.out
	@echo '_______________compilation finished_________________'
a.out: ogl.c ogl_ty.h sha.frag sha.vert 
	cc $(CFLAGS) ogl.c -o a.out 2>cmpl.log || ! less cmpl.log
clean:
	rm *.out *.o
refresh_tags:
	rm tags
	ctags *.c /usr/include/{GLFW/glfw3.h,GL/glew.h,stdio.h,stdio.h,cglm/*}
