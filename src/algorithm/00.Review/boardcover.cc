#include <iostream>
#include <vector>

using namespace std;

// y, x
const int type[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },
	{ { 0, 0 }, { 1, 0 }, { 1, -1 } }
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta)
{
	for (int i = 0; i < 3; i++) {
		const int nY = y + type[type][i][0];
		const int nX = x + type[type][i][1];
		if (nX < 0 || nX > board.size() || nY < 0 || nY > board.size())
			return false;
		else if (board[nY][nX] += delta > 1)
			return false;
	}
	return true;
}

int cover(vector<vector<int>>& board)
{
	int x = -1, y = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {
				x = j;
				y = i;
				goto SEEK_END;
			}
		}
	}
SEEK_END:
	if (x == -1 && y == -1)
		return 1;

	int ret = 0;
	for (int i = 0; i < 4; i++) {
		if (set(board, y, x, i, 1)) {
			ret += cover(board);
		}
		set(board, y, x, i, -1);
	}
	return ret;
}
