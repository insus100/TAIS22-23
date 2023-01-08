
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int minParches(vector<int> const& v, int const& n, int const& l) {
	int parches = 0, longitud = 0;
	for (int i = 0; i < n; i++) {
		if (parches != 0) {// resto de parches 
			if (!(v[i] - longitud <= l)) {
				longitud = v[i];
				parches++;
			}
		}
		else {//primer parche
			longitud = v[i];
			parches++;
		}
	}
	return parches;
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int N, L;
	cin >> N >> L;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> pos_agujeros(N);
	for (int i = 0; i < N; i++) {
		cin >> pos_agujeros[i];
	}

	// resolver el caso posiblemente llamando a otras funciones
	int sol = minParches(pos_agujeros, N, L);
	// escribir la solución
	cout << sol << "\n";
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
