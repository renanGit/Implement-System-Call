all: test

test: test_pinfo.o
	gcc test_pinfo.o -o test

test.o: test_pinfo.c
	gcc -c test_pinfo.c

clean:
	rm -rf *.o test

