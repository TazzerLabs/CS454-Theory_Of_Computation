#include "DFA2.h"
using namespace std;

DFA2::DFA2() {
	for (int i = 0; i < 10; i++)
		allowed[i] = 0;
	numcols = 0;
	digits = "";
	delta = nullptr;

	get_input();
	bool b = create_table();
	while (!b) {
		cout << "Impossible to find a multiple of " << k << " over alphabet ";
		for (int i = 0; i < numcols; i++)
		{
			cout << digits[i];
		}
		cout << "\nPlease try a different combination\n";
		delete delta;
		for (int i = 0; i < 10; i++)
			allowed[i] = 0;
		digits = "";
		get_input();
		b = create_table();
	}

}

DFA2::~DFA2() {

}

int** DFA2::get_delta() {
	return delta;
}

bool* DFA2::get_allowed() {
	return allowed;
}

int DFA2::get_k() {
	return k;
}

int DFA2::get_numcols() {
	return numcols;
}

string DFA2::get_digits() {
	return digits;
}

void DFA2::print_table() {
	cout << endl << setw(10) << '\t';
	for (int i = 0; i < digits.length(); i++) {
		cout << setw(10) << digits[i];
	}
	cout << endl << setw(10) << '\t';
	for (int i = 0; i < digits.length(); i++) {
		cout << "----------";
	}
	cout << endl;
	for (int i = 0; i < k; i++) {
		cout << setw(10) << i << '|' << "\t";
		for (int j = 0; j < numcols; j++)
			cout << setw(10) << delta[i][j];
		cout << endl;
	}

}

void DFA2::get_input() {
	k = 0; numcols = 0;
	string temp = "";
	cout << "Enter K: ";
	cin >> k;
	cout << "Enter Allowed Digits [ 0 - 9 ]: ";
	if (cin.peek() == '\n')
		cin.ignore();
	getline(cin, temp);
	for (int i = 0; i < temp.length(); i++) {
		//If the current char in the input string is a number
		//and we haven't marked that digit as being allowed yet,
		//mark it as allowed and increment the number of columns
		if (isdigit(temp[i]) && allowed[temp[i] - '0'] == 0) {
			allowed[(temp[i]) - '0'] = 1;
			digits += (temp[i]);
			numcols++;
		}
	}
	//Some print outs used in ensuring value accuracy
	/*
	cout << "\n{ ";
	for(int j = 0; j < 10; j++){
		cout << allowed[j] << ' ';
	}
	cout << "}\n";
	cout << numcols << " allowed digits total\n";
	*/
	sort(digits.begin(), digits.end());
}

bool DFA2::create_table() {
	delta = new int*[k];
	for (int i = 0; i < k; i++) {
		delta[i] = new int[numcols];
		for (int j = 0; j < numcols; j++)
			delta[i][j] = ((10 * i) + (digits[j]) - '0') % k;
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < numcols; j++) {
			if (delta[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}
