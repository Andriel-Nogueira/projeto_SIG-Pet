all:
		gcc -c -Wall *.h
		gcc -c -Wall *.c
		gcc -o sigpet *.o