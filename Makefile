CPP = g++
CPPFLAGS = -g -Wall -std=gnu++11 -O0
LIBS =

TITLE = wagnventures
OBJS = main.o wagn.o item_base.o command.o space.o

all: $(TITLE)

$(TITLE): $(OBJS)
		$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
		$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
		rm -f $(TITLE) $(OBJS)

main.o: main.h wagn.h command.h
wagn.o: wagn.h item_base.h command.h space.h
item_base.o: item_types.h
command.o: wagn.h
space.o: item_base.h
