
CFLAGS=-Wall -Wextra `pkg-config --libs --cflags glfw3 glew`

all: a.out
	@echo 'compilation finished'
a.out: ogl.c
	cc $(CFLAGS) ogl.c -o a.out
clean:
	rm *.out *.o
