all:End.o main.o
	g++ -o simulate End.o main.o
End.o:main.cpp End.h
	g++ main.cpp End.h -c
main.o:End.h End.cpp
	g++ End.cpp End.h -c

clean:
	rm -f *.o
