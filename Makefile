CPP = g++
CPPFLAGS = -g -Wall
LIBS =

TITLE = wagnventures
OBJS = main.o wagn.o item_base.o

all: $(TITLE)

$(TITLE): $(OBJS)
		$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
		$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
		rm -f $(TITLE) $(OBJS)

main.o: wagn.h
wagn.o: wagn.h item_base.h command.h space.h
item_base.o: item_types.h
