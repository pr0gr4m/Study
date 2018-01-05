#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<char>> v;
bool flag = false;

/*
void hasWord(vector<char>& comb, int y, int x, string& word)
{
	if (flag)
		return;

	if (comb.size() == word.size()) {
		stringstream tmp;
		for (char ch : comb)
			tmp << ch;
		if (tmp.str() == word) {
			flag = true;
			return;
		} else {
			return;
		}
	}

	comb.push_back(v[y][x]);
	for (int i = y - 1; i <= y + 1; i++) {
		if (i < 0 || i > 4)
			continue;
		for (int j = x - 1; j <= x + 1; j++) {
			if (j < 0 || j > 4)
				continue;
			if (i == y && j == x)
				continue;
			hasWord(comb, i, j, word);
		}
	}
	comb.pop_back();
}*/

const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };

bool inRange(int y, int x) {
	if (y < 0 || x < 0 || y > 4 || x > 4)
		return false;
	return true;
}

bool hasWord(int y, int x, const string& word)
{
	if (!inRange(y, x)) return false;
	if (v[y][x] != word[0]) return false;
	if (word.size() == 1)
		return true;
	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if (hasWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}

int main()
{
	v.resize(5);
	for (int i = 0; i < 5; i++) {
		v[i].resize(5);
		for (int j = 0; j < 5; j++) {
			char ch;
			cin >> ch;
			if (ch == '\n') {
				j--;
				continue;
			}
			v[i][j] = ch;
		}
	}
	
	int num;
	cin >> num;
	vector<string> words;
	words.resize(num);
	for (int i = 0; i < num; i++) {
		cin >> words[i];
	}

	bool flag = false;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (hasWord(j, k, words[i])) {
					cout << words[i] << " YES" << endl;
					flag = true;
					goto NEXT;
				}
			}
		}
NEXT:
		if (!flag)
			cout << words[i] << " NO" << endl;
		flag = false;
	}
	
	return 0;
}
