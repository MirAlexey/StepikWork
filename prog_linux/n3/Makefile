all: exe lib

exe: hello.h main.c lib
	gcc main.c -fPIC -ldl -o hello

lib: hello.h hello.c
	gcc -shared hello.c -fPIC -o libHello.so 

clean:
	-rm bak/*.* 2>/dev/null 
	-mkdir bak 2>/dev/null
	-cp hello bak 2>/dev/null
	-cp *.o bak 2>/dev/null
	-cp libHello.so bak 2>/dev/null
	-rm hello libHello.so *.o 2>/dev/null
