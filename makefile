compile:
	gcc -c variables.c
	gcc -c symbolTable.c
	gcc -c parseTree.c
	gcc -c lexer.c
	gcc -c stack.c
	gcc -c parser.c
	gcc -c driver.c
	
	gcc -o compiler variables.o lexer.o symbolTable.o stack.o parseTree.o parser.o driver.o
