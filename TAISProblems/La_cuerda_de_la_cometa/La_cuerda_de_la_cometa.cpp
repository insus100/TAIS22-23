
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
const int64_t INF = 1000000000;
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Cuerda {
	int longitud;
	int coste;
};
bool posible(vector<Cuerda> const& c, int64_t l) {
	int64_t n = c.size();
	Matriz<int64_t> cuerdas(n + 1, l + 1, false);
	cuerdas[0][0] = true;
	for (int64_t i = 1; i <= n; i++) {
		cuerdas[i][0] = true;
		for (int64_t j = 1; j <= l; j++)
			if (c[i - 1].longitud > j)
				cuerdas[i][j] = cuerdas[i - 1][j];
			else
				cuerdas[i][j] = cuerdas[i - 1][j] || cuerdas[i - 1][j - c[i - 1].longitud];
	}
	return cuerdas[n][l];
}

int64_t formas(vector < Cuerda> const& c, int64_t l) {
	int64_t n = c.size();
	Matriz<int64_t> cuerdas(n + 1, l + 1, 0);
	cuerdas[0][0] = 1;
	for (int64_t i = 1; i <= n; i++) {
		cuerdas[i][0] = 1;
		for (int64_t j = 1; j <= l; j++)
			if (c[i - 1].longitud > j)
				cuerdas[i][j] = cuerdas[i - 1][j];
			else
				cuerdas[i][j] = cuerdas[i - 1][j] + cuerdas[i - 1][j - c[i - 1].longitud];
	}
	return cuerdas[n][l];
}

int64_t minimo(vector<Cuerda> const& C, int64_t l) {
	int64_t n = C.size();
	Matriz<int64_t> cuerdas(n + 1, l + 1, INF);
	cuerdas[0][0] = 0;
	for (int64_t i = 1; i <= n; i++) {
		cuerdas[i][0] = 0;
		for (int64_t j = 1; j <= l; j++) {
			if (C[i - 1].longitud > j) {
				cuerdas[i][j] = cuerdas[i - 1][j];
			}
			else {
				cuerdas[i][j] = min(cuerdas[i - 1][j], cuerdas[i - 1][j - C[i - 1].longitud] + 1);
			}
		}
	}
	return cuerdas[n][l];
}

int64_t coste(vector<Cuerda> const& C, int64_t l) {
	int64_t n = C.size();
	Matriz<int64_t> cuerdas(n + 1, l + 1, INF);
	cuerdas[0][0] = 0;
	for (int64_t i = 1; i <= n; i++) {
		cuerdas[i][0] = 0;
		for (int64_t j = 1; j <= l; j++) {
			if (C[i - 1].longitud > j) {
				cuerdas[i][j] = cuerdas[i - 1][j];
			}
			else {
				cuerdas[i][j] = min(cuerdas[i - 1][j], cuerdas[i - 1][j - C[i - 1].longitud] + C[i - 1].coste);
			}
		}
	}
	return cuerdas[n][l];
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int64_t N, L;
	cin >> N >> L;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<Cuerda> C;
	Cuerda aux;
	for (int64_t i = 0; i < N; i++) {
		cin >> aux.longitud >> aux.coste;
		C.push_back(aux);
	}
	// resolver el caso posiblemente llamando a otras funciones
	bool esPosible = posible(C, L);

	// escribir la solución
	if (!esPosible) {
		cout << "NO";
	}
	else {
		cout << "SI ";
		cout << formas(C, L);
		cout << " ";
		cout << minimo(C, L);
		cout << " ";
		cout << coste(C, L);
	}
	cout << "\n";
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}
