modules		:=code


.PHONY: all clean

all: $(modules)
	gcc -c ./code/main.c>./code/main.o ./code/fibo.c>./code/fibo.o -I ./include 
	gcc ./code/main.c ./code/fibo.c -o fibo -I ./include



clean:
	rm ./code/main.o
	rm ./code/fibo.o
