CPP = g++
CPPFLAGS = -g -Wall -std=gnu++11 -O0 -frtti -I./yaml-cpp-0.5.1/include
LIBS =

TITLE = wagnventures
OBJS = main.o wagn.o item_base.o command.o space.o generation.o parser.o

YAML_OBJS = yaml-cpp-0.5.1/src/binary.o \
yaml-cpp-0.5.1/src/convert.o            \
yaml-cpp-0.5.1/src/directives.o         \
yaml-cpp-0.5.1/src/emit.o               \
yaml-cpp-0.5.1/src/emitfromevents.o     \
yaml-cpp-0.5.1/src/emitter.o            \
yaml-cpp-0.5.1/src/emitterstate.o       \
yaml-cpp-0.5.1/src/emitterutils.o       \
yaml-cpp-0.5.1/src/exp.o                \
yaml-cpp-0.5.1/src/memory.o             \
yaml-cpp-0.5.1/src/node.o               \
yaml-cpp-0.5.1/src/node_data.o          \
yaml-cpp-0.5.1/src/nodebuilder.o        \
yaml-cpp-0.5.1/src/nodeevents.o         \
yaml-cpp-0.5.1/src/null.o               \
yaml-cpp-0.5.1/src/ostream_wrapper.o    \
yaml-cpp-0.5.1/src/parse.o              \
yaml-cpp-0.5.1/src/parser.o             \
yaml-cpp-0.5.1/src/regex.o              \
yaml-cpp-0.5.1/src/scanner.o            \
yaml-cpp-0.5.1/src/scanscalar.o         \
yaml-cpp-0.5.1/src/scantag.o            \
yaml-cpp-0.5.1/src/scantoken.o          \
yaml-cpp-0.5.1/src/simplekey.o          \
yaml-cpp-0.5.1/src/singledocparser.o    \
yaml-cpp-0.5.1/src/stream.o             \
yaml-cpp-0.5.1/src/tag.o

all: $(TITLE)

$(TITLE): $(OBJS) yaml.a
		$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
		$(CPP) $(CPPFLAGS) -c -o $@ $<

yaml.a: $(YAML_OBJS)
	ar rsu $@ $^

clean:
		rm -f $(TITLE) $(OBJS) wagnventures.exe

clean-all: clean
	rm -f yaml.a $(YAML_OBJS)

main.o: main.h wagn.h command.h
wagn.o: wagn.h item_base.h command.h space.h generation.h
item_base.o: item_base.h item_types.h
command.o: command.h wagn.h
space.o: space.h item_base.h
generation.o: generation.h item_base.h space.h
parser.o: parser.h generation.h item_base.h space.h
