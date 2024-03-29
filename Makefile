CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
OBJS=main.o deck.o eval.o cards.o hash.o input.o future.o
PROGRAM=main

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c deck.h
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
