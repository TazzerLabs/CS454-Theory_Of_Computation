#pragma once

#include <string>
#include "DFA2.h"

class BFS
{
public:
	BFS();
	~BFS();

	std::string min_string(DFA2 m);

private:
	struct Data;
	struct Queue;
};

