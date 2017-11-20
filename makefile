all: hw.c
	gcc -o hw hw.c

run: all
	./hw

clean:
	rm -f *~ hw
