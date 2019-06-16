CC := gcc

HDRS := src/main.h src/search.h src/sort.h src/tree.h src/hashmap.h

SRCS := src/main.c src/search.c src/sort.c src/tree.c src/hashmap.c

OBJS := $(subst src/,bin/,$(subst .c,.o,$(SRCS)))

EXEC := bin/exe

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS)

$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(subst bin/,src/,$(@:.o=.c)) -c 

all: $(EXEC)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
