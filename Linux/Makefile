CC=cc
CFLAGS=-Wall -std=gnu17 -pthread
SRCDIR=src
OBJDIR=obj
BINDIR=bin
HDRDIR=src
INCLUDES=-I $(HDRDIR)
EXE=tetris

SRC:=$(shell find $(SRCDIR) -name '*.c')
OBJ:=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(EXE): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(BINDIR)/$(EXE)

dev: all

release: CFLAGS+=-Werror
release: CFLAGS+=-Wextra
release: dev

debug: CFLAGS+=-DDEBUG
debug: dev

test: CFLAGS+=-DTEST
test: dev

testdebug: CFLAGS+=-DTEST
testdebug: CFLAGS+=-DDEBUG
testdebug: dev

.PHONY: clean run depend

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/*

run:
	./$(BINDIR)/$(EXE) 2> err.txt

# I don't think it's necessary, but I write it down for now.
depend:
	makedepend --$(CFLAGS)--$(INCLUDES)--$(SRC)--$(HDRDIR)
