bstsort : main.o 
	cc -o bstsort main.o 
main.o : main.c 
	cc -c main.c
clean :
	rm *o bstsort