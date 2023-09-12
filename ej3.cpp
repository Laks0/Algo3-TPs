#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool llegaAlFinal(vector<int> valores, int i, int totalActual, int objetivo,
                  vector<pair<vector<char>, vector<char>>>& resultados) {
    if (totalActual >= 0) {
        if (i + 1 == valores.size()) {
            if (totalActual + valores[i] == objetivo) {
                if (resultados[i].first[totalActual] == '-') {
                    resultados[i].first[totalActual] = '?';
                } else {
                    resultados[i].first[totalActual] = '+';
                }

                return true;
            } else if (totalActual - valores[i] == objetivo) {
                if (resultados[i].first[totalActual] == '+') {
                    resultados[i].first[totalActual] = '?';
                } else {
                    resultados[i].first[totalActual] = '-';
                }
                return true;
            } else {
                if (resultados[i].first[totalActual] == 'O') {
                    resultados[i].first[totalActual] = 'X';
                }
                return false;
            }
        }
        if (resultados[i].first[totalActual] != 'O') {
        } else {
            bool llegaSumando = llegaAlFinal(
                valores, i + 1, totalActual + valores[i], objetivo, resultados);
            bool llegaRestando = llegaAlFinal(
                valores, i + 1, totalActual - valores[i], objetivo, resultados);
            if (llegaSumando && llegaRestando) {
                resultados[i].first[totalActual] = '?';
                return true;
            } else if (llegaSumando) {
                resultados[i].first[totalActual] = '+';
                return true;
            } else if (llegaRestando) {
                resultados[i].first[totalActual] = '-';
                return true;
            } else {
                resultados[i].first[totalActual] = 'X';
                return false;
            }
        }
    } else {
        if (i + 1 == valores.size()) {
            if (totalActual + valores[i] == objetivo) {
                if (resultados[i].second[abs(totalActual)] == '-') {
                    resultados[i].second[abs(totalActual)] = '?';
                } else {
                    resultados[i].second[abs(totalActual)] = '+';
                }

                return true;
            } else if (totalActual - valores[i] == objetivo) {
                if (resultados[i].second[abs(totalActual)] == '+') {
                    resultados[i].second[abs(totalActual)] = '?';
                } else {
                    resultados[i].second[abs(totalActual)] = '-';
                }
                return true;
            } else {
                if (resultados[i].second[abs(totalActual)] == 'O') {
                    resultados[i].second[abs(totalActual)] = 'X';
                }
                return false;
            }
        }
        if (resultados[i].second[abs(totalActual)] != 'O') {
            return resultados[i].second[abs(totalActual)] != 'X';
        } else {
            bool llegaSumando = llegaAlFinal(
                valores, i + 1, totalActual + valores[i], objetivo, resultados);
            bool llegaRestando = llegaAlFinal(
                valores, i + 1, totalActual - valores[i], objetivo, resultados);
            if (llegaSumando && llegaRestando) {
                resultados[i].second[abs(totalActual)] = '?';
                return true;
            } else if (llegaSumando) {
                resultados[i].second[abs(totalActual)] = '+';
                return true;
            } else if (llegaRestando) {
                resultados[i].second[abs(totalActual)] = '-';
                return true;
            } else {
                resultados[i].second[abs(totalActual)] = 'X';

                return false;
            }
        }
    }
    return false;
}

void mostrarSecuencia(vector<pair<vector<char>, vector<char>>> resultados,
                      vector<int> valores) {
    string resultado = "";

    for (int i = 0; i < valores.size(); i++) {
        bool haySuma = false;
        bool hayResta = false;
        bool haySigno = false;
        for (int j = 0; j < resultados[i].first.size(); j++) {
            char actualPos = resultados[i].first[j];
            char actualNeg = resultados[i].second[j];
            switch (actualPos) {
                case '+':
                    haySuma = true;
                    break;
                case '-':
                    hayResta = true;
                    break;
                case '?':
                    haySigno = true;
                    break;
                default:
                    break;
            }
            switch (actualNeg) {
                case '+':
                    haySuma = true;
                    break;
                case '-':
                    hayResta = true;
                    break;
                case '?':
                    haySigno = true;
                    break;
                default:
                    break;
            }
        }
        if (haySigno || (haySuma && hayResta)) {
            resultado += '?';
        } else if (haySuma) {
            resultado += '+';
        } else if (hayResta) {
            resultado += '-';
        }
    }

    cout << resultado << endl;
}

int main() {
    int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int n, objetivo;
        cin >> n >> objetivo;
        objetivo /= 100;
        vector<int> valores(n);
        vector<pair<vector<char>, vector<char>>> resultados(
            n, make_pair(vector<char>(10000, 'O'), vector<char>(10000, 'O')));

        for (int j = 0; j < n; j++) {
            int valor;
            cin >> valor;
            valores[j] = valor / 100;
        }
        bool llega = llegaAlFinal(valores, 0, 0, objetivo, resultados);

        mostrarSecuencia(resultados, valores);
    }

    return 0;
}
