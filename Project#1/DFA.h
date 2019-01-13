#pragma once
#include <string>

//These only used for debugging
#include <iostream>
#include <math.h>
#include <sstream>

class DFA
{
public:
	DFA();
	~DFA();

	void generate();
	std::string valid_at_len(int len);
	void debug(int n);

private:
	int transitions[38][3];

	bool test(int w);
	void increment(int &w);
	int true_index(int i);
	int check_valid(int i);
};

