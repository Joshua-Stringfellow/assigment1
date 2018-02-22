
OBJS = integer.o real.o main.o bst.o queue.o sll.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : main

main : main.o integer.o bst.o queue.o sll.o real.o
	gcc $(LOPTS) main.o integer.o real.o bst.o queue.o sll.o -o test-main

#test-dll : test-dll.o integer.o bst.o
#	gcc $(LOPTS) test-dll.o integer.o real.o bst.o -o test-dll

#test-stack : test-stack.o integer.o dll.o stack.o
	#gcc $(LOPTS) test-stack.o integer.o dll.o stack.o -o test-stack

#test-queue : test-queue.o integer.o sll.o queue.o
	#gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

#test-sll.o : test-sll.c sll.h integer.h real.h
	#gcc $(OOPTS) test-sll.c

#test-dll.o : test-dll.c dll.h integer.h real.h
	#gcc $(OOPTS) test-dll.c

#test-stack.o : test-stack.c stack.h integer.h
	#gcc $(OOPTS) test-stack.c

#test-queue.o : test-queue.c queue.h integer.h
	#gcc $(OOPTS) test-queue.c

#stack.o : stack.c stack.h
	#gcc $(OOPTS) stack.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

main.o : main.c
	gcc $(OOPTS) main.c

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

valgrind  : all
	echo testing test-main list
	valgrind ./test-sll
	echo
	#echo testing doubly-linked list
	#valgrind ./test-dll
	#echo
	#echo testing stack
	#valgrind ./test-stack
	#echo
	#echo testing queue
	#valgrind ./test-queue
	#echo


test : all
	echo testing singly-linked list
	./test-sll
	echo
	echo testing doubly-linked list
	./test-dll
	echo
	echo testing stack
	./test-stack
	echo
	echo testing queue
	./test-queue
	echo

clean    :
	 rm -f $(OBJS) test-*.o test-stack test-queue test-sll test-dll
