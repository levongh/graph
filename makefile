CC = g++
CPPFLAGS = -O1 -std=c++14 -Wall -Werror -g
HEADERS = graph.h partition.h kernigan_lin.h fiduccia_mattheyses.h partition_manager.h graph_input.h timer.h simulated_annealing.h
SOURCES = graph.cpp partition.cpp main.cpp kernigan_lin.cpp  fiduccia_mattheyses.cpp partition_manager.cpp graph_input.cpp simulated_annealing.cpp

VPATH = task_sheduler

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
