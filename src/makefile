SOURCS = graph.cpp \
		 vertex.cpp \
		 graphinput.cpp \
		 partitionmanager.cpp \
		 partition.cpp \
		 simulatedannealing.cpp \
		 fiducciamattheyses.cpp \
		 kerniganlin.cpp \
		 main.cpp

OBJDIR        = ../obj
INCLUDEDIR    = ../include
OBJECTS       = $(SOURCS:.cpp=.o)
MOVED_OBJECTS = $(adprefix ./$(OBJDIR)/,$(OBJECTS))
CC = g++
CPPFLAGS = -std=c++14 -c -Wall -Werror -O3

.PHONY: clean all
all: $(OBJECTS) $(SOURCS)
	mkdir -p $(OBJDIR)
	mv *.o $(OBJDIR)

.cpp.o:
	$(CC) -I$(INCLUDEDIR) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)
