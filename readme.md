Understanding Hamming Code
==========================

Description
-----------
Command line utility with no parameters. Will ask user for a character and
which parity (even or odd) they'd like to use, then displays that character's
ascii values and [Hamming code][1] (8, 4). Finally it will flip a bit at 
random, and correct itself all with some pretty output.

Code is kind of hard to follow, needs some serious refactoring (Cyclomatic 
complexity bandit's strike again!). Seems to work though.


Compiling
---------
Do it in Linux (run the make file), not tested in Windows because I didn't feel
like it.


Expected Output
---------------

	Displays ascii values and calculates the 8,4 Hamming code for an inputted 
	character. Then randomly flips a bit, displays the error and correction.

	  Enter a character: A
	  Choose parity (e for even, o for odd): e

	  ASCII Values for Input:
	    char    binary    hex    decimal
	       A  01000001     41         65

	  Calculated Hamming Code: 
	     +--+-----+-----------+----------------parity bits (even)
	     |  |     |           |
	     1  0  0  0  1  0  0  1  0  0  0  1 
	           |     |  |  |     |  |  |  |
	           +-----+--+--+-----+--+--+--+----data bits

	  Force random single-bit error:
	    Location DB bit flipped.
	     1  0  0  0  1  0  0  1  0  0  1  1 
	    P1 P2 D3 P4 D5 D6 D7 P8 D9 DA DB DC <---- bit lcoations

	  ASCII Values with Error:
	    char    binary    hex    decimal
	       C  01000011     43         67

	  Parity Checking:
	    first parity set  101001 <--error
	    second parity set 000001 <--error
	    third parity set  001001 <--good
	    fourth parity set 010011 <--error

	    Error found at location DB.

	Run again (y/n)? 

[1]: http://en.wikipedia.org/wiki/Hamming_code