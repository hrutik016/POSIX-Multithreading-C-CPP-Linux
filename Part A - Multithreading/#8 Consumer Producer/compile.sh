gcc -g -c Queue.c -o Queue.o
gcc -g -c prod_cons_on_Q.c -o _prod_cons_on_Q.o
gcc -g prod_cons_on_Q.o Queue.o -o exe -lpthread
gcc -g prod_cons_on_Q.o Queue.o -o solution.exe -lpthread
