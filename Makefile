CXX=clang++
CXXFLAGS=-Wall -fsanitize=address -g
LINKFLAGS=-fsanitize=address -g

.PHONY: all clean

all: program

program: main.o movies.o
	${CXX} ${LINKFLAGS} main.o movies.o -o program

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

movies.o: MovieCollection.cpp
	${CXX} ${CXXFLAGS} -c MovieCollection.cpp -o movies.o

clean:
	rm -rf program *.o