CC = g++
CFLAGS = -g
all:End.o parse.o main.o
	${CC} ${CFLAGS} -o simulate End.o parse.o main.o
End.o:End.cpp End.h
	${CC} ${CFLAGS} End.cpp End.h -c
parse.o:parse.cpp parse.h
	$(CC) $(CFLAGS) parse.cpp parse.h -c
main.o:main.cpp End.h parse.h
	${CC} ${CFLAGS} main.cpp End.h parse.h -c
clean:
	rm -f *.o *.gch simulate

