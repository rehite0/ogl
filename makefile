
CFLAGS=-Wall -Wextra `pkg-config --libs --cflags glfw3 glew`

all: refresh_tags a.out
	@echo 'compilation finished'
a.out: ogl.c sha.frag sha.vert
	cc $(CFLAGS) ogl.c -o a.out
clean:
	rm *.out *.o
refresh_tags:
	rm tags
	ctags *.c /usr/include/{GLFW/glfw3.h,GL/glew.h,stdio.h,stdio.h}
