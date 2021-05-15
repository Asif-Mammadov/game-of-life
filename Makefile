CC = gcc
CFLAGS = -Wall
EXEC = game
OBJ = $(patsubst %.c, %.o, $(wildcard *.c)) 

all: $(EXEC)

clean: 
	rm -f *.o game -r doc dist

doc: 
	doxygen

dist: 
	mkdir -p dist && tar cvzf dist/life-1.0.tar.gz --exclude-from=.gitignore *

%.o: %.c
	$(CC) -c $< 

$(EXEC): $(OBJ)
	$(CC)  $^ -o $@ $(CFLAGS)