CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

all: bin/testTableEntry bin/testHashTable

bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp HashTable.h TableEntry.h Dict.h
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/testHashTable testHashTable.cpp

clean:
	rm -rf bin

