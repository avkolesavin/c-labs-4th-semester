.PHONY: program program-cli test

run: program
	./program

cli: program-cli
	./program-cli

program:
	gcc ./main.c $(wildcard ./tree/*.c) $(wildcard ./tree/**/*.c) $(flags) -o $@

program-cli:
	gcc ./main-cli.c $(wildcard ./tree/*.c) $(wildcard ./tree/**/*.c) $(flags) -o $@

test:
	gcc ./test.c -o test && ./test