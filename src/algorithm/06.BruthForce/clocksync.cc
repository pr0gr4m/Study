#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 987654321, SWITCHES = 10, CLOCKS = 16;

const int clockSwitch[SWITCHES][CLOCKS] = {
	{ 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 3, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3 },
	{ 3, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 0, 3, 0, 0, 0 },
	{ 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3 },
	{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3 },
	{ 0, 0, 0, 0, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 3 },
	{ 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 3, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0 }
};

bool areAligned(const vector<int>& clocks)
{
	for (int clock : clocks)
		if (clock != 12)
			return false;
	return true;
}

void push(vector<int>& clocks, int type) {
	for (int clock = 0; clock < CLOCKS; ++clock) {
		clocks[clock] += clockSwitch[type][clock];
		if (clocks[clock] == 15)
			clocks[clock] = 3;
	}
}

int solve(vector<int>& clocks, int type)
{
	if (areAligned(clocks))
		return 0;

	if (type == SWITCHES)
		return INF;

	int ret = INF;
	for (int cnt = 0; cnt < 4; ++cnt) {
		ret = min(ret, cnt + solve(clocks, type + 1));
		push(clocks, type);
	}
	return ret;
}


int main()
{
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++) {
		vector<int> clocks;
		clocks.resize(CLOCKS);
		for (int j = 0; j < CLOCKS; j++) {
			cin >> clocks[j];
		}
		cout << solve(clocks, 0) << endl;
	}
	return 0;
}
