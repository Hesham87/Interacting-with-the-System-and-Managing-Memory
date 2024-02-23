CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
OBJS=test.o deck.o eval.o cards.o hash.o
PROGRAM=test

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c deck.h
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
