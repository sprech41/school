Driver: Driver.o MMheap.o
	g++ -ansi -Wall -o proj4 Driver.o MMheap.o

Driver.o: Driver.cpp MMheap.cpp
	g++ -ansi -Wall -c Driver.cpp

MMheap.o: MMheap.cpp MMheap.h MyException.h
	g++ -ansi -Wall -c MMheap.cpp MyException.h

run:
	./proj4 $(FILE)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
	rm proj4