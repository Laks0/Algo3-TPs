#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool llegaAlFinal(vector<int> valores, int i, int totalAnterior, int objetivo,
                  vector<pair<vector<char>, vector<char>>>& resultados,
                  bool suma) {
    // cout << "i: " << i << endl
    //      << "total anterior: " << totalAnterior << endl
    //      << "siguiente: " << valores[i] << endl
    //      << "total siguiente: " << valores[i] + totalAnterior << endl
    //      << "resultados en [i][totalAnterior] (Positivo): '"
    //      << resultados[i].first[abs(totalAnterior)] << "'" << endl
    //      << "resultados en [i][totalAnterior] (Negativo): '"
    //      << resultados[i].second[abs(totalAnterior)] << "'" << endl;
    if (totalAnterior >= 0) {
        if (i + 1 == valores.size()) {
            if (totalAnterior + valores[i] == objetivo) {
                // cout << "En este paso llego haciendo una suma" << endl <<
                // endl;
                resultados[i].first[totalAnterior] = '+';
                return true;
            } else if (totalAnterior - valores[i] == objetivo) {
                // cout << "En este paso llego haciendo una resta" << endl <<
                // endl;
                resultados[i].first[totalAnterior] = '-';
                return true;
            } else {
                // cout << "En este paso no llego" << endl << endl;
                resultados[i].first[totalAnterior] = 'X';
                return false;
            }
        }

        if (resultados[i].first[totalAnterior] != 'O' &&
            resultados[i].first[totalAnterior] != '\0' &&
            int(resultados[i].first[totalAnterior]) != 0) {
            if (resultados[i].first[totalAnterior] == '+' && !suma) {
                // cout << "En el " << i
                //      << "hay una suma pero estoy viendo la resta" << endl;
                bool llegaRestando =
                    llegaAlFinal(valores, i + 1, totalAnterior - valores[i],
                                 objetivo, resultados, false);
                if (llegaRestando) {
                    resultados[i].first[totalAnterior] = '?';
                }
            }

            return resultados[i].first[totalAnterior] != 'X';
        } else {
            bool llegaSumando =
                llegaAlFinal(valores, i + 1, totalAnterior + valores[i],
                             objetivo, resultados, true);
            bool llegaRestando =
                llegaAlFinal(valores, i + 1, totalAnterior - valores[i],
                             objetivo, resultados, false);
            if (llegaSumando && llegaRestando) {
                resultados[i].first[totalAnterior] = '?';
                return true;
            } else if (llegaSumando) {
                resultados[i].first[totalAnterior] = '+';
                return true;
            } else if (llegaRestando) {
                resultados[i].first[totalAnterior] = '-';
                return true;
            } else {
                resultados[i].first[totalAnterior] = 'X';
                return true;
            }
        }
    } else {
        if (i + 1 == valores.size()) {
            if (totalAnterior + valores[i] == objetivo) {
                // cout << "En este paso llego haciendo una suma" << endl <<
                // endl;
                resultados[i].second[abs(totalAnterior)] = '+';
                return true;
            } else if (totalAnterior - valores[i] == objetivo) {
                // cout << "En este paso llego haciendo una resta" << endl <<
                // endl;
                resultados[i].second[abs(totalAnterior)] = '-';
                return true;
            } else {
                resultados[i].second[abs(totalAnterior)] = 'X';
                // cout << "En este paso no llego" << endl << endl;
                return false;
            }
        }

        if (resultados[i].first[totalAnterior] != 'O' &&
            resultados[i].first[totalAnterior] != '\0' &&
            int(resultados[i].first[totalAnterior]) != 0) {
            return resultados[i].second[abs(totalAnterior)] != 'X';
        } else {
            bool llegaSumando =
                llegaAlFinal(valores, i + 1, totalAnterior + valores[i],
                             objetivo, resultados, true);
            bool llegaRestando =
                llegaAlFinal(valores, i + 1, totalAnterior - valores[i],
                             objetivo, resultados, false);
            if (llegaSumando && llegaRestando) {
                resultados[i].second[abs(totalAnterior)] = '?';
                return true;
            } else if (llegaSumando) {
                resultados[i].second[abs(totalAnterior)] = '+';
                return true;
            } else if (llegaRestando) {
                resultados[i].second[abs(totalAnterior)] = '-';
                return true;
            } else {
                resultados[i].second[abs(totalAnterior)] = 'X';
                return true;
            }
        }
    }
}

void mostrarTodo(vector<pair<vector<char>, vector<char>>> resultados) {
    for (int i = 0; i < resultados.size(); i++) {
        for (int j = 0; j < resultados[i].first.size(); j++) {
            cout << resultados[i].first[j];
        }
    }

    cout << endl << "------------------------" << endl;
    for (int i = 0; i < resultados.size(); i++) {
        for (int j = 0; j < resultados[i].second.size(); j++) {
            cout << resultados[i].second[j];
        }
    }
}

void mostrarSecuencia(vector<pair<vector<char>, vector<char>>> resultados,
                      vector<int> valores) {
    string resultado = "";
    // resultado += resultados[0].first[0];

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

        bool llegaSumando =
            llegaAlFinal(valores, 0, 0, objetivo, resultados, true);
        bool llegaRestando =
            llegaAlFinal(valores, 0, 0, objetivo, resultados, false);
        cout << llegaSumando << " " << llegaRestando << endl;

        mostrarSecuencia(resultados, valores);
        mostrarTodo(resultados);
    }

    return 0;
}
