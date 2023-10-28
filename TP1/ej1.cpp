#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> bordes(pair<int, int> a, pair<int, int> b) {
	return {min(a.first, b.first), max(a.second, b.second)};
}

// Si no es posible ningún camino devuelve {1440, 0}
pair<int,int> caminos(const vector<vector<char>>& mapa, vector<vector<bool>>& usados, int x, int y, int ultX, int ultY, int longitud) {
	pair<int, int> total = {1440, 0};

	// Llegamos
	if (x == mapa.size()-1 && y == mapa[0].size()-1) {
		if (mapa[x][y] != '#') {
			return {longitud, longitud};
		}
		return total;
	}

	// Fuera del mapa
	if (x >= mapa.size() || x < 0 || y >= mapa[0].size() || y < 0) {
		return total;
	}

	// Repetida
	if (usados[x][y]) {
		return total;
	}

	usados[x][y] = true;
	longitud++;

	switch (mapa[x][y]) {
		case 'I':
			/* La línea recta solo sigue en la dirección por la que se vino y no se puede rotar.
			* Si se empieza en una recta sí se consideran las dos rotaciones*/
			// Vertical
			if (ultX == x) {
				total = bordes(total, caminos(mapa, usados, x, y+1, x, y, longitud));
				total = bordes(total, caminos(mapa, usados, x, y-1, x, y, longitud));
			}
			// Horizontal
			if (ultY == y) {
				total = bordes(total, caminos(mapa, usados, x+1, y, x, y, longitud));
				total = bordes(total, caminos(mapa, usados, x-1, y, x, y, longitud));
			}
			break;

		case '+':
			/* La cruz no se rota, se consideran todos los caminos */
			total = bordes(total, caminos(mapa, usados, x, y+1, x, y, longitud));
			total = bordes(total, caminos(mapa, usados, x, y-1, x, y, longitud));
			total = bordes(total, caminos(mapa, usados, x+1, y, x, y, longitud));
			total = bordes(total, caminos(mapa, usados, x-1, y, x, y, longitud));
			break;

		case 'L':
			/* La L difurca el camino en las direcciones posibles del eje opuesto del que vino */
			// Viene del vertical
			if (ultX == x) {
				total = bordes(total, caminos(mapa, usados, x-1, y, x, y, longitud));
				total = bordes(total, caminos(mapa, usados, x+1, y, x, y, longitud));
			}
			// Viene del Horizontal
			if (ultY == y) {
				total = bordes(total, caminos(mapa, usados, x, y+1, x, y, longitud));
				total = bordes(total, caminos(mapa, usados, x, y-1, x, y, longitud));
			}
			break;

		default:
			break;
	}

	usados[x][y] = false;
	return total;
}

int main() {
	int c;
	cin >> c;

	pair<int, int> resultados[c];

	for (int i = 0; i < c; i++) {
		int n, m, e;
		cin >> m >> n;

		vector<vector<char>> mapa(n, vector<char>(m, '#'));

		for (int y = 0; y < m; y++) {
			for (int x = 0; x < n; x++) {
				cin >> mapa[x][y];
			}
		}

		vector<vector<bool>> usados(n, vector<bool>(m, false));

		pair<int, int> res = caminos(mapa, usados, 0, 0, 0, 0, 0);

		resultados[i] = res;
	}

	for (pair<int, int> r : resultados) {
		if (r.second == 0) {
			cout << "IMPOSIBLE" << endl;
			continue;
		}
		cout << "POSIBLE " << r.first << " " << r.second << endl;
	}
}
