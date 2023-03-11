CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
BINDIR = bin
HDRDIR = src
EXEFILE = tetris

SOURCES := $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(EXEFILE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDRDIR)

.PHONY: clean run

clean:
	rm -rfv $(BINDIR)/* $(OBJDIR)/*

run:
	./$(BINDIR)/$(EXEFILE)