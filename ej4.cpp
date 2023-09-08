#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int costo(const vector<int>& puestos, const vector<int>& postas, vector<int>& aportes, int costoAnterior, int& costoFijo) {
	int c = costoAnterior;

	// Los únicos aportes al costo que cambian son los de los puestos después de
	// la anteúltima posta que pusimos
	int principio = 0;
	if (postas.size() > 1) {
		principio = puestos[postas[postas.size() - 2]];
	}

	// Hay que hacer esto porque guardamos el índice del puesto que está enfrente de la posta
	int posicionUltimaPosta = puestos[postas[postas.size() - 1]];

	for (int i = principio; i < puestos.size(); i++) {
		c -= aportes[i];

		aportes[i] = min(aportes[i], abs(puestos[i] - posicionUltimaPosta));

		c += aportes[i];
		if (i < posicionUltimaPosta)
			costoFijo += aportes[i];
	}

	return c;
}

/* Backtracking yendo en orden lexicográfico de las posibles soluciones
 * Como en la mejor solución las postas están siempre en el mismo lugar
 * que un puesto, las codificamos directamente con el índice de puesto 
 * que corresponde. Esto hace más eficiente también el cálculo del costo*/
int ponerPostas(const vector<int>& puestos, vector<int>& postas, vector<int>& mejorSol, vector<int>& aportes, int costoActual, int costoFijo,int mejorCosto, int i, int k) {
	if (k == 0) {
		if (costoActual < mejorCosto) {
			mejorSol = postas;
		}
		return costoActual;
	}
	if (i >= puestos.size() || costoFijo > mejorCosto) {
		return 1e7;
	}
	// Llenar todos los espacios que quedan
	if (i == puestos.size() - k) {
		if (costoFijo < mejorCosto) {
			mejorSol = postas;

			for (int x = i; x < puestos.size(); x++) {
				mejorSol.push_back(x);
			}
		}
		return costoFijo;
	}

	vector<int> memAportes(aportes);

	postas.push_back(i);
	int nuevoCosto = costo(puestos, postas, aportes, costoActual, costoFijo);
	int poniendo = ponerPostas(puestos, postas, mejorSol, aportes, nuevoCosto, costoFijo, mejorCosto, i + 1, k - 1);
	if (poniendo < mejorCosto) {
		mejorCosto = poniendo;
	}

	postas.pop_back();
	aportes = memAportes;
	int sinPoner = ponerPostas(puestos, postas, mejorSol, aportes, costoActual, costoFijo, mejorCosto, i + 1, k);
	if (sinPoner < mejorCosto) {
		mejorCosto = sinPoner;
	}

	return mejorCosto;
}

void pasarACoordenadas(const vector<int>& puestos, vector<int>& postas) {
	for (int i = 0; i < postas.size(); i++) {
		postas[i] = puestos[postas[i]];
	}
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

		int maxPos = puestos[n-1];
		vector<int> aportes(n, 1e5);

		vector<int> postas;
		vector<int> mejorSol;

		int res = ponerPostas(puestos, postas, mejorSol, aportes, n*1e5, 0, 1e7, 0, k);

		pasarACoordenadas(puestos, mejorSol);

		cout << res << endl;
		cout << mejorSol[0];
		for (int j = 1; j < k; j++) {
			cout << " " << mejorSol[j];
		}
		cout << endl;
	}
}
