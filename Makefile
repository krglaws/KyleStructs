
CC := gcc

SRC := src
INC := src/include
SBIN := src/bin

TEST := tests
TBIN := tests/bin

ERR := 0

# compile sources

HASHDEPS := $(SRC)/hash.c $(INC)/hash.h
HASHTARG := $(SBIN)/hash.o

$(HASHTARG): $(HASHDEPS)
	$(CC) -c $< -o $@


DATACONTDEPS := $(SRC)/datacont.c $(INC)/datacont.h
DATACONTTARG := $(SBIN)/datacont.o

$(DATACONTTARG): $(DATACONTDEPS)
	$(CC) -c $< -o $@


TREENODEDEPS := $(SRC)/treenode.c $(INC)/treenode.h
TREENODETARG := $(SBIN)/treenode.o

$(TREENODETARG): $(TREENODEDEPS) 
	$(CC) -c $< -o $@


TREESETDEPS := $(SRC)/treeset.c $(INC)/treeset.h
TREESETTARG := $(SBIN)/treeset.o

$(TREESETTARG): $(TREESETDEPS) 
	$(CC) -c $< -o $@


HASHSETDEPS := $(SRC)/hashset.c $(INC)/hashset.h
HASHSETTARG := $(SBIN)/hashset.o

$(HASHSETTARG): $(HASHSETDEPS) 
	$(CC) -c $< -o $@


# compile tests

TESTDEPS := $(DATACONTTARG) $(HASHTARG)
DATACONTTESTTARG := $(TBIN)/datacont_tests.out

$(DATACONTTESTTARG): $(TEST)/datacont_tests.c $(TESTDEPS)
	$(CC) $^ -o $@


TESTDEPS += $(TREENODETARG)
TREENODETESTTARG := $(TBIN)/treenode_tests.out

$(TREENODETESTTARG): $(TEST)/treenode_tests.c $(TESTDEPS)
	$(CC) $^ -o $@


TESTDEPS += $(TREESETTARG)
TREESETTESTTARG := $(TBIN)/treeset_tests.out

$(TREESETTESTTARG): $(TEST)/treeset_tests.c $(TESTDEPS)
	$(CC) $^ -o $@


TESTDEPS += $(HASHSETTARG)
HASHSETTESTTARG := $(TBIN)/hashset_tests.out

$(HASHSETTESTTARG): $(TEST)/hashset_tests.c $(TESTDEPS)
	$(CC) $^ -o $@


# make libs

static_lib: $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	ar rcs libkylestructs.a $(SBIN)/*.o


dynamic_lib: $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	gcc -shared $(SBIN)/*.o -o libkylestructs.so


tests: $(DATACONTTESTTARG) $(TREENODETESTTARG) $(TREESETTARG) $(HASHSETTARG)


run_tests: $(tests)
	./runtests.sh

all: tests run_tests
	@if [ "$ERR" = "0" ]; then echo "All tests pass. Building shared libs..."; $(MAKE) static_lib; $(MAKE) dynamic_lib; echo "done."; fi;

clean:
	rm -f *.a
	rm -f *.so
	rm -f src/bin/*.o
	rm -f tests/bin/*.out

.PHONY: static_lib dynamic_lib tests run_tests all clean
