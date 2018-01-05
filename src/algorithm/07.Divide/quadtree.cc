#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator& it)
{
	char head = *it;
	it++;
	if (head == 'b' || head == 'w')
		return string(1, head);
	else {
		string s1 = reverse(it);
		string s2 = reverse(it);
		string s3 = reverse(it);
		string s4 = reverse(it);
		return string("x") + s3 + s4 + s1 + s2;
	}
}

int main()
{
	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		string str;
		cin >> str;
		string::iterator it = str.begin();
		cout << reverse(it) << endl;
	}

	return 0;
}
