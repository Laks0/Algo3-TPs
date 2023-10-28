#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct dsu {
	vector<int> parent;
	vector<int> size;

	dsu(int n) {
		for (int i = 0; i < n; i++) {
			parent.push_back(i);
			size.push_back(1);
		}
	}

	int find(int v) {
		int w = v;
		while (parent[w] != w) w = parent[w];
		parent[v] = w;
		return w;
	}

	void unite(int v, int w) {
		v = find(v); w = find(w);
		if (size[v] < size[w]) swap(v, w);

		parent[w] = v;
		size[v] += size[w];
	}
};

float c; // El valor medio de la búsqueda binaria

struct {
	bool operator()(tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
		float wa = (float) get<2>(a) - (c * get<3>(a));
		float wb = (float) get<2>(b) - (c * get<3>(b));

		return wa > wb;
	}
} w;

// Encuentra el árbol generador máximo con una lista de aristas y pesos dados por w
pair<int, int> kruskal(vector<tuple<int, int, int, int>>& aristas, int n) {
	int dt = 0;
	int rt = 0;

	sort(aristas.begin(), aristas.end(), w);
	dsu clases(n);

	for (auto [u, v, d, r] : aristas) {
		if (clases.find(u) == clases.find(v)) continue;

		clases.unite(u, v);
		dt += d;
		rt += r;
	}

	return {dt, rt};
}

pair<int, int> mejorRelacion(vector<tuple<int, int, int, int>>& aristas, int n) {
	int rt;
	int dt;

	float a = 0;

	float b = 0;
	for (auto [u, v, d, r] : aristas) b += d;

	float aOld = -1;
	float bOld = -1;

	while (!(a == aOld && b == bOld)) {
		c = (a+b)/2;
		pair<int, int> mejor = kruskal(aristas, n);
		float costoT = (float) mejor.first - (c * mejor.second);
		aOld = a; bOld = b;
		if (costoT >= 0)
			a = c;
		if (costoT < 0)
			b = c;

		dt = mejor.first;
		rt = mejor.second;

		if (abs(a - b) < 1e-5) break;
	}

	return {dt, rt};
}

int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {
		int n, m;
		cin >> n >> m;

		vector<tuple<int, int, int, int>> e; // Lista de aristas

		for (int j = 0; j < m; j++) {
			int a, b;
			cin >> a >> b;
			a--;b--; // Lo paso de [1, n] a [0, n-1]

			int d, r;
			cin >> d >> r;

			e.push_back(make_tuple(a, b, d, r));
		}

		pair<int, int> res = mejorRelacion(e, n);
		cout << res.first << " " << res.second << endl;
	}
}
