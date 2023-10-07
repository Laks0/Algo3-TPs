#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

int SIN_VER = 0, EMP = 1, FIN = 2;

vector<vector<int>> adj;
vector<vector<int>> hijos;
vector<int> parent;
vector<int> back_inf;
vector<int> back_sup;
vector<int> estado;
vector<pair<int, int>> backedges;

void dfs(int v, int p) {
	estado[v] = EMP;
	parent[v] = p;

	for (int w : adj[v]) {
		if (estado[w] == SIN_VER) {
			hijos[v].push_back(w);
			dfs(w, v);
		}
		else if (w != p) {
			if (estado[w] == EMP) {
				back_inf[v]++;
			} else {
				back_sup[v]++;
				// Guardo el parent primero
				backedges.push_back({v,w});
			}
		}
	}

	estado[v] = FIN;
}

vector<int> mem;

int cubren(int v) {
	if (mem[v] != -1) return mem[v];

	int res = 0;
	for (int w : hijos[v]) {
		res += cubren(w);
	}
	res -= back_sup[v];
	res += back_inf[v];

	return mem[v] = res;
}

vector<pair<int, int>> importantes() {
	vector<pair<int, int>> res;

	dfs(0, -1);

	for (int v = 0; v < adj.size(); v++) {
		if (cubren(v) != 1) continue;

		// Si llegó acá encontramos una importante
		res.push_back({min(parent[v], v), max(parent[v], v)});
	}

	for (pair<int,int> b : backedges) {
		int v = b.second;
		while (v != b.first) {
			if (cubren(v) == 1){
				res.push_back({min( b.first, b.second ), max( b.first, b.second )});
				break;
			}
			v = parent[v];
		}
	}

	sort(res.begin(), res.end());

	return res;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n, m;
		cin >> n >> m;

		adj = vector<vector<int>>(n, vector<int>());
		hijos = vector<vector<int>>(n, vector<int>());
		back_inf = vector<int>(n, 0);
		back_sup = vector<int>(n, 0);
		backedges = vector<pair<int, int>>();
		parent = vector<int>(n);
		estado = vector<int>(n, SIN_VER);
		mem = vector<int>(n, -1);

		for (int j = 0; j < m; j++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		vector<pair<int, int>> res = importantes();

		cout << res.size() << endl;
		for (pair<int, int> r : res) {
			cout << r.first << " " << r.second << endl;
		}
	}
}
