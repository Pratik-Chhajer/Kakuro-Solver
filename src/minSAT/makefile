1: main.o helper.o input_functions.o
	g++ main.o helper.o input_functions.o -o 1

main.o: main.cpp
	g++ -c main.cpp

helper.o: helper.cpp helper.h
	g++ -c helper.cpp

input_functions.o: input_functions.cpp input_functions.h
	g++ -c input_functions.cpp

clean:
	rm *.o 1