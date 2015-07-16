CC = g++
LIBS =
INCLUDE =
OBJS = main.o list.o sorting.o

main : $(OBJS)
	$(CC) -o main $(OBJS)

main.o : queue_2s.h stack_2q.h tree.h list.h sorting.h C++from0to1.cpp
	$(CC) -c C++from0to1.cpp -o main.o

list.o : list.h list.cpp
	$(CC) -c list.cpp

sorting.o : sorting.h sorting.cpp
	$(CC) -c sorting.cpp


.PHONY : clean
clean :
	-rm main $(OBJS)
