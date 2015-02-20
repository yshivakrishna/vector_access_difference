CXXFLAGS=-std=c++0x -DMEASURE_INT
CC=g++
vector_access_diff:
%:%.o
%.o:%.c
	$(CC) -c -o $@ $<
