
CC := gcc
CFLAGS := #default none 

SRC := src
INC := src/include
SBIN := src/bin

TEST := tests
TBIN := tests/bin

default: all


# compile sources

HASHDEPS := $(SRC)/hash.c $(INC)/hash.h
HASHTARG := $(SBIN)/hash.o

$(HASHTARG): $(HASHDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


DATACONTDEPS := $(SRC)/datacont.c $(INC)/datacont.h
DATACONTTARG := $(SBIN)/datacont.o

$(DATACONTTARG): $(DATACONTDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


TREENODEDEPS := $(SRC)/treenode.c $(INC)/treenode.h
TREENODETARG := $(SBIN)/treenode.o

$(TREENODETARG): $(TREENODEDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


TREESETDEPS := $(SRC)/treeset.c $(INC)/treeset.h
TREESETTARG := $(SBIN)/treeset.o

$(TREESETTARG): $(TREESETDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


HASHSETDEPS := $(SRC)/hashset.c $(INC)/hashset.h
HASHSETTARG := $(SBIN)/hashset.o

$(HASHSETTARG): $(HASHSETDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


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


.PHONY: all
all: run_tests
	@echo "All tests passed. Building shared libs..."
	@$(MAKE) static_lib
	@$(MAKE) dynamic_lib
	@echo "Done."


.PHONY: clean
clean:
	rm -f *.a
	rm -f *.so
	rm -f src/bin/*.o
	rm -f tests/bin/*.out


.PHONY: run_tests
run_tests: tests
	@./runtests.sh


.PHONY: tests
tests: $(DATACONTTESTTARG) $(TREENODETESTTARG) $(TREESETTESTTARG) $(HASHSETTESTTARG)
	@echo Finished building tests.


.PHONY: static_lib
static_lib: $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	ar rcs libkylestructs.a $(SBIN)/*.o

set_flags:
	CFLAGS=-fPIC

.PHONY: dynamic_lib
dynamic_lib: clean set_flags $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	gcc -shared $(SBIN)/*.o -o libkylestructs.so


