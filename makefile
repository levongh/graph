CC = g++
CPPFLAGS = -O1 -std=c++14 -Wall -g
HEADERS = graph.h partition.h kernigan_lin.h graph_input.h fiduccia_mattheyses.h partition_manager.h
SOURCES = graph.cpp partition.cpp main.cpp kernigan_lin.cpp graph_input.cpp fiduccia_mattheyses.cpp partition_manager.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = graph_project

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS): $(HEADERS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) $(SOURCES) -c

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
