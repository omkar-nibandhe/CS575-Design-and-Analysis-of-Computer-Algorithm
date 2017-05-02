all: brute backtrack

brute: brute.c
	gcc -Wall -g -std=c11 -o brute.out -lm brute.c

backtrack: backtrack.c
	gcc -Wall -g -std=c11 -lm -o backtrack.out backtrack.c


clean:
	rm -rf brute.out
	rm -rf brute_output.txt
	rm -rf backtrack.out
	rm -rf backtrack_output.txt 
