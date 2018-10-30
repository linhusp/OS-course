CC=gcc

%.o: %.c
	$(CC) -c $@ $<

all: lib1.o lib2.o selects.o
	ar cr libs.a lib1.o lib2.o && $(CC) -o selects selects.o libs.a
