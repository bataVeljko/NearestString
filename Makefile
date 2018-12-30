CXXFLAGS = -Wall -std=c++14

nearestString : main.o closeststring.o
	g++ -o $@ $^

main.o : main.cpp closeststring.hpp
	g++ $(CXXFLAGS) -c $<

closeststring.o : closeststring.cpp closeststring.hpp
	g++ $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm nearestString *.o