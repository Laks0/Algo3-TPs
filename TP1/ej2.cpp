#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

float calcularFactor(int tiempo, int coeficiente) {
    return static_cast<float>(coeficiente) / (tiempo);
}

bool compararFactores(pair<int, int> a, pair<int, int> b) {
    return calcularFactor(a.first, a.second) >
           calcularFactor(b.first, b.second);
}

int descontento(vector<pair<int, int>> examenes) {
    int n = examenes.size();

    sort(examenes.begin(), examenes.end(), compararFactores);

    int tiempoTotal = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            tiempoTotal += (examenes[i].first * examenes[j].second) % MOD;
            tiempoTotal %= MOD;
        }
    }

    return tiempoTotal;
}

int main() {
    int c;
    cin >> c;

    vector<int> results(c);

    for (int i = 0; i < c; i++) {
        int n;
        cin >> n;
        vector<pair<int, int>> examenes(n);

        for (int j = 0; j < n; j++) {
            cin >> examenes[j].first;
        }

        for (int j = 0; j < n; j++) {
            cin >> examenes[j].second;
        }

        results[i] = descontento(examenes);
    }

    for (int i = 0; i < c; i++) {
        cout << results[i] << endl;
    }

    return 0;
}
