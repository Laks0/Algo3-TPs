#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool setearResultados(vector<int> valores, int i, int total, int objetivo,
                      vector<pair<bool, bool>>& resultados, bool suma) {
    if (i == valores.size()) {
        return (objetivo == total);
    }
    bool result = false;
    if (setearResultados(valores, i + 1, total + valores[i], objetivo,
                         resultados, true)) {
        resultados[i].first = true;
        result = true;
    }
    if (setearResultados(valores, i + 1, total - valores[i], objetivo,
                         resultados, false)) {
        resultados[i].second = true;
        result = true;
    }
    return result;
}

int main() {
    int c;
    cin >> c;

    vector<string> stringsResultantes(c);

    for (int i = 0; i < c; i++) {
        int n, objetivo;
        cin >> n >> objetivo;
        vector<int> valores(n);
        vector<pair<bool, bool>> resultados(n);

        for (int j = 0; j < n; j++) {
            cin >> valores[j];
        }

        setearResultados(valores, 0, 0, objetivo, resultados, true);
        setearResultados(valores, 0, 0, objetivo, resultados, false);

        stringsResultantes[i] = "";
        for (int j = 0; j < n; j++) {
            if (resultados[j].first && resultados[j].second) {
                stringsResultantes[i] += "?";
            } else if (resultados[j].first) {
                stringsResultantes[i] += "+";
            } else if (resultados[j].second) {
                stringsResultantes[i] += "-";
            }
        }
    }

    for (int i = 0; i < c; i++) {
        cout << stringsResultantes[i] << endl;
    }

    return 0;
}
