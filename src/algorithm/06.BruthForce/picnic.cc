#include <iostream>
#include <vector>

using namespace std;

int n, m;
bool areFriends[10][10];

int countPairings(bool taken[10])
{
	int firstFree = -1;
	for (int i = 0; i < n; i++) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}

	if (firstFree == -1)
		return 1;

	int ret = 0;
	for (int pairWith = firstFree + 1; pairWith < n; pairWith++) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}

int main()
{
	
	int numCase;
	cin >> numCase;
	for (int i = 0; i < numCase; i++) {
		bool taken[10];
		for (int i = 0; i < 10; i++) {
			taken[i] = false;
			for (int j = 0; j < 10; j++) {
				areFriends[i][j] = false;
			}
		}

		cin >> n >> m;
		for (int j = 0; j < m; j++) {
			int front, back;
			cin >> front >> back;
			areFriends[front][back] = true;
			areFriends[back][front] = true;
		}
		int cnt = countPairings(taken);
		cout << cnt << endl;
	}
	return 0;
}
