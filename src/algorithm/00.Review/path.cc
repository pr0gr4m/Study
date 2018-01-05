
const int MAX = 10;
const double INF = 987654321;

int n;
double dist[MAX][MAX];

double shortestPath(vector<int>& path, vector<bool>& visited, double curLen)
{
	if (path.size() == n)
		return curLen + dist[path[0]][path.back()];
	double ret = INF;

	for (int next = 0; next < n; next++) {
		if (visited[next])
			continue;

		int now = path.back();
		path.push_back(next);
		visited(next) = true;
		ret = min(ret, shortestPath(path, visited, curLen + dist[now][next]));
		visited(next) = false;
		path.pop_back();
	}
	return ret;
}
