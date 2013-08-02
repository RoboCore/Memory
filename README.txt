
	RoboCore Memory Library
		(v1.3 - 01/03/2013)

  Memory functions for Arduino
    (tested with Arduino 0022 and 1.0.1)

  Copyright 2013 RoboCore (François) ( http://www.RoboCore.net )
  
  ------------------------------------------------------------------------------
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ------------------------------------------------------------------------------


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



