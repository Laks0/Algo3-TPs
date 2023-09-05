#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int costo(const vector<int>& puestos, const vector<int>& postas, vector<int>& contribuciones, vector<int>& masCercano, int i) {
	int c = 0;
	int ubicacion = puestos[postas[i]];

	for (int j = 0; j < contribuciones.size(); j++) {
		if (masCercano[j] == i) {
			int minimo = 1e7;
			int cercano = 0;
			for (int x = 0; x < postas.size(); x++) {
				int dist = abs(puestos[j] - puestos[postas[x]]);
				if (dist < minimo) {
					minimo = dist;
					cercano = x;
				}
			}

			contribuciones[j] = minimo;
			masCercano[j] = cercano;
		}

		if (contribuciones[j] > abs(puestos[j] - ubicacion)) {
			contribuciones[j] = abs(puestos[j] - ubicacion);
			masCercano[j] = i;
		}

		c += contribuciones[j];
	}

	return c;
}

void solucionOptima(const vector<int>& puestos, vector<int>& postas, int i, int mejorCosto, vector<int>& mejorSol, vector<int>& contribuciones, vector<int>& masCercano) {
	if (i < 0) {
		return;
	}

	int posInicial = postas[i];

	for (int x = postas[i]; x < puestos.size(); x++) {
		if (i < postas.size() - 1 && x >= postas[i+1]) {
			break;
		}
		if (mejorSol.size() > 0) {
			return;
		}

		postas[i] = x;

		if (costo(puestos, postas, contribuciones, masCercano, i) == mejorCosto) {
			mejorSol = postas;
			return;
		}

		solucionOptima(puestos, postas, i-1, mejorCosto, mejorSol, contribuciones, masCercano);
	}

	postas[i] = posInicial;
	costo(puestos, postas, contribuciones, masCercano, i);
}

int mejorDist(const vector<int>& puestos, int n, vector<int>& postas) {
	/* Las postas solo pueden ir enfrente de puestos, las codificamos
	** con el número de puesto en el que están */

	// Estructuras de memorización para calcular el costo
	vector<int> contribuciones(puestos.size(), 1e7); // Cuánto contribuye al costo cada puesto
	vector<int> masCercano(puestos.size(), 0); // La posta más cercana a cada puesto

	int mejorCosto;

	for (int i = 0; i < n; i++) {
		postas.push_back(0);

		int costoMinimo = 1e7;
		int mejorPos = postas[i];

		for (int x = 0; x < puestos.size(); x++) {
			postas[i] = x;
			int nuevoCosto = costo(puestos, postas, contribuciones, masCercano, i);

			if (nuevoCosto < costoMinimo || ( nuevoCosto == costoMinimo && postas[i] < mejorPos )) {
				costoMinimo = nuevoCosto;
				mejorPos = postas[i];
			}
		}

		postas[i] = mejorPos;
		mejorCosto = costo(puestos, postas, contribuciones, masCercano, i);
	}

	vector<int> mejorSol;
	for (int i = 0; i < postas.size(); i++) {
		postas[i] = i;
	}

	solucionOptima(puestos, postas, postas.size() - 1, mejorCosto, mejorSol, contribuciones, masCercano);

	postas = mejorSol;

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
		cout << postas[0];
		for (int j = 1; j < postas.size(); j++) {
			cout << " " << postas[j];
		}
		cout << endl;
	}
}
