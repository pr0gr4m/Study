#include <iostream>
#include <vector>

using namespace std;

ostream& operator <<(ostream& os, const vector<int>& v)
{
	os << "[ ";
	for (int i : v)
		os << i << ' ';
	os << "]" << endl;
	return os;
}

void pick(int n, vector<int>& v, int toPick)
{
	if (toPick == 0) {
		cout << v;
		return;
	}

	int smallest = v.empty() ? 0 : v.back() + 1;
	for (int i = smallest; i < n; i++) {
		v.push_back(i);
		pick(n, v, toPick - 1);
		v.pop_back();
	}
}

int main()
{
	vector<int> v;
	pick(5, v, 3);
	return 0;
}
