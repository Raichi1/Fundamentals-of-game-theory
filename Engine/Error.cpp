#include <iostream>
using namespace std;

void faltaError(string errorString) {
	cout << errorString << endl;
	cout << "Enter any key to quit" << endl;
	int tmp;
	cin >> tmp;
	exit(-1);
}