#include <iostream>
#include <vector>
#include <string>

using namespace std;

char table[5][5];

bool hasWord(int y, int x, string word)
{
	if (table[y][x] != word[0])
		return false;

	if (word.size() == 1)
		return true;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)		// same coord
				continue;

			int nX = x + j;
			int nY = y + i;
			if (nX < 0 || nX > 4 || nY < 0 || nY > 4)
				continue;
			
			if (hasWord(nY, nX, word.substr(1, word.size())))
				return true;
		}
	}
	return false;
}

int main()
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char ch;
			cin >> ch;
			if (ch == '\n') {
				j--;
				continue;
			}
			table[i][j] = ch;
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
