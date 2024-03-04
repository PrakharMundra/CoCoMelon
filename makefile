compile:
	gcc -c symbolTable.c
	gcc -c parseTree.c
	gcc -c lexer.c
	gcc -c stack.c
	gcc -c parser.c
	gcc -c driver.c
	gcc -o compiler lexer.o symbolTable.o stack.o parser.o parseTree.o driver.o
