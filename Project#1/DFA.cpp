#include "DFA.h"


DFA::DFA()
{
}


DFA::~DFA()
{
}

void DFA::generate()
{
	int n, c;
	
	//This loop uses 1 to refer to a, 2 to b, and 3 to c
	//Thus, the int 132 is the string acb
	for (int i = 0; i < 333; i++)
	{
		//These are checks to skip over values that don't matter 
		//since we only care about the digits 1 2 and 3
		if (i % 10 == 4)
		{
			i += 7;
		}
		if ((i / 10) % 10 == 4)
		{
			i += 70;
		}
		if (i == 111 || i == 222)
		{
			continue;
		}

		n = true_index(i);
		
		//These lines concatinate the state we're at with either
		//an a b or c for each of the different transitions
		transitions[n][0] = true_index((i * 10) % 1000 + 1);
		transitions[n][1] = true_index((i * 10) % 1000 + 2);
		transitions[n][2] = true_index((i * 10) % 1000 + 3);

		c = check_valid(i);
		if (c == 0)
		{
			transitions[n][1] = 37;
			transitions[n][2] = 37;
		}
		if (c == 1)
		{
			transitions[n][0] = 37;
			transitions[n][2] = 37;
		}
		if (c == 2)
		{
			transitions[n][0] = 37;
			transitions[n][1] = 37;
		}
	}
	//Special case transitions to dead state
	transitions[4][0] = 37; //aa on a
	transitions[8][1] = 37; //bb on b
	transitions[12][3] = 37;//cc on c

	transitions[37][0] = 37;
	transitions[37][1] = 37;
	transitions[37][2] = 37;
}

//This function checks if we need to see a specific number/letter
//to continue. ie If we're at state 112/aab we need to see a 3/c
//so the other 2 transitions on 1/a and 2/b should go to the dead state (37)
//-1 means all transitions allowed
int DFA::check_valid(int i)
{
	int one = 0, two = 0, three = 0;
	int digit;
	if (i < 100) { return -1; }
	
	digit = i % 10;
	if (digit == 1) { one++; }
	if (digit == 2) { two++; }
	if (digit == 3) { three++; }

	digit = (i / 10) % 10;
	if (digit == 1) { one++; }
	if (digit == 2) { two++; }
	if (digit == 3) { three++; }

	digit = (i / 100) % 10;
	if (digit == 1) { one++; }
	if (digit == 2) { two++; }
	if (digit == 3) { three++; }

	if (one == 0) { return 0; }
	if (two == 0) { return 1; }
	if (three == 0) { return 2; }
	return -1;
}

//Does some calculations I spent some time theorizing that take
//us from a number like 331 to the specific number out of 37 that
//we want that state to be at
int DFA::true_index(int i)
{
	//Safety check
	if (i == 111 || i == 222 || i == 333)
	{
		return 37;
	}

	int n = i - (92 * (i / 100)) - (7 * ((i / 10) % 10));
	
	//Corrects off-by-one error caused from skipping 111 and 222 states
	if (i > 300 || (i > 200 && i < 222))
	{
		n++;
	}
	return n;
}

std::string DFA::valid_at_len(int len)
{
	int n;
	int transition_matrix[38][38];

	for (int j = 0; j < 38; j++)
	{
		for (int i = 0; i < 38; i++)
		{
			transition_matrix[j][i] = 0;
		}
	}

	for (int j = 0; j < 38; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			n = transitions[j][i];
			transition_matrix[j][n]++;
		}
	}

	//return mmult(transition_matrix, len);
	return "";
}

/* 
	Debug functions below
*/

bool DFA::test(int w)
{
	int index = 0, tran = 0;
	std::istringstream digits(std::to_string(w));

	tran = digits.get();
	while (tran >= 49 && tran <= 51)
	{
		tran -= 49;
		index = transitions[index][tran];
		tran = digits.get();
	}

	if (index != 37)
	{
		return true;
	}

	return false;
}

void DFA::increment(int &w)
{
	int digit = 0;
	int multiplier;
	int current = w % 10;

	while (current == 3)
	{
		multiplier = pow(10, digit);
		w -= 2 * multiplier;
		digit++;

		multiplier = pow(10, digit);
		current = (w / multiplier) % 10;
	}

	w += pow(10, digit);

}

void DFA::debug(int n)
{
	bool res;
	int upper_bound;
	int w = 1;
	for (int i = 0; i < n; i++)
	{
		w *= 10;
		w++;
	}
	
	upper_bound = w * 3;
	while (w <= upper_bound)
	{
		res = test(w);
		std::cout << "Testing: " << w << " returned: " << res << std::endl;
		increment(w);
	}
}