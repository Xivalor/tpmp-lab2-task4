all:
	gcc -Iinclude src/*.c -o program

clean:
	rm -f program

run:
	./program
