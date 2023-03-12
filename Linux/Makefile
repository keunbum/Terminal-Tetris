CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
BINDIR = bin
HDRDIR = src
EXEFILE = tetris

SRC := $(shell find $(SRCDIR) -name '*.c')
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(EXEFILE): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDRDIR)

.PHONY: clean

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/*