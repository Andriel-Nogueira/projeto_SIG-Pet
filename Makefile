
all:
	gcc -Wall -c agendamentos/*.c
	gcc -Wall -c clientes/*.c
	gcc -Wall -c produtos/*.c
	gcc -Wall -c servicos/*.c
	gcc -Wall -c vendas/*.c
	gcc -Wall -c relatorios/*.c
	gcc -Wall -c utilitarios/*.c
	gcc -Wall -c projeto.c
	gcc -o sigpet *.o

clean:
	rm -f *.o 

run: all 
	make clean
	./sigpet
	