
output: Lab3.o
	g++ Lab3.o -o output

my_da_array_use.o: Lab3.cpp
	g++ -c Lab3.cpp

clean:
	rm *.o output