CC = g++
CFLAGS = -Wall -std=c++17
SOURCES_L = ./PrimL/PrimL.cpp ./Algo-Prim/VertexL.cpp ./Algo-Prim/VertexM.cpp ./Algo-Prim/AlgoPrim.cpp
SOURCES_M = ./PrimM/PrimM.cpp ./Algo-Prim/VertexL.cpp ./Algo-Prim/VertexM.cpp ./Algo-Prim/AlgoPrim.cpp

all: primL primM

primM: $(SOURCES_M:.cpp=.o)
	$(CC) $(CFLAGS) -o $@ $^

primL: $(SOURCES_L:.cpp=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del -f *.o primL.exe primM.exe