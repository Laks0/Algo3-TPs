#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// Placeholder ineficiente
int costo(const vector<int>& puestos, const vector<int>& postas) {
	int c = 0;
	for (int i = 0; i < puestos.size(); i++) {
		int minimo = 1e6;

		for (int p : postas) {
			int d = abs(puestos[p] - puestos[i]);
			minimo = min(d, minimo);
		}

		c += minimo;
	}
	return c;
}

bool esMejorSolucion(vector<int> a, vector<int> b) {
	for (int i = 0; i < min(a.size(), b.size()); i++) {
		if (a[i] == b[i]) {
			continue;
		}
		if (a[i] > b[i]) {
			return false;
		}
		if (a[i] < b[i]) {
			return true;
		}
	}
	return true;
}

void reducirSolucion(const vector<int>& puestos, vector<int>& postas, vector<int>& mejor, int i, int minimoCosto) {
	if (i >= postas.size()) {
		return;
	}

	int posInicial = postas[i];

	for (int x = posInicial; x >= 0; x--) {
		if (i > 0 && postas[i] <= postas[i-1]) {
			postas[i] = posInicial;
			break;
		}

		postas[i]--;
		if (costo(puestos,postas) == minimoCosto && esMejorSolucion(postas, mejor)) {
			mejor = postas;
		}

		reducirSolucion(puestos, postas, mejor, i+1, minimoCosto);
	}

	postas[i] = posInicial;
}

int mejorDist(const vector<int>& puestos, int n, vector<int>& postas) {
	/* Las postas solo pueden ir enfrente de puestos, las codificamos
	** con el número de puesto en el que están */

	int mejorCosto;

	for (int i = 0; i < n; i++) {
		postas.push_back(0);

		int costoMinimo = costo(puestos, postas);
		int mejorPos = postas[i];

		for (int x = 0; x < puestos.size(); x++) {
			postas[i] = x;
			int nuevoCosto = costo(puestos, postas);

			if (nuevoCosto < costoMinimo || ( nuevoCosto == costoMinimo && postas[i] < mejorPos )) {
				costoMinimo = nuevoCosto;
				mejorPos = postas[i];
			}
		}

		postas[i] = mejorPos;
		mejorCosto = costoMinimo;
	}

	sort(postas.begin(), postas.end());

	// Encontrada una solución optima, se busca la menor lexicográficamente
	vector<int> mejorSolucion = postas;
	reducirSolucion(puestos, postas, mejorSolucion, 0, mejorCosto);

	postas = mejorSolucion;

	// Transformar a posiciones
	for (int i = 0; i < n; i++) {
		postas[i] = puestos[postas[i]];
	}

	return mejorCosto;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n, cantPuestos;
		cin >> cantPuestos >> n;

		vector<int> puestos(cantPuestos);
		for (int p = 0; p < cantPuestos; p++) {
			cin >> puestos[p];
		}

		vector<int> postas;
		int res = mejorDist(puestos, n, postas);

		cout << res << endl;
		cout << puestos[0];
		for (int j = 1; j < postas.size(); j++) {
			cout << " " << postas[j];
		}
		cout << endl;
	}
}
