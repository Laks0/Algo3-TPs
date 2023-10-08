#include <iomanip>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> adj(pair<int, int> v, int n, int m) {
	vector<pair<int, int>> res;

	if (v.first < m-1)
		res.push_back({v.first + 1, v.second});
	if (v.first > 0)
		res.push_back({v.first - 1, v.second});
	if (v.second < n-1)
		res.push_back({v.first, v.second + 1});
	if (v.second > 0)
		res.push_back({v.first, v.second - 1});

	return res;
}

int tiempoMinimo(pair<int, int> a, pair<int, int> b, int t, const vector<vector<int>>& map) {
	int depth = 0;

	int m = map.size();
	int n = map[0].size();

	vector<vector<bool>> visitado(m, vector<bool>(n, false));
	visitado[a.first][a.second] = true;

	list<pair<int, int>> front;
	list<pair<int, int>> next;

	front.push_back(a);

	while (front.size() > 0) {
		for (pair<int, int> v : front) {
			if (v == b) return depth;

			for (pair<int, int> w : adj(v, n, m)) {
				int wx = w.first;
				int wy = w.second;

				if (visitado[wx][wy]) continue;

				int tij = map[wx][wy];
				if (tij <= t + depth && tij != 0) continue;

				next.push_back(w);
				visitado[wx][wy] = true;
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
		// n es la cantidad de filas y m de columnas

		vector<vector<int>> map(m, vector<int>(n));

		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				cin >> map[x][y];
			}
		}

		pair<int, int> a;
		pair<int, int> b;

		cin >> a.second >> a.first >> b.second >> b.first;

		int ida = tiempoMinimo(a, b, 1, map);

		if (ida == -1) {
			cout << "IMPOSIBLE" << endl;
			continue;
		}

		int vuelta = tiempoMinimo(b, a, 1+ida, map);

		if (vuelta == -1) {
			cout << "IMPOSIBLE" << endl;
			continue;
		}

		cout << ida  << " " << ida + vuelta << endl;
	}
}
