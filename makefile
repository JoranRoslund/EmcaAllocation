all: sp521.exe

sp521.exe: bbrs.o test.o
	g++ -o sp521.exe -g test.o bbrs.o

bbrs.o: bbrs.cpp
	gcc -c -std=gnu++0x bbrs.cpp

test.o: test.cpp
	gcc -c -std=gnu++0x test.cpp
clean:
	rm -f *.o *e.exe
