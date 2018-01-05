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
	bool flag = true;
	for (int i = 0; i < clocks.size(); i++) {
		if (clocks[i] != 12) {
			flag = false;
			break;
		}
	}
	return flag;
}

void push(vector<int>& clocks, int type)
{
	for (int clock = 0; clock < CLOCKS; ++clock) {
		clocks[clock] += clockSwitch[type][clock];
		if (clocks[clock] > 12)
			clocks[clock] = 3;
	}
}

int solve(vector<int>& clocks, int type)
{
	if (areAligned(clocks))
		return 0;

	if (type == SWITCHES) {
		return INF;
	}

	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, solve(clocks, type + 1));
		push(clocks, type);
	}
	return ret;
}
