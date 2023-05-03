OUT = main.out
CC = g++
ODIR = obj
SDIR = src
INC = -Iinc

_CPPFS = $(shell find $(SDIR)/*.cpp)
_OBJS = $(foreach item,$(_CPPFS), $(item:$(SDIR)/%.cpp=%.o))

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

SHELL := /bin/bash

BUILD_ARGS = $(shell pkg-config  --cflags --libs ./build/*.pc)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(BUILD_ARGS) -c $(INC) -o $@ $< $(CFLAGS)

$(OUT): $(OBJS) build/conanbuild.sh
	$(CC) $(OBJS) $(BUILD_ARGS) -o $(OUT)

build/conanbuild.sh: conanfile.txt
	conan install . --output-folder=build --build=missing

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(OUT) build/*.sh build/*.conf build/*.pc

.PHONY: install
install: build/conanbuild.sh
