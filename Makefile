all: 
	gcc encrypt.c key.c -g -o encrypt -O3 -w
	gcc brute.c key.c -g -o brute -O3 -w
	gcc decrypt.c key.c hash.c -g -o decrypt -O3 -w

clean:
	rm -f brute decrypt encrypt