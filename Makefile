WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = a6.c
OBJS = $(SRCS:%.c=%.o)

build: $(OBJS)
	$(GCC) $(TESTFALGS) $(SRCS) -o a6

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c

run: a6
	./a6 in_file out_file1 out_file2 out_file3

memory: a6
	valgrind ./a6 in_file out_file1 out_file2 out_file3

clean: # remove all machine generated files
	rm -f a6 *.o output? *~