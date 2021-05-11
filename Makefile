CC = gcc

all: game

clean: 
	rm -f *.o game -r doc dist

doc: 
	doxygen

dist: 
	mkdir -p dist && tar cvzf dist/life-1.0.tar.gz --exclude-from=.gitignore *

%.o: %.c
	$(CC) -c $< 

game: main.o ansi.o
	$(CC)  $^ -o $@