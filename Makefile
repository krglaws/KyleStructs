
CC := gcc
CFLAGS := -fPIC 

SRC := src
INC := src/include
SBIN := src/bin

TEST := tests
TBIN := tests/bin

INCLOC := /usr/include/kylestructs
LIBLOC := /usr/lib

default: all


# compile sources

DATACONTDEPS := $(SRC)/datacont.c 
DATACONTTARG := $(SBIN)/datacont.o

$(DATACONTTARG): $(DATACONTDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


LISTNODEDEPS := $(SRC)/listnode.c
LISTNODETARG := $(SBIN)/listnode.o

$(LISTNODETARG): $(LISTNODEDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


LISTDEPS := $(SRC)/list.c
LISTTARG := $(SBIN)/list.o

$(LISTTARG): $(LISTDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


QUEUEDEPS := $(SRC)/queue.c
QUEUETARG := $(SBIN)/queue.o

$(QUEUETARG): $(QUEUEDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


STACKDEPS := $(SRC)/stack.c
STACKTARG := $(SBIN)/stack.o

$(STACKTARG): $(STACKDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


TREESETNODEDEPS := $(SRC)/treesetnode.c
TREESETNODETARG := $(SBIN)/treesetnode.o

$(TREESETNODETARG): $(TREESETNODEDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


TREESETDEPS := $(SRC)/treeset.c 
TREESETTARG := $(SBIN)/treeset.o

$(TREESETTARG): $(TREESETDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


HASHSETDEPS := $(SRC)/hashset.c 
HASHSETTARG := $(SBIN)/hashset.o

$(HASHSETTARG): $(HASHSETDEPS) 
	$(CC) -c $< -o $@ $(CFLAGS)


TREEMAPNODEDEPS := $(SRC)/treemapnode.c 
TREEMAPNODETARG := $(SBIN)/treemapnode.o

$(TREEMAPNODETARG): $(TREEMAPNODEDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


TREEMAPDEPS := $(SRC)/treemap.c 
TREEMAPTARG := $(SBIN)/treemap.o

$(TREEMAPTARG): $(TREEMAPDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)


HASHMAPDEPS := $(SRC)/hashmap.c 
HASHMAPTARG := $(SBIN)/hashmap.o

$(HASHMAPTARG): $(HASHMAPDEPS)
	$(CC) -c $< -o $@ $(CFLAGS)



# compile tests

DATACONTTESTDEPS := $(DATACONTDEPS)
DATACONTTESTTARG := $(TBIN)/datacont_tests.out

$(DATACONTTESTTARG): $(TEST)/datacont_tests.c $(DATACONTTESTDEPS)
	$(CC) -g $^ -o $@


LISTNODETESTDEPS := $(DATACONTTESTDEPS) $(LISTNODEDEPS) 
LISTNODETESTTARG := $(TBIN)/listnode_tests.out

$(LISTNODETESTTARG): $(TEST)/listnode_tests.c $(LISTNODETESTDEPS)
	$(CC) -g $^ -o $@


LISTTESTDEPS := $(LISTNODETESTDEPS) $(LISTDEPS)
LISTTESTTARG := $(TBIN)/list_tests.out

$(LISTTESTTARG): $(TEST)/list_tests.c $(LISTTESTDEPS)
	$(CC) -g $^ -o $@


QUEUETESTDEPS := $(LISTNODETESTDEPS) $(QUEUEDEPS)
QUEUETESTTARG := $(TBIN)/queue_tests.out

$(QUEUETESTTARG): $(TEST)/queue_tests.c $(QUEUETESTDEPS)
	$(CC) -g $^ -o $@


STACKTESTDEPS := $(LISTNODETESTDEPS) $(STACKDEPS)
STACKTESTTARG := $(TBIN)/stack_tests.out

$(STACKTESTTARG): $(TEST)/stack_tests.c $(STACKTESTDEPS) 
	$(CC) -g $^ -o $@


TREESETNODETESTDEPS := $(LISTNODETESTDEPS) $(TREESETNODEDEPS)
TREESETNODETESTTARG := $(TBIN)/treesetnode_tests.out

$(TREESETNODETESTTARG): $(TEST)/treesetnode_tests.c $(TREESETNODETESTDEPS)
	$(CC) -g $^ -o $@


TREESETTESTDEPS := $(TREESETNODETESTDEPS) $(TREESETDEPS)
TREESETTESTTARG := $(TBIN)/treeset_tests.out

$(TREESETTESTTARG): $(TEST)/treeset_tests.c $(TREESETTESTDEPS)
	$(CC) -g $^ -o $@


HASHSETTESTDEPS := $(TREESETTESTDEPS) $(HASHSETDEPS)
HASHSETTESTTARG := $(TBIN)/hashset_tests.out

$(HASHSETTESTTARG): $(TEST)/hashset_tests.c $(HASHSETTESTDEPS)
	$(CC) -g $^ -o $@


TREEMAPNODETESTDEPS := $(LISTNODETESTDEPS) $(TREEMAPNODEDEPS)
TREEMAPNODETESTTARG := $(TBIN)/treemapnode_tests.out

$(TREEMAPNODETESTTARG): $(TEST)/treemapnode_tests.c $(TREEMAPNODETESTDEPS)
	$(CC) -g $^ -o $@


TREEMAPTESTDEPS := $(TREEMAPNODETESTDEPS) $(TREEMAPDEPS)
TREEMAPTESTTARG := $(TBIN)/treemap_tests.out

$(TREEMAPTESTTARG): $(TEST)/treemap_tests.c $(TREEMAPTESTDEPS)
	$(CC) -g $^ -o $@


HASHMAPTESTDEPS += $(TREEMAPTESTDEPS) $(HASHMAPDEPS)
HASHMAPTESTTARG := $(TBIN)/hashmap_tests.out

$(HASHMAPTESTTARG): $(TEST)/hashmap_tests.c $(HASHMAPTESTDEPS)
	$(CC) -g $^ -o $@


.PHONY: run_tests
run_tests: tests
	./runtests.sh


.PHONY: tests
tests: $(DATACONTTESTTARG) $(LISTNODETESTTARG) $(LISTTESTTARG) $(QUEUETESTTARG) $(STACKTESTTARG)\
	$(TREESETNODETESTTARG) $(TREESETTESTTARG) $(HASHSETTESTTARG) $(TREEMAPNODETESTTARG)\
	$(TREEMAPTESTTARG) $(HASHMAPTESTTARG)
	@echo Finished building tests.


STATICLIB := libkylestructs.a
$(STATICLIB): $(DATACONTTARG) $(LISTNODETARG) $(LISTTARG) $(QUEUETARG) $(STACKTARG) $(TREESETNODETARG)\
	$(TREESETTARG) $(HASHSETTARG) $(TREEMAPNODETARG) $(TREEMAPTARG) $(HASHMAPTARG)
	ar rcs $(STATICLIB)\
		$(DATACONTTARG)\
		$(LISTNODETARG)\
		$(LISTTARG)\
		$(QUEUETARG)\
		$(STACKTARG)\
		$(TREESETNODETARG)\
		$(TREESETTARG)\
		$(HASHSETTARG)\
		$(TREEMAPNODETARG)\
		$(TREEMAPTARG)\
		$(HASHMAPTARG)


DYNAMICLIB := libkylestructs.so
$(DYNAMICLIB): $(DATACONTTARG) $(LISTNODETARG) $(LISTTARG) $(QUEUETARG) $(STACKTARG) $(TREESETNODETARG)\
		$(TREESETTARG) $(HASHSETTARG) $(LISTNODETARG) $(TREEMAPNODETARG) $(TREEMAPTARG) $(HASHMAPTARG)
	gcc -shared -o $(DYNAMICLIB)\
		$(DATACONTTARG)\
		$(LISTNODETARG)\
		$(LISTTARG)\
		$(QUEUETARG)\
		$(STACKTARG)\
		$(TREESETNODETARG)\
		$(TREESETTARG)\
		$(HASHSETTARG)\
		$(TREEMAPNODETARG)\
		$(TREEMAPTARG)\
		$(HASHMAPTARG)


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
	if [ -f $(DATACONTTARG) ]; then rm $(DATACONTTARG); fi;
	if [ -f $(DATACONTTESTTARG) ]; then rm $(DATACONTTESTTARG); fi;
	if [ -f $(LISTNODETARG) ]; then rm $(LISTNODETARG); fi;
	if [ -f $(LISTNODETESTTARG) ]; then rm $(LISTNODETESTTARG); fi;
	if [ -f $(LISTTARG) ]; then rm $(LISTTARG); fi;
	if [ -f $(LISTTESTTARG) ]; then rm $(LISTTESTTARG); fi;
	if [ -f $(QUEUETESTTARG) ]; then rm $(QUEUETESTTARG); fi;
	if [ -f $(QUEUETARG) ]; then rm $(QUEUETARG); fi;
	if [ -f $(STACKTARG) ]; then rm $(STACKTARG); fi;
	if [ -f $(STACKTESTTARG) ]; then rm $(STACKTESTTARG); fi;
	if [ -f $(TREESETNODETARG) ]; then rm $(TREESETNODETARG); fi;
	if [ -f $(TREESETNODETESTTARG) ]; then rm $(TREESETNODETESTTARG); fi;
	if [ -f $(TREESETTARG) ]; then rm $(TREESETTARG); fi;
	if [ -f $(TREESETTESTTARG) ]; then rm $(TREESETTESTTARG); fi;
	if [ -f $(HASHSETTARG) ]; then rm $(HASHSETTARG); fi;
	if [ -f $(HASHSETTESTTARG) ]; then rm $(HASHSETTESTTARG); fi;
	if [ -f $(TREEMAPNODETARG) ]; then rm $(TREEMAPNODETARG); fi;
	if [ -f $(TREEMAPNODETESTTARG) ]; then rm $(TREEMAPNODETESTTARG); fi;
	if [ -f $(TREEMAPTARG) ]; then rm $(TREEMAPTARG); fi;
	if [ -f $(TREEMAPTESTTARG) ]; then rm $(TREEMAPTESTTARG); fi;
	if [ -f $(HASHMAPTARG) ]; then rm $(HASHMAPTARG); fi;
	if [ -f $(HASHMAPTESTTARG) ]; then rm $(HASHMAPTESTTARG); fi;


.PHONY: all
all: run_tests
	@echo "All tests passed."
	@echo "Building static libs..."
	$(MAKE) $(STATICLIB)
	@echo "Done."
	@echo "Building shared libs..."
	$(MAKE) $(DYNAMICLIB)
	@echo "Done."


