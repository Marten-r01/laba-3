gcc

all: main.exe
 main.exe: main.o
	gcc -o main.exe main.o
main.o: main.c
	gcc -c main.c
func.o: func.c
	gcc -c func.c
clean:
	rm main.o main.exe