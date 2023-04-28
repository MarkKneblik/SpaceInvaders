BINS = spaceinvaders

CFLAGS = -g -Wall -Wstrict-prototypes

LDFLAGS = -g

.PHONY: default
default: $(BINS)


spaceinvaders.o : main.cpp invaderManager.h playerShip.h alienShip.h
	g++ $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f core* *.o *~

spaceinvaders : spaceinvaders.o
	g++ $(LDFLAGS) $^ -lpthread -lncurses -o $@


.PHONY: immaculate
immaculate: clean
	rm -f $(BINS)

