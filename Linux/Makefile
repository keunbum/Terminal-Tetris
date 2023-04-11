CC=cc
CFLAGS=-Wall -std=gnu17 -pthread -lrt
SRCDIR=src
OBJDIR=obj
BINDIR=bin
HDRDIR=src
INCLUDES=-I $(HDRDIR)
EXE=Tetris

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

debug: CFLAGS+=-g
debug: CFLAGS+=-DTETRIS_DEBUG
#debug: CFLAGS+=-Werror
#debug: CFLAGS+=-Wextra
debug: dev

test: CFLAGS+=-DUNIT_TEST
test: dev

testdebug: CFLAGS+=-DUNIT_TEST
testdebug: CFLAGS+=-DTETRIS_DEBUG
testdebug: dev

.PHONY: clean run depend

clean:
	clear
	rm -rf $(BINDIR)/* $(OBJDIR)/*

run:
	sudo ./$(BINDIR)/$(EXE)

rundebug:
	code ./err.txt
	sudo ./$(BINDIR)/$(EXE) 2> err.txt

# I don't think it's necessary, but I write it down for now.
depend:
	makedepend --$(CFLAGS)--$(INCLUDES)--$(SRC)--$(HDRDIR)
