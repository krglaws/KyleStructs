# KyleStructs
This is a C library I am working on to satisfy my own curiosity as to how simple data structures like tree sets and hash sets might be implemented.

Here are some visual examples of the data structures I have implemented so far:

![Treeset](/samples/treeset.png)

My implementation of a tree set is essentially a collection of linked `treenode` structs organized into a binary search tree. Each `treenode` contains a pointer to another struct called `datacont` (aka data container), which is able to contain a multitude of basic data types. This way, a treeset can contain almost any kind of data without having to be rewritten for each type.

![Hashset](/samples/hashset.png)

A hash set is just a `hashset` struct that contains an array of nicely distributed (hopefully) tree sets. Each new `datacont` is placed in the hashset by generating the hash of its contained value, modding the hash value with the length of the hashset's array (giving us the index), and finally adding the `datacont` to the treeset located at that index.

Pseudocode code to illustrate:

```python
hashset[ hash(data) % hashset_length ].add(data)
```

I also added support for adding arrays of any kind of data to a `treeset`/`hashset`:
![Treeset List](/samples/treeset_list.png)

_Images generated using [Graphviz](https://www.graphviz.org/)_

## To Do:
- fix `listnode_delete()`
- make sets more easily iterable, maybe `*set_getnth(...)`
- add `listnode_add()`, `listnode_remove()`, `listnode_deleteall()`
- write toString functions for each structure
- write set operation functions (e.g. union, intersection, difference, comparison, etc.)

