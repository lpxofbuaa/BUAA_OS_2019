Main 	:= main.c
Fibo	:= fibo.c


all:
	gcc -c main.c fibo.c -I ../include

%.o: $(Main) $(Fibo)
	gcc -c $@ -I ../include
