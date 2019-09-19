
CC := gcc
CFLAGS := -fPIC 

SRC := src
INC := src/include
SBIN := src/bin

TEST := tests
TBIN := tests/bin

INCLOC := /usr/include/kylestructs
LIBLOC := /usr/lib/

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
	$(CC) -g $^ -o $@


TESTDEPS += $(TREENODETARG)
TREENODETESTTARG := $(TBIN)/treenode_tests.out

$(TREENODETESTTARG): $(TEST)/treenode_tests.c $(TESTDEPS)
	$(CC) -g $^ -o $@


TESTDEPS += $(TREESETTARG)
TREESETTESTTARG := $(TBIN)/treeset_tests.out

$(TREESETTESTTARG): $(TEST)/treeset_tests.c $(TESTDEPS)
	$(CC) -g $^ -o $@


TESTDEPS += $(HASHSETTARG)
HASHSETTESTTARG := $(TBIN)/hashset_tests.out

$(HASHSETTESTTARG): $(TEST)/hashset_tests.c $(TESTDEPS)
	$(CC) -g $^ -o $@



.PHONY: run_tests
run_tests: tests
	./runtests.sh


.PHONY: tests
tests: $(DATACONTTESTTARG) $(TREENODETESTTARG) $(TREESETTESTTARG) $(HASHSETTESTTARG)
	@echo Finished building tests.


STATICLIB := libkylestructs.a
$(STATICLIB): $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	ar rcs $(STATICLIB) $(SBIN)/*.o


DYNAMICLIB := libkylestructs.so
$(DYNAMICLIB): $(HASHTARG) $(DATACONTTARG) $(TREENODETARG) $(TREESETTARG) $(HASHSETTARG)
	gcc -shared $(SBIN)/*.o -o $(DYNAMICLIB)


.PHONY: install
install: $(STATICLIB) $(DYNAMICLIB)
	mkdir $(INCLOC)
	cp $(INC)/* $(INCLOC)
	cp $(STATICLIB) $(LIBLOC)
	cp $(DYNAMICLIB) $(LIBLOC)


.PHONY: uninstall
uninstall:
	if [ -d "$(INCLOC)" ]; then rm -r $(INCLOC); fi;
	if [ -f "$(LIBLOC)/$(STATICLIB)" ]; then rm $(LIBLOC)/$(STATICLIB); fi;
	if [ -f "$(LIBLOC)/$(DYNAMICLIB)" ]; then rm $(LIBLOC)/$(DYNAMICLIB); fi;


.PHONY: clean
clean:
	if [ -f $(STATICLIB) ]; then rm $(STATICLIB); fi;
	if [ -f $(DYNAMICLIB) ]; then rm $(DYNAMICLIB); fi;
	if [ -f $(HASHTARG) ]; then rm $(HASHTARG); fi;
	if [ -f $(DATACONTTARG) ]; then rm $(DATACONTTARG); fi;
	if [ -f $(TREENODETARG) ]; then rm $(TREENODETARG); fi;
	if [ -f $(TREESETTARG) ]; then rm $(TREESETTARG); fi;
	if [ -f $(HASHSETTARG) ]; then rm $(HASHSETTARG); fi;


.PHONY: all
all: run_tests
	@echo "All tests passed."
	@echo "Building static libs..."
	$(MAKE) $(STATICLIB)
	@echo "Done."
	@echo "Building shared libs..."
	$(MAKE) $(DYNAMICLIB)
	@echo "Done."


