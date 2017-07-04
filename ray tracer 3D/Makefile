Main: Main.o World.o Polygon.o
	g++ -ansi -Wall -o proj1 Main.o World.o Polygon.o

Main.o: Main.cpp World.h
	g++ -ansi -Wall -g -c Main.cpp

World.o: World.cpp World.h Polygon.h
	g++ -ansi -Wall -g -c World.cpp

Polygon.o: Polygon.cpp Polygon.h Ray.h
	g++ -ansi -Wall -g -c Polygon.cpp

slVector.o: slVector.cpp slVector.H slIO.H
	g++ -ansi -Wall -g -c slVector.cpp slIO.H

run:
	./proj1 $(INPUT) $(OUTPUT)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#
	rm proj1