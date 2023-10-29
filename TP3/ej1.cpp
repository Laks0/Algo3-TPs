#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

/*
 * El grafo se representa con 4 "niveles", donde estar en el
 * nivel i significa haber usado i puentes.
 * El vértice que representa al salón v habiendo usado i puentes
 * se codifica con el número i*N + v
 * */

vector<vector<int>> tuneles;

vector<int> adj(int v, int n) {
	vector<int> res;

	if (v < 3*n) {
		int salon = v % n;
		int nivel = (int) v / n;
		for (int b : tuneles[salon]) {
			res.push_back((nivel + 1)*n + b);
		}
	}

	if ((v + 1) % n != 0) res.push_back(v+1);

	return res;
}

int costo(int a, int b) {
	if (a + 1 == b) return 1;
	return 2;
}

int dist(int n) {
	vector<int> d(4*n, 2e6);
	d[0] = 1;

	// El heap va a incluir a todos los
	// elementos de V - S con p < inf
	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> heap;
	heap.push({1, 0});

	while (heap.size() > 0) {
		auto [_, i] = heap.top();
		heap.pop();

		for (int j : adj(i, n)) {
			int nuevoCosto = d[i] + costo(i, j);
			if (d[j] < nuevoCosto) continue;
			d[j] = nuevoCosto;
			heap.push({nuevoCosto, j});
		}
	}

	vector<int> respuestas = {d[n-1],d[2*n-1],d[3*n-1],d[4*n-1]};
	int m = *min_element(respuestas.begin(), respuestas.end());
	return m;
}

int main() {
	int c;
	cin >> c;

	for (int caso = 0; caso < c; caso++) {
		int n, m;
		cin >> n >> m;
		tuneles = vector<vector<int>>(4*n, vector<int>());

		for (int t = 0; t < m; t++) {
			int a, b;
			cin >> a;
			cin >> b;
			a--; b--;
			tuneles[a].push_back(b);
		}

		cout << dist(n) << endl;
	}
}
