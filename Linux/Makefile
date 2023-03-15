CC = cc

CFLAGS = -Wall -Werror -std=gnu17 -pthread

SRCDIR = src
OBJDIR = obj
BINDIR = bin
HDRDIR = src

INCLUDES = -I $(HDRDIR)

EXE = tetris

SRC := $(shell find $(SRCDIR) -name '*.c')
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean run depend

dev: all

release: CFLAGS += -Wextra
release: dev

debug: CFLAGS += -DDEBUG
debug: dev

test: CFLAGS += -DTEST
test: dev

testdebug: CFLAGS += -DTEST
testdebug: CFLAGS += -DLOCAL
testdebug: dev

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/*

run:
	./$(BINDIR)/$(EXE) 2> err.txt

# hmm..
depend:
	makedepend --$(CFLAGS)--$(INCLUDES)--$(SRC)--$(HDRDIR)
