CC = g++
CFLAGS = -g
all:End.o parse.o main.o specialfunctions.o alglibinternal.o ap.o
	${CC} ${CFLAGS} -o simulate End.o parse.o main.o specialfunctions.o alglibinternal.o ap.o
End.o:End.cpp End.h
	${CC} ${CFLAGS} End.cpp End.h -c
parse.o:parse.cpp parse.h
	$(CC) $(CFLAGS) parse.cpp parse.h -c
alglibinternal.o:alglibinternal.h alglibinternal.cpp 
	$(CC) $(CFLAGS) alglibinternal.h alglibinternal.cpp -c
ap.o:ap.h ap.cpp
	$(CC) $(CFLAGS) ap.h ap.cpp -c
specialfunctions.o:specialfunctions.h specialfunctions.cpp alglibinternal.h ap.h
	$(CC) $(CFLAGS) specialfunctions.h specialfunctions.cpp alglibinternal.h ap.h -c
main.o:main.cpp End.h parse.h specialfunctions.h
	${CC} ${CFLAGS} main.cpp End.h parse.h specialfunctions.h -c
clean:
	rm -f *.o *.gch simulate

