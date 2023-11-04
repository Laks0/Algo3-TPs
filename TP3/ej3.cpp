#include <iostream>
#include <list>
#include <vector>
#include <set>

using namespace std;

// Devuelve la lista de adyacencia de la red de flujo, la capacidad de todas
// las aristas es 1
vector<set<int>> red_de_flujo(const vector<vector<int>>& mapa) {
	int n = mapa.size();

	vector<set<int>> adj(n*n); // Los primeros n*n representan los casilleros

	// FILAS
	// cada fila conecta a los casilleros que la componen
	int ultimaFila;
	bool nuevaFila = false;
	for (int i = 0; i < n; i++) {
		nuevaFila = false;
		ultimaFila = adj.size();
		adj.push_back(set<int>());

		for (int j = 0; j < n; j++) {
			if (mapa[i][j] == 0) {
				if (nuevaFila) {
					ultimaFila = adj.size();
					adj.push_back(set<int>());
					nuevaFila = false;
				}
				adj[ultimaFila].insert(i+j*n);
				continue;
			}
			// Hay un roto, se crea una nueva fila
			nuevaFila = true;
		}
	}

	// COLUMNAS
	// cada casillero conecta a su fila correspondiente
	int ultimaColumna;
	bool nuevaColumna = false;
	for (int j = 0; j < n; j++) {
		nuevaColumna = false;
		ultimaColumna = adj.size();
		adj.push_back(set<int>());

		for (int i = 0; i < n; i++) {
			if (mapa[i][j] == 0) {
				if (nuevaColumna) {
					ultimaColumna = adj.size();
					adj.push_back(set<int>());
					nuevaColumna = false;
				}

				adj[i+j*n].insert(ultimaColumna);
				continue;
			}
			// Hay un roto, se crea una nueva columna
			nuevaColumna = true;
		}
	}

	// t es el aneúltimo
	int t = adj.size();
	adj.push_back(set<int>());

	// s es el último
	int s = adj.size();
	adj.push_back(set<int>());

	// s conecta a todas las filas
	for (int i = n*n; i <= ultimaFila; i++) {
		adj[s].insert(i);
	}

	// todas las columnas conectan a t
	for (int i = ultimaFila+1; i <= ultimaColumna; i++) {
		adj[i].insert(t);
	}

	// No hace falta una matriz de capacidades porque son siempre 1
	return adj;
}

bool bfs(int s, int t, const vector<set<int>>& adj, vector<int>& parent) {
	fill(parent.begin(), parent.end(), -1);
	list<int> frontera = {s};

	while (frontera.size() > 0) {
		int v = frontera.front();
		frontera.pop_front();

		for (int h : adj[v]) {
			if (parent[h] != -1) continue;

			parent[h] = v;
			if (h == t) return true;
			frontera.push_back(h);
		}
	}

	return false;
}

int maxTorres(const vector<vector<int>>& mapa) {
	vector<set<int>> adj = red_de_flujo(mapa);

	int flujo = 0;
	vector<int> parent(adj.size());

	int s = adj.size()-1;
	int t = adj.size()-2;

	bool hayAumento = bfs(s, t, adj, parent);
	while (hayAumento) {
		int v = t;
		while (v!=s) {
			int padre = parent[v];
			adj[v].insert(padre);
			adj[padre].erase(v);
			v = padre;
		}
		flujo++;
		hayAumento = bfs(s, t, adj, parent);
	}

	return flujo;
}

int main() {
	int c;
	cin >> c;
	for (int caso = 0; caso < c; caso++) {
		int n;
		cin >> n;

		vector<vector<int>> mapa(n, vector<int>(n));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> mapa[i][j];
			}
		}

		cout << maxTorres(mapa) << endl;
	}
}
