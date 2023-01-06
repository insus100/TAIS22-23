
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct par {
	int entrada;
	int salida;
};
#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

	// leer los datos de la entrada
	int V, A, v1, v2;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;
	Digrafo g(V);

	for (int i = 0; i < A; i++) {
		cin >> v1 >> v2;
		g.ponArista(v1, v2);
	}
	Digrafo g1(g.inverso());
	int v = 0;
	bool sumidero = false;
	for (int i = 0; i < V; i++) {
		int tam = g.ady(i).size();
		int tam2 = g1.ady(i).size();
		if (tam == 0 && tam2 == V - 1) {
			sumidero = true;
			v = i;
			break;
		}
	}
	if (sumidero) {
		cout << "SI " << v << "\n";
	}
	else {
		cout << "NO\n";
	}

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
