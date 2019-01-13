#ifndef _DFA2
#define _DFA2
#include <iostream>
#include <istream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <algorithm> //used to alphabetically sort digits string

class DFA2 {

public:
	DFA2();
	~DFA2();
	int** get_delta(); //Returns a pointer to the transition table. Maybe make const?
	bool* get_allowed(); //Returns allowed
	int get_k(); //Returns the value the user input/number of states/number of rows in get_delta
	int get_numcols(); //Returns number of unique digits from the (possibly garbled) input of allowed digits
	std::string get_digits(); //Returns the sorted list of allowed digits as a string for mapping the indexs of delta onto the actual values each column represents
	void print_table(); //Prints the transition table

private:
	bool create_table(); //Loads the transition table
	void get_input(); //Prompts the user for input for k and the allowed digits and sets k and allowed accordingly
	int k; //The number the user gives us. Also equal to the number of states
	int **delta; //The transition table
	bool allowed[10]; //Array representing the allowed digits
	int numcols; // |L|, or number of allowed digits
	std::string digits; //A string holding the actual allowed digits. I use it for maping the column in delta to the actual number it represents. Probably a better way to do it, but this works for now
};

#endif
