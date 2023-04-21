.PHONY: program

run: program
	./program

program:
	gcc ./main.c $(wildcard ./table/*.c) $(wildcard ./table/**/*.c) $(flags) -o $@