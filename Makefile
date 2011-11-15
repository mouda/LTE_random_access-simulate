CC = g++
CFLAGS = -g
all:End.o main.o
	${CC} ${CFLAGS} -o simulate End.o main.o
End.o:End.cpp End.h
	${CC} ${CFLAGS} End.cpp End.h -c
main.o:main.cpp End.h
	${CC} ${CFLAGS} main.cpp End.h -c
clean:
	rm -f *.o *.gch simulate
