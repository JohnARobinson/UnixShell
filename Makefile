wish: wish.c built_in.c commands.c wish.o built_in.o commands.o
	gcc -c wish.c
	gcc -c built_in.c
	gcc -c commands.c
	gcc -o wish wish.o built_in.o commands.o
wish.o: wish.c
	gcc -c wish.c
built_in.o: built_in.c
	gcc -c built_in.c
commands.o: commands.c
	gcc -c commands.c

