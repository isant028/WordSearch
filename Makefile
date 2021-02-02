CC = gcc

all:
	$(CC) -o a.exe wordsearch.c

clean:
	rm -f a.exe

run: 
	./wordsearch puzzle1.txt