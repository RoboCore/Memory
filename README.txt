
	RoboCore Memory Library
		(v1.2 - 26/02/2013)

  Memory functions for Arduino
    (tested only in Arduino 1.0.1)

  Released under the Beerware licence


The PointerList class implements static functionality to track
	allocated memory.
	# one must first Initialize the values
	# the tracker capacity is limited and can be changed in
		'Memory.h'
	# macros 'Mmalloc()', 'Mfree()' and 'MReset()' defined
        # leave USE_POINTER_LIST defined to use this class
                (other libraries use this functionality if defined,
                otherwise use 'standard' malloc())
        !!! DO NOT use free() on pointers added to the list



