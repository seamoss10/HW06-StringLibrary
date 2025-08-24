# ---- Compiler & flags -------------------------------------------------------
CC       := gcc
WARNINGS := -Wall -Wshadow -pedantic
ERRORS   := -Wvla -Werror

CFLAGS  += -std=c11 -g $(WARNINGS) $(ERRORS) -MMD -MP
LDFLAGS ?=
LDLIBS  ?=

# ---- Project layout ---------------------------------------------------------
PROG := stringm
SRCS := main.c stringm.c
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

.DEFAULT_GOAL := $(PROG)

# ---- Build rules ------------------------------------------------------------
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

# ---- Test helpers -----------------------------------------------------------
.PHONY: testall test test% leakcheck leakcheck% clean

testall: test
test: $(PROG)
	./$(PROG) -1

# E.g. `make test5` runs ./stringm 5
test%: $(PROG)
	./$(PROG) $*

# Valgrind helpers
VALGRIND ?= valgrind --leak-check=full --show-leak-kinds=all
leakcheck: $(PROG)
	$(VALGRIND) ./$(PROG) -1
leakcheck%: $(PROG)
	$(VALGRIND) ./$(PROG) $*

# ---- Housekeeping -----------------------------------------------------------
clean:
	$(RM) $(PROG) $(OBJS) $(DEPS)
