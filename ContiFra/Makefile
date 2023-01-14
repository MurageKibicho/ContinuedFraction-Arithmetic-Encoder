CC=gcc
CFLAGS= 
LIBS = -lm
all: main
profile: ContinuedFraction.c ContinuedFraction.h 
	$(CC) $(CFLAGS) -pg -o $@ $^ $(LIBS)
main: ContinuedFraction.c ContinuedFraction.h
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
clean:
	rm *.o 
