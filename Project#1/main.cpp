#include <iostream>
#include "DFA.h"
#include "DFA2.h"
#include "BFS.h"

int main()
{
	int i;

	std::cout << "Problem 1 or problem 2?\n";
	std::cin >> i;

	if (i == 1)
	{
		DFA m;
		int n;

		std::cout << "Enter n: ";
		std::cin >> n;

		m.generate();
		std::cout << m.valid_at_len(n) << std::endl;
	}
	else if (i == 2)
	{
		DFA2 m2;
		BFS b;
		std::string s;

		s = b.min_string(m2);

		std::cout << s << std::endl;
	}
	else
	{
		std::cout << "I said problem 1 or 2; it's not that hard" << std::endl;
	}

	return 0;
}