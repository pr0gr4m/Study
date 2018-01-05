#include <iostream>
#include <vector>

using namespace std;

int count(const vector<int>& group, const vector<int>& fan)
{
	int cnt = 0;
	for (int i = 0; i <= fan.size() - group.size(); i++) {
		bool flag = true;
		for (int j = 0; j < group.size(); j++) {
			if (!(group[j] | fan[i + j])) {
				flag = false;
				break;
			}
		}
		if (flag)
			cnt++;
	}
	return cnt;
}

int main()
{
	int cn;
	cin >> cn;
	cin.get();
	for (int i = 0; i < cn; i++) {
		vector<int> group, fan;
		char ch;
		while (1) {
			ch = cin.get();
			if (ch == 'F')
				group.push_back(1);
			else if (ch == 'M')
				group.push_back(0);
			else 
				break;
		}
		
		while (1) {
			ch = cin.get();
			if (ch == 'F')
				fan.push_back(1);
			else if (ch == 'M')
				fan.push_back(0);
			else
				break;
		}

		cout << count(group, fan) << endl;
	}

	return 0;
}
