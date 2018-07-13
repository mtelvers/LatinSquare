
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

string IntToString(int num) {
	ostringstream temp;
	temp << setfill('0') << setw(6) << num;
	return temp.str();
}

bool CheckDuplicates(vector<unsigned int>* v) {
	vector<unsigned int> c (v->begin(), v->end());
//	for (vector<unsigned int>::iterator it = v->begin(); it != v->end(); ++it)
//		cout << *it;
//	cout << "\n";
	sort(c.begin(), c.end());
	vector<unsigned int>::iterator it = adjacent_find(c.begin(), c.end());
	if (it == c.end())
		return false;
	else
		return true;
}

int main () {

	for (unsigned int t = 0; t < 1000000; t++) {
		vector< vector<unsigned int>* > square;

		{
			vector<unsigned int>* row = new vector<unsigned int>;
			unsigned int n = t;
			for (int i = 0; i < 6; i++) {
				row->insert(row->begin(), n % 10);
				n /= 10;
			}
			if (CheckDuplicates(row)) {
				//cout << t << " contains duplicates\n";
				delete row;
			} else {
				square.push_back(row);
			}
		}

		if (square.size() == 1) {
			for (unsigned int j = 2; j <= 6; j++) {
				unsigned int carry = 0;
				vector<unsigned int>* row = new vector<unsigned int>;
				for (int i = 5; i >= 0; i--) {
					unsigned int n = square.at(0)->at(i) * j + carry;
					if (n > 9) {
						carry = n / 10;
						n %= 10;
					} else {
						carry = 0;
					}
					row->insert(row->begin(), n);
				}
				if (carry) {
					//cout << "x" << j << " overflow\n";
					delete row;
					break;
				} else {
					if (CheckDuplicates(row)) {
						//cout << "x" << j << " contains duplicates\n";
						delete row;
					} else {
						square.push_back(row);
					}
				}
			}
		}

		if (square.size() == 6) {
			bool duplicates = false;
			for (int i = 5; i >= 0; i--) {
				vector<unsigned int> column;
				for (vector<unsigned int>* row : square)
					column.push_back(row->at(i));
				if (CheckDuplicates(&column)) {
					//cout << "column " << i << " contains duplicates\n";
					duplicates = true;
				}
			}
			if (!duplicates) {
				cout << "\nsolution\n";
				for (vector<unsigned int>* row : square) {
					for (unsigned int c : *row) {
						cout << c << ' ';
					}
					cout << '\n';
				}
			}
		}

		for (vector<unsigned int>* row : square)
			delete row;
		square.erase(square.begin(), square.end());
	}

	return 0;
}

