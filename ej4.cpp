#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int ultimoCostoFijo(const vector<int>& puestos, const vector<int>& postas) {
	int c = 0;

	int principio = 0;
	if (postas.size() >= 2) {
		principio = postas[postas.size() - 2];
	}

	// Ubicaciones en coordenadas de los límites del cálculo
	// La posta anterior
	int a = -1e5;
	if (postas.size() >= 2) {
		a = puestos[principio];
	}

	// La última posta
	int b = puestos[postas[postas.size() - 1]];

	for (int i = principio; i < postas[postas.size() - 1]; i++) {
		c += min(abs(puestos[i] - a), abs(puestos[i] - b));
	}

	return c;
}

int ponerPostas(const vector<int>& puestos, int i, int k, int dist, vector<vector<vector<int>>>& mejores, vector<int>& postas) {
	if (k == 0 && i == puestos.size()) {
		int costoFinal = 0;

		// Coordenada de la última posta
		int ultimaPosta = puestos[postas[postas.size() - 1]];

		for (int x = postas[postas.size() - 1]; x < puestos.size(); x++) {
			costoFinal += abs(puestos[x] - ultimaPosta);
		}

		return costoFinal;
	}

	if (i == puestos.size()) {
		return 1e7;
	}

	if (k == 0) {
		int alFinal = ponerPostas(puestos, puestos.size(), k, dist + puestos.size() - i, mejores, postas);
		mejores[i][k][dist] = alFinal;
	}

	if (mejores[i][k][dist] != -1) {
		return mejores[i][k][dist];
	}

	postas.push_back(i);
	int costoFijo = ultimoCostoFijo(puestos, postas);
	int poniendo = ponerPostas(puestos, i+1, k-1, 0, mejores, postas) + costoFijo;

	postas.pop_back();
	int sinPoner = ponerPostas(puestos, i+1, k, dist + 1, mejores, postas);

	mejores[i][k][dist] = min(poniendo, sinPoner);

	return mejores[i][k][dist];
}

vector<int> reconstruirSol(int k, const vector<vector<vector<int>>>& mejores, const vector<int> puestos) {
	vector<int> postas;

	int dist = 0;

	for (int i = 0; i < puestos.size() - 1; i++) {
		int poniendo = 1e5;
		if (k > 0)
			poniendo = mejores[i+1][k-1][0];
		int sinPoner = mejores[i+1][k][dist+1];

		if (sinPoner != -1 && sinPoner > poniendo) {
			dist++;
		}
		if (poniendo != -1 && poniendo <= sinPoner) {
			k--;
			dist = 0;
			postas.push_back(puestos[i]);
		}
	}

	return postas;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n, k;
		cin >> n >> k;

		vector<int> puestos(n);
		for (int x = 0; x < n; x++) {
			cin >> puestos[x];
		}

		vector<int> postas;

		// Estructura de memorización
		vector<vector<vector<int>>> mejores(n, vector<vector<int>>(k+1, vector<int>(n, -1)));

		vector<int> mejorSol;
		int res = ponerPostas(puestos, 0, k, 0, mejores, postas);

		postas = reconstruirSol(k, mejores, puestos);

		cout << res << endl;

		for (int p : postas) {
			cout << p << endl;
		}
	}
}
