#include "BFS.h"

BFS::BFS()
{
}


BFS::~BFS()
{
}

//Struct so the queue can hold more than 1 piece of data per entry
//
//value is the full path we've taken to get to this point
//last_state is the last state (column) of the transition table
//(used to avoid re-checking every number from scratch)
//next_transition is the transition (row) we will take at the table
struct BFS::Data
{
	std::string value;
	int last_state;
	int next_transition;
};

struct BFS::Queue
{
private:
	//Struct for my linked list
	struct Node
	{
		Node* next = nullptr;
		Data* value = nullptr;
	};

	Node *first = nullptr, *last = nullptr;

public:
	//Really basic queue insert and delete (pop)
	//commands along with an empty check

	void insert(Data* d)
	{
		Node* n = new Node;
		
		n->value = d;
		
		if (!first)
		{
			first = n;
			last = n;
		}
		else
		{
			last->next = n;
			last = n;
	}
	}

	Data* pop()
	{
		if (is_empty())
		{
			return nullptr;
		}

		Node *n = first;
		Data *d = n->value;
		first = first->next;

		delete n;
		return d;
	}

	bool is_empty()
	{
		if (!first)
		{
			return true;
		}
		return false;
	}
};

std::string BFS::min_string(DFA2 m)
{
	int** delta = m.get_delta();
	bool* allowed = m.get_allowed();
	int legal_moves[10];
	int count = 0, n = 0;

	//legal_moves is used to see what the actual number is for each transition
	//ie if delta[0] is actually transitions on 7 i can use legal_moves[0] to get 7
	for (int i = 0; i < 10; i++)
	{
		if (allowed[i])
		{
			count++;
			legal_moves[n] = i;
			n++;
		}
	}

	Queue *q = new Queue;

	//I do the first set of inputs to the queue manually
	//to avoid things like nullptr exceptions and bothering 
	//to check if 0 is a multiple of k (technically true, but i
	//assume we wish to avoid this)
	for (int i = 0; i < count; i++)
	{
		Data *d = new Data;

		d->value = std::to_string(legal_moves[i]);
		d->last_state = 0;
		d->next_transition = i;

		q->insert(d);
	}

	int transition = 0, state = 0;
	std::string val;

	while (!q->is_empty())
	{
		Data *d = q->pop();

		//Grabs the data from the queue entry and does the transition 
		//from the delta table
		state = d->last_state;
		transition = d->next_transition;
		val = d->value;

		state = delta[state][transition];

		//Checks for goal state
		if (state == 0 && d->last_state != 0)
		{
			delete q;
			return val;
		}

		delete d;

		for (int i = 0; i < count; i++)
		{
			Data *d = new Data;

			d->value = val + std::to_string(legal_moves[i]);
			d->last_state = state;
			d->next_transition = i;

			q->insert(d);
		}
	}

	//Just in case
	delete q;
	return "No string found";

}