#include <iostream>
#include <vector>

using namespace std;

int n;
bool arePair[10][10];

int countPair(bool taken[10])
{
	int first = -1;
	for (int i = 0; i < n; i++) {
		if (!taken[i]) {
			first = i;
			break;
		}
	}
	if (first == -1)
		return -1;
	
	int ret = 0;
	for (int with = first + 1; with < n; with++) {
		if (!taken[with] && arePair[first][with]) {
			taken[first] = taken[with] = true;
			ret += countPair(taken);
			taken[first] = taken[with] = false;
		}
	}
	return ret;
}
