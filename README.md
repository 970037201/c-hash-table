# C++ Semi static hash table
Semi static hash table implementation, where a fixed number of buckets are implemented, and adding elements by key type are dynamically added.

This implementation is the third in a series of basic data storage types that I am making, to help me and others understand their inner workings.
The hash table is:
	-Collision proof (as it compares keys, and not hashes of keys... etc)
	-Dynamically growing (not the buckets, but the number of elements)
	-Not well tested (Intended for educational purposes only, for now, you are most likely better off with standard library)
	-Able to add elements, remove elements, access elements by reference, and find if the table contains an element.

