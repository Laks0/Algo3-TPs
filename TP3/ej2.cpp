#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define INF 2e6

bool imposible = false;

bool es_eficiente(int a, int b, const vector<vector<int>>& latencia) {
	int n = latencia.size();

	// Quiero ver que no haya ningún k tq l(a,k) + l(k,b) = l(a,b)
	for (int k = 0; k < n; k++) {
		if (k==b || k==a) continue;
		if (latencia[a][k] + latencia[k][b] == latencia[a][b]) return false;

		// IMPOSIBLE
		if (latencia[a][k] + latencia[k][b] < latencia[a][b]) {
			imposible = true;
			return false;
		}
	}

	return true;
}

// Devuelve la matriz de adyacencias del grafo eficiente
vector<vector<int>> adyacencias(const vector<vector<int>>& latencia) {
	int n = latencia.size();
	vector<vector<int>> adj(n, vector<int>(n, INF));

	for (int a = 0; a < n; a++) {
		for (int b = 0; b < a; b++) {
			if (es_eficiente(a, b, latencia)) {
				adj[a][b] = 1;
				adj[b][a] = 1;
			}
		}
	}

	return adj;
}

// FW
vector<vector<int>> distancias(const vector<vector<int>>& latencia) {
	int n = latencia.size();

	vector<vector<int>> d0 = adyacencias(latencia); // La del paso "anterior"
	for (int i = 0; i < n; i++) d0[i][i] = 0;

	vector<vector<int>> d1(n, vector<int>(n));      // La del paso actual

	if (imposible) return d0;

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d1[i][j] = min(d0[i][j], d0[i][k] + d0[k][j]);
				d1[j][i] = d1[i][j];
			}
		}
		d0 = d1;
	}

	return d1;
}

int main() {
	int c;
	cin >> c;
	for (int caso = 0; caso < c; caso++) {
		int n;
		cin >> n;

		imposible = false;

		vector<vector<int>> latencia(n, vector<int>(n, 0));

		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				cin >> latencia[i][j];
				latencia[j][i] = latencia[i][j];
			}
		}

		vector<vector<int>> res = distancias(latencia);

		if (imposible) {
			cout << "IMPOSIBLE" << endl;
			continue;
		}

		cout << "POSIBLE" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
	}
}
