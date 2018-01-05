#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bruteForce(const vector<int>& h)
{
	int ret = 0;
	for (int i = 0; i < h.size(); i++) {
		int m = 0;
		for (int j = i; j < h.size(); j++) {
			m = min(m, h[j]);
			ret = max(ret, (j - i + 1) * m);
		}
	}
	return ret;
}

vector<int> h;

int solve(int left, int right)
{
	if (left == right)
		return h[left];

	int half = (left + right) / 2;
	int ret = max(solve(left, half), solve(half + 1, right));

	int low = half, high = half + 1;
	int height = min(h[low], h[high]);
	ret = max(ret, height * 2);

	while (left < low || high < right) {
		if (high < right && (low == left || h[low - 1] < h[high + 1])) {
			high++;
			height = min(height, h[high]);
		} else {
			low--;
			height = min(height, h[low]);
		}
		ret = max(ret, height * (high - low + 1));
	}
	return ret;
}

int main()
{
	int cas;
	cin >> cas;

	for (int i = 0; i < cas; i++) {
		int hNum;
		cin >> hNum;
		h.resize(hNum);
		for (int j = 0; j < hNum; j++) {
			cin >> h[j];
		}
		cout << solve(0, hNum - 1) << endl;
	}
	return 0;
}
