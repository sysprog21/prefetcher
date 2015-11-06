CFLAGS = -msse2 --std gnu99 -O0 -Wall

all: main.c
	$(CC) $(CFLAGS) -o main main.c

clean:
	$(RM) main
