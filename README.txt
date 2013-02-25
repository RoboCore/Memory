
	RoboCore Memory Library
		(v1.1 - 25/02/2013)

  Memory functions for Arduino (for Arduino 1.0 or later)

  Released under the Beerware licence


The PointerList class implements static functionality to track
	allocated memory.
	# one must first Initialize the values
	# the tracker capacity is limited and can be changed in
		'Memory.h'
	# macros 'Mmalloc()', 'Mfree()' and 'MReset()' defined
        !!! DO NOT use free() on pointers added to the list



