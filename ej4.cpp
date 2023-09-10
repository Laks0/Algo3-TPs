#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

long long ultimoCosto(const vector<int>& puestos, int a, int b) {
	long long c = 0;

	int posA = -2e9;
	if (a < puestos.size()) {
		posA = puestos[a];
	}

	int posB = b;
	if (b < puestos.size()) {
		posB = puestos[b];
	}

	int inicio = a;
	if (a == puestos.size()) {
		inicio = 0;
	}

	for (int i = inicio; i < min(b, (int) puestos.size()); i++) {
		c += min(abs(puestos[i] - posA), abs(puestos[i] - posB));
	}

	return c;
}

long long mejorCosto(const vector<int>& puestos, int i, int k, int ult, vector<vector<vector<long long>>>& mejores) {
	if (k == 0 && i == puestos.size()) {
		return ultimoCosto(puestos, ult, 3e7);
	}

	if (k > 0 && i == puestos.size()) {
		return 2e9;
	}

	if (ult >= 0 && mejores[i][k][ult] != -1) {
		return mejores[i][k][ult];
	}

	long long poniendo = 2e9;
	if (k > 0) {
		long long costoFijo = ultimoCosto(puestos, ult, i);
		poniendo = mejorCosto(puestos, i+1, k-1, i, mejores) + costoFijo;
	}

	long long sinPoner = mejorCosto(puestos, i+1, k, ult, mejores);

	mejores[i][k][ult] = min(poniendo, sinPoner);
	return mejores[i][k][ult];
}

vector<int> reconstruirSol(const vector<int>& puestos, int k, const vector<vector<vector<long long>>>& mejores) {
	vector<int> postas;

	int ult = puestos.size();

	for (int i = 0; i < puestos.size() - 1; i++) {
		int poniendo = 2e9;
		if (k > 0) {
			int costoFijo = ultimoCosto(puestos, ult, i);
			poniendo = mejores[i+1][k-1][i] + costoFijo;
		}

		int sinPoner = mejores[i+1][k][ult];

		if (poniendo <= sinPoner) {
			postas.push_back(puestos[i]);
			ult = i;
			k--;
		}
	}

	if (k==1) {
		postas.push_back(puestos[puestos.size() - 1]);
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

		vector<vector<vector<long long>>> mejores(n, vector<vector<long long>>(k+1, vector<long long>(n+1, -1)));

		long long res = mejorCosto(puestos, 0, k, n, mejores);

		vector<int> postas = reconstruirSol(puestos, k, mejores);

		cout << res << endl;
		cout << postas[0];
		for (int x = 1; x < postas.size(); x++) {
			cout << " " << postas[x];
		}
		cout << endl;
	}
}
