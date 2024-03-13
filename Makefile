CC = gcc
CXX = g++

CSRCS = $(wildcard src/*.c)
CXXSRCS = $(wildcard src/*.cpp)

LIBCSRC = $(wildcard lib/*.c)
LIBCXXSRC = $(wildcard lib/*.cpp)

LIBCOBJ = $(patsubst lib/%.c, obj/lib/%.obj, $(LIBCSRC))
LIBCXXOBJ = $(patsubst lib/%.cpp, obj/lib/%cpp.obj, $(LIBCXXSRC))

COBJ = $(patsubst src/%.c, obj/%.obj, $(CSRCS))
CXXOBJ = $(patsubst src/%.cpp, obj/%cpp.obj, $(CXXSRCS))

CPROGS = $(patsubst src/%.c, bin/%.exe, $(CSRCS))
CXXPROGS = $(patsubst src/%.cpp, bin/%cpp.exe, $(CXXSRCS))

CCOMMONFLAGS = -g -O0
CFLAGS = -std=gnu17
CXXFLAGS = -std=gnu++17

LFLAGS = 

all: $(CPROGS) $(CXXPROGS)

%: bin/%.exe
	./$^

bin/%.exe: obj/%.obj $(LIBCOBJ) $(LIBCXXOBJ)
	$(CXX) $(LFLAGS) -o $@ $< $(LIBCOBJ) $(LIBCXXOBJ)

.PRECIOUS: obj/%.obj
obj/%.obj: src/%.c
	$(CC) $(CCOMMONFLAGS) $(CFLAGS) -c -o $@ $<

.PRECIOUS: obj/%cpp.obj
obj/%cpp.obj: src/%.cpp
	$(CXX) $(CCOMMONFLAGS) $(CXXFLAGS) -c -o $@ $<

.PRECIOUS: obj/lib/%.obj
obj/lib/%.obj: lib/%.c
	$(CC) $(CCOMMONFLAGS) $(CFLAGS) -c -o $@ $<

.PRECIOUS: obj/lib/%cpp.obj
obj/lib/%cpp.obj: lib/%.cpp
	$(CXX) $(CCOMMONFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f -v ./obj/*.obj
	rm -f -v ./obj/lib/*.obj
	rm -f -v ./bin/*