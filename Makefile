all: tests.exe

dynarr.o: dynarr.h dynarr.c
	gcc -c dynarr.c -o dynarr.o

tests.exe: tests.c dynarr.o
	gcc tests.c dynarr.o -o tests.exe

clean:
	del *.o *.exe