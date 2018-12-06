#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	string s;
	cout<<"Getting a string from STDIN...\n";
	getline(cin, s);
	cout<<"...The string is: "<<s<<endl;
	return 0;
}