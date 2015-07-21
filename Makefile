CC = g++
LIBS =
INCLUDE = 
HEADERS = queue_2s.h stack_2q.h tree.h list.h sorting.h C++from1to2.h
OBJS = main.o list.o sorting.o C++from1to2.o

main : $(OBJS)
	$(CC) -o main $(OBJS)

main.o :  $(HEADERS) C++from0to1.cpp
	$(CC) -c C++from0to1.cpp -o main.o

list.o : list.h list.cpp
	$(CC) -c list.cpp

sorting.o : sorting.h sorting.cpp
	$(CC) -c sorting.cpp

C++from1to2.o : $(HEADERS) C++from1to2.cpp
	$(CC) -c C++from1to2.cpp


.PHONY : clean
clean :
	-rm main $(OBJS)
