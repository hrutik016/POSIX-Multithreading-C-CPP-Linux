gcc -g -c crud_algo.c -o crud_algo.o
gcc -g -c ref_count.c -o ref_count.o
gcc -g -c student_list.c -o student_list.o
gcc -g -c LinkedList/LinkedListApi.c -o LinkedList/LinkedListApi.o

gcc -g LinkedList/LinkedListApi.o crud_algo.o ref_count.o student_list.o -o crud_algo.exe -lpthread
