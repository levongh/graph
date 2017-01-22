CC = g++
CPPFLAGS = -O3 -std=c++14
HEADERS = graph.h partition.h
SOURCES = graph.cpp main.cpp
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
