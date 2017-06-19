lib: solution.h solution.c
	gcc -shared solution.c -fPIC -o libsolution.so 

exe: main.c solution.h lib
	gcc main.c -L. -lsolution -fPIC -o solustion
