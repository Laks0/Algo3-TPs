#include <iomanip>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> adj(pair<int, int> v, int n, int m) {
	vector<pair<int, int>> res;

	if (v.first > 0)
		res.push_back({v.first - 1, v.second});
	if (v.first < n-1)
		res.push_back({v.first + 1, v.second});
	if (v.second > 0)
		res.push_back({v.first, v.second - 1});
	if (v.second < m-1)
		res.push_back({v.first, v.second + 1});

	return res;
}

int caminoMasCorto(pair<int, int> a, pair<int, int> b, int t, const vector<vector<int>>& map) {
	int n = map.size();
	int m = map[0].size();

	int depth = 0;
	list<pair<int, int>> front;
	list<pair<int, int>> next;
	vector<vector<bool>> visitado(n, vector<bool>(m, false));
	front.push_back(a);
	visitado[a.first][a.second] = true;

	while (front.size() > 0) {
		for (pair<int, int> v : front) {
			if (v == b) return depth;

			for (pair<int, int> w : adj(v, n, m)) {
				if (visitado[w.first][w.second]) continue;

				int tij = map[w.first][w.second];
				if (t + depth >= tij && tij != 0) continue;

				next.push_back(w);
				visitado[w.first][w.second] = true;
			}
		}

		front = next;
		next.erase(next.begin(), next.end());
		depth++;
	}

	return -1;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> map(m, vector<int>(n));

		for (int y = 0; y < n; y ++) {
			for (int x = 0; x < m; x++) {
				cin >> map[x][y];
			}
		}

		pair<int, int> a, b;
		cin >> a.first >> a.second >> b.first >> b.second;

		int ida = caminoMasCorto(a, b, 1, map);

		if (ida == -1) {
			cout << "IMPOSIBLE" << endl;
			continue;
		}

		int vuelta = caminoMasCorto(b, a, 1+ida, map);
		cout << ida << " " << vuelta + ida << endl;
	}
}
